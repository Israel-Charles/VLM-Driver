import requests
import base64
from PIL import Image
import io

API_URL = "" #obviously change this as needed
IMAGE_PATH = "" #same as above

image = Image.open(IMAGE_PATH).convert("RGB")
buffer = io.BytesIO()
image.save(buffer, format="JPEG")
b64 = base64.b64encode(buffer.getvalue()).decode("utf-8")

response = requests.post(
    f"{API_URL}/v1/chat/completions",
    json={
        "model": "Qwen/Qwen2.5-VL-7B-Instruct",
        "messages": [{"role": "user", "content": [
            {"type": "image_url", "image_url": {"url": f"data:image/jpeg;base64,{b64}"}},
            {"type": "text", "text": "Describe this image."}
        ]}],
        "max_tokens": 200,
    },
    timeout=60,
)

print(f"Status code: {response.status_code}")
print(f"Response text: {response.text}")