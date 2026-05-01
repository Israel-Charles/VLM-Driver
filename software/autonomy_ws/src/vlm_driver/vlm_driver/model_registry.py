"""Loads the model registry and resolves auth tokens."""

from __future__ import annotations

import os
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Optional

import yaml


@dataclass
class ModelEntry:
    """One configured model and the local folder where it should live."""

    key: str
    repo_id: str
    subfolder: str
    family: str
    enabled: bool

    def local_dir(self, model_root: Path) -> Path:
        """Return the local path for this model under the configured root."""
        return model_root / self.subfolder


@dataclass
class Registry:
    """Loaded registry of known model keys and their metadata."""

    model_root: Path
    models: Dict[str, ModelEntry]

    def get(self, key: str) -> ModelEntry:
        """Look up one model entry by key."""
        if key not in self.models:
            raise KeyError(
                f"Model key '{key}' not found in registry. "
                f"Known keys: {sorted(self.models.keys())}"
            )
        return self.models[key]


def load_registry(yaml_path: str, model_root_override: str = "") -> Registry:
    """Load models.yaml and return a registry object."""
    with open(yaml_path, "r") as f:
        data = yaml.safe_load(f)

    root_str = model_root_override or data.get("model_root", "")
    if not root_str:
        raise ValueError(f"model_root not set in {yaml_path} and no override given.")
    model_root = Path(os.path.expanduser(root_str))

    entries: Dict[str, ModelEntry] = {}
    for key, spec in (data.get("models") or {}).items():
        entries[key] = ModelEntry(
            key=key,
            repo_id=spec["repo_id"],
            subfolder=spec["subfolder"],
            family=spec["family"],
            enabled=bool(spec.get("enabled", True)),
        )
    return Registry(model_root=model_root, models=entries)


# HF token. Leave blank to fall back to env vars or huggingface-cli login.
# Prefer setting HF_TOKEN in shell instead of writing it here.
#
# To set token in SHELL, run this in your terminal:
# `export HF_TOKEN="your_huggingface_token_here"`
#
# This will only make it active in current terminal windows
#
# To make it persistent, add it to your current shell, such as `.bashrc`. Ex: 
# `echo 'export HF_TOKEN="your_huggingface_token_here"' >> ~/.bashrc`
# `source ~/.bashrc`

def resolve_hf_token(explicit: str = "") -> Optional[str]:
    """Priority: explicit arg > HF_TOKEN > HUGGING_FACE_HUB_TOKEN > stored login."""
    if explicit:
        return explicit
    for var in ("HF_TOKEN", "HUGGING_FACE_HUB_TOKEN"):
        v = os.environ.get(var)
        if v:
            return v
    try:
        from huggingface_hub import HfFolder
        return HfFolder.get_token()
    except Exception:
        return None


def enable_hf_transfer_if_available() -> None:
    """Enable the faster Hugging Face transfer backend when it is installed."""
    try:
        import hf_transfer  # noqa: F401
        os.environ.setdefault("HF_HUB_ENABLE_HF_TRANSFER", "1")
    except ImportError:
        pass