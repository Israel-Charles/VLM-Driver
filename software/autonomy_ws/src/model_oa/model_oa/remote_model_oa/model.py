####
#Run the model with: 
# modal deploy model.py

# stop it with:
# modal app stop example-sglang-low-latency
####
"""Modal app that serves the vision-language model through an SGLang endpoint."""

import asyncio
import json
import subprocess
import time

import aiohttp
import modal
import modal.experimental

MINUTES = 60  # seconds

sglang_image = modal.Image.from_registry(
    "lmsysorg/sglang:v0.5.9-cu129-amd64-runtime"
).entrypoint(
    []  
)

GPU_TYPE, N_GPUS = "A10G", 1
GPU = f"{GPU_TYPE}:{N_GPUS}"

MODEL_NAME = "Qwen/Qwen2.5-VL-7B-Instruct"
MODEL_REVISION = ( 
    "main" 
)

HF_CACHE_VOL = modal.Volume.from_name("huggingface-cache", create_if_missing=True)
HF_CACHE_PATH = "/root/.cache/huggingface"
MODEL_PATH = f"{HF_CACHE_PATH}/{MODEL_NAME}"

sglang_image = sglang_image.env(
    {"HF_HUB_CACHE": HF_CACHE_PATH, "HF_XET_HIGH_PERFORMANCE": "1"}
)
DG_CACHE_VOL = modal.Volume.from_name("deepgemm-cache", create_if_missing=True)
DG_CACHE_PATH = "/root/.cache/deepgemm"

sglang_image = sglang_image.env({"SGLANG_ENABLE_JIT_DEEPGEMM": "1"})

def compile_deep_gemm():
    """Compile DeepGEMM kernels during image setup when that path is enabled."""
    import os

    if int(os.environ.get("SGLANG_ENABLE_JIT_DEEPGEMM", "1")):
        subprocess.run(
            f"python3 -m sglang.compile_deep_gemm --model-path {MODEL_NAME} --revision {MODEL_REVISION} --tp {N_GPUS}",
            shell=True,
        )

sglang_image = sglang_image.run_function(
    compile_deep_gemm,
    volumes={DG_CACHE_PATH: DG_CACHE_VOL, HF_CACHE_PATH: HF_CACHE_VOL},
    gpu=GPU,
)


REGION = "us-east"
MIN_CONTAINERS = 1  # set to 1 to ensure one replica is always ready
TARGET_INPUTS = 10

with sglang_image.imports():
    import requests


def wait_ready(process: subprocess.Popen, timeout: int = 10 * MINUTES):
    """Wait until the local SGLang server answers its health endpoint."""
    deadline = time.time() + timeout
    while time.time() < deadline:
        try:
            check_running(process)
            requests.get(f"http://127.0.0.1:{PORT}/health").raise_for_status()
            return
        except (
            subprocess.CalledProcessError,
            requests.exceptions.ConnectionError,
            requests.exceptions.HTTPError,
        ):
            time.sleep(5)
    raise TimeoutError(f"SGLang server not ready within {timeout} seconds")


def check_running(p: subprocess.Popen):
    """Raise an error if the server process already exited."""
    if (rc := p.poll()) is not None:
        raise subprocess.CalledProcessError(rc, cmd=p.args)


def warmup():
    """Send a few tiny requests so the model is ready before real traffic arrives."""
    payload = {
        "messages": [{"role": "user", "content": "Hello, how are you?"}],
        "max_tokens": 16,
    }
    for _ in range(3):
        requests.post(
            f"http://127.0.0.1:{PORT}/v1/chat/completions", json=payload, timeout=10
        ).raise_for_status()

app = modal.App(name="example-sglang-low-latency")
PORT = 8000


@app.cls(
    image=sglang_image,
    gpu=GPU,
    volumes={HF_CACHE_PATH: HF_CACHE_VOL, DG_CACHE_PATH: DG_CACHE_VOL},
    region=REGION,
    min_containers=MIN_CONTAINERS,
    startup_timeout=600
)
@modal.experimental.http_server(
    port=PORT,  # wrapped code must listen on this port
    proxy_regions=[REGION],  # location of proxies, should be same as Cls region
    exit_grace_period=15,  # seconds, time to finish up requests when closing down
)
@modal.concurrent(target_inputs=TARGET_INPUTS)
class SGLang:
    """Modal class that owns one SGLang server process."""

    @modal.enter()
    def startup(self):
        """Start the SGLang server and block until it is healthy, then warm it up and put it to sleep."""
        cmd = [
            "python",
            "-m",
            "sglang.launch_server",
            "--model-path",
            MODEL_NAME,
            "--revision",
            MODEL_REVISION,
            "--served-model-name",
            MODEL_NAME,
            "--host",
            "0.0.0.0",
            "--port",
            f"{PORT}",
            "--tp",  # use all GPUs to split up tensor-parallel operations
            f"{N_GPUS}",
            "--cuda-graph-max-bs",  # only capture CUDA graphs for batch sizes we're likely to observe
            f"{TARGET_INPUTS * 2}",
            "--enable-metrics",  # expose metrics endpoints for telemetry
            "--decode-log-interval",  # how often to log during decoding, in tokens
            "100",
            "--mem-fraction",  # leave space for speculative model
            "0.8",
        ]

        

        self.process = subprocess.Popen(cmd)
        wait_ready(self.process)
        warmup()

    @modal.exit()
    def stop(self):
        """Stop the SGLang process when Modal shuts the container down."""
        self.process.terminate()




print("no issue")
