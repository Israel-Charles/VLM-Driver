import requests
import json

URL = "https://samaviajaffery--example-sglang-low-latency-sglang-dev.us-east.modal.direct/v1/chat/completions"

payload = {
    "model": "Qwen/Qwen2.5-VL-7B-Instruct",
    "messages": [
        {
            "role": "user",
            "content": "Return only this JSON: {\"steering\":\"straight\", \"speed\":\"slow\"}"
        }
    ],
    "temperature": 0,
    "max_tokens": 128,
}

response = requests.post(URL, json=payload, timeout=30)
print(response.status_code)
print(json.dumps(response.json(), indent=2))