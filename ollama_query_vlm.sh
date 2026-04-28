#!/bin/bash
IMAGE_B64=$(base64 "$1")   # Linux-compatible

curl http://[PUBLIC_IP]:11434/api/generate \
  -H "Content-Type: application/json" \
  -d "$(jq -n \
    --arg model "qwen2.5vl:7b" \
    --arg prompt "What do you see?" \
    --arg img "$IMAGE_B64" \
    '{model: $model, prompt: $prompt, stream: false, images: [$img]}')"
