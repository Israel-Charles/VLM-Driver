"""Family-aware loader and inference runner. Holds one model in GPU at a time."""

from __future__ import annotations

import time
from pathlib import Path
from typing import Optional, Tuple

from PIL import Image


def _select_dtype_and_device():
    import torch
    if torch.cuda.is_available():
        return torch.bfloat16, "auto"
    return torch.float32, None


class InferenceEngine:
    def __init__(self):
        self.model = None
        self.processor = None
        self.family: Optional[str] = None
        self.local_path: Optional[Path] = None

    # -------- lifecycle --------

    def is_loaded(self) -> bool:
        return self.model is not None

    def load(self, family: str, local_path: Path) -> None:
        if self.is_loaded():
            self.unload()

        if family == "qwen2_5_vl":
            from transformers import (
                AutoProcessor,
                Qwen2_5_VLForConditionalGeneration as ModelCls,
            )
            dtype, device_map = _select_dtype_and_device()
            self.model = ModelCls.from_pretrained(
                str(local_path), torch_dtype=dtype, device_map=device_map,
            )
            self.processor = AutoProcessor.from_pretrained(str(local_path))

        elif family == "qwen3_vl":
            from transformers import (
                AutoProcessor,
                Qwen3VLForConditionalGeneration as ModelCls,
            )
            dtype, device_map = _select_dtype_and_device()
            self.model = ModelCls.from_pretrained(
                str(local_path), torch_dtype=dtype, device_map=device_map,
            )
            self.processor = AutoProcessor.from_pretrained(str(local_path))

        elif family == "llava":
            from transformers import AutoProcessor, LlavaForConditionalGeneration
            dtype, device_map = _select_dtype_and_device()
            self.model = LlavaForConditionalGeneration.from_pretrained(
                str(local_path), torch_dtype=dtype, device_map=device_map,
            )
            self.processor = AutoProcessor.from_pretrained(str(local_path))

        elif family == "llava_onevision":
            from transformers import (
                AutoProcessor,
                LlavaOnevisionForConditionalGeneration,
            )
            dtype, device_map = _select_dtype_and_device()
            self.model = LlavaOnevisionForConditionalGeneration.from_pretrained(
                str(local_path), torch_dtype=dtype, device_map=device_map,
            )
            self.processor = AutoProcessor.from_pretrained(str(local_path))

        elif family == "mllama":
            from transformers import AutoProcessor, MllamaForConditionalGeneration
            dtype, device_map = _select_dtype_and_device()
            self.model = MllamaForConditionalGeneration.from_pretrained(
                str(local_path), torch_dtype=dtype, device_map=device_map,
            )
            self.processor = AutoProcessor.from_pretrained(str(local_path))

        else:
            raise ValueError(f"Unsupported family: {family}")

        self.model.eval()

        # Strip sampling-only fields so do_sample=False doesn't warn about them.
        gc = getattr(self.model, "generation_config", None)
        if gc is not None:
            for attr in ("temperature", "top_p", "top_k", "typical_p", "min_p"):
                if hasattr(gc, attr):
                    try:
                        setattr(gc, attr, None)
                    except Exception:
                        pass
            gc.do_sample = False

        self.family = family
        self.local_path = local_path

    def unload(self) -> None:
        self.model = None
        self.processor = None
        self.family = None
        self.local_path = None
        try:
            import gc, torch
            gc.collect()
            if torch.cuda.is_available():
                torch.cuda.empty_cache()
                torch.cuda.ipc_collect()
        except Exception:
            pass

    # -------- inference --------

    def infer_pil(self, image: Image.Image, prompt: str, max_new_tokens: int = 128) -> Tuple[str, float]:
        """Returns (raw_text, latency_seconds)."""
        if not self.is_loaded():
            raise RuntimeError("No model loaded.")

        if self.family in ("qwen2_5_vl", "qwen3_vl"):
            return self._run_qwen(image, prompt, max_new_tokens)
        if self.family in ("llava", "llava_onevision"):
            return self._run_llava_like(image, prompt, max_new_tokens)
        if self.family == "mllama":
            return self._run_mllama(image, prompt, max_new_tokens)
        raise ValueError(f"Unknown family: {self.family}")

    def _run_qwen(self, image, prompt, max_new_tokens):
        import torch
        # Pass the PIL image directly; qwen-vl-utils is path-oriented.
        messages = [{
            "role": "user",
            "content": [
                {"type": "image", "image": image},
                {"type": "text", "text": prompt},
            ],
        }]
        text = self.processor.apply_chat_template(
            messages, tokenize=False, add_generation_prompt=True
        )
        inputs = self.processor(
            text=[text],
            images=[image],
            padding=True,
            return_tensors="pt",
        ).to(self.model.device)

        t0 = time.time()
        with torch.inference_mode():
            out_ids = self.model.generate(
                **inputs, max_new_tokens=max_new_tokens, do_sample=False,
            )
        dt = time.time() - t0
        trimmed = [o[len(i):] for i, o in zip(inputs.input_ids, out_ids)]
        text_out = self.processor.batch_decode(
            trimmed, skip_special_tokens=True, clean_up_tokenization_spaces=False
        )[0].strip()
        return text_out, dt

    def _run_llava_like(self, image, prompt, max_new_tokens):
        import torch
        conversation = [{
            "role": "user",
            "content": [
                {"type": "image"},
                {"type": "text", "text": prompt},
            ],
        }]
        prompt_text = self.processor.apply_chat_template(
            conversation, add_generation_prompt=True
        )
        inputs = self.processor(
            images=image, text=prompt_text, return_tensors="pt"
        ).to(self.model.device)

        t0 = time.time()
        with torch.inference_mode():
            out_ids = self.model.generate(
                **inputs, max_new_tokens=max_new_tokens, do_sample=False,
            )
        dt = time.time() - t0
        full = self.processor.batch_decode(out_ids, skip_special_tokens=True)[0]
        if "ASSISTANT:" in full:
            full = full.split("ASSISTANT:", 1)[-1]
        return full.strip(), dt

    def _run_mllama(self, image, prompt, max_new_tokens):
        import torch
        messages = [{
            "role": "user",
            "content": [
                {"type": "image"},
                {"type": "text", "text": prompt},
            ],
        }]
        input_text = self.processor.apply_chat_template(
            messages, add_generation_prompt=True
        )
        inputs = self.processor(
            image, input_text, return_tensors="pt"
        ).to(self.model.device)

        t0 = time.time()
        with torch.inference_mode():
            out_ids = self.model.generate(
                **inputs, max_new_tokens=max_new_tokens, do_sample=False,
            )
        dt = time.time() - t0
        return self.processor.decode(out_ids[0], skip_special_tokens=True).strip(), dt