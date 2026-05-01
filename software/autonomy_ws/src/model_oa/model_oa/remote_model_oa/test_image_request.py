"""Small image request to check that the remote model handles vision input."""

import requests
import json

URL = "https://samaviajaffery--example-sglang-low-latency-sglang-dev.us-east.modal.direct/v1/chat/completions"

payload = {
    "model": "Qwen/Qwen2.5-VL-7B-Instruct",
    "messages": [
        {
            "role": "user",
            "content": [
                {
                    "type": "text",
                    "text": """
You are an obstacle avoidance model for a small autonomous vehicle.

Look at the image and return ONLY valid JSON:
{
  "steering": "hard_left | left | slight_left | straight | slight_right | right | hard_right",
  "speed": "stop | slow | medium",
  "reason": "short reason"
}
"""
                },
                {
                    "type": "image_url",
                    "image_url": {
                        "url": "https://raw.githubusercontent.com/sgl-project/sglang/main/examples/assets/example_image.png"
                    }
                }
            ]
        }
    ],
    "temperature": 0,
    "max_tokens": 128,
}

response = requests.post(URL, json=payload, timeout=60)
print(response.status_code)
print(json.dumps(response.json(), indent=2))