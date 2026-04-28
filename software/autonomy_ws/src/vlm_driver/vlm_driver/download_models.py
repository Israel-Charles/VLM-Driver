"""Download all enabled models from a registry YAML."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from huggingface_hub import snapshot_download

from .model_registry import (
    enable_hf_transfer_if_available,
    load_registry,
    resolve_hf_token,
)


def ensure_one(repo_id: str, local_dir: Path, token):
    local_dir.mkdir(parents=True, exist_ok=True)
    if (local_dir / "config.json").is_file():
        print(f"[cache] already present: {repo_id} -> {local_dir}")
        return
    print(f"[download] {repo_id} -> {local_dir}")
    snapshot_download(repo_id=repo_id, local_dir=str(local_dir), token=token)
    print(f"[done]     {repo_id}")


def main(argv=None):
    p = argparse.ArgumentParser(description="Download VLMs listed in a registry YAML.")
    p.add_argument("--config", required=True, help="Path to models.yaml")
    p.add_argument("--model-root", default="", help="Override model_root from YAML")
    p.add_argument("--only", default="", help="Download only this model key")
    p.add_argument("--hf-token", default="", help="HF token (overrides env/login)")
    args = p.parse_args(argv)

    enable_hf_transfer_if_available()
    token = resolve_hf_token(args.hf_token)
    if token is None:
        print("[auth] No HF token. Public models will still download (slower); "
              "gated models will fail.")
    else:
        print("[auth] HF token detected.")

    reg = load_registry(args.config, args.model_root)
    print(f"[setup] model_root = {reg.model_root}")

    keys = [args.only] if args.only else [k for k, e in reg.models.items() if e.enabled]
    failed = []
    for key in keys:
        entry = reg.get(key)
        if not args.only and not entry.enabled:
            continue
        try:
            ensure_one(entry.repo_id, entry.local_dir(reg.model_root), token)
        except Exception as e:
            print(f"[error] {entry.repo_id}: {e}")
            failed.append(key)

    if failed:
        print(f"\n[summary] failed: {failed}")
        sys.exit(1)
    print("\n[summary] all requested models present.")