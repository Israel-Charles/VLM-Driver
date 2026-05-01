import requests
import base64

def analyze_driving_image(image_path, prompt="Describe this driving scene. What hazards are present?"):
    with open(image_path, "rb") as f:
        image_data = base64.b64encode(f.read()).decode("utf-8")

    response = requests.post(
        "http://localhost:11434/api/generate",
        json={
            "model": "qwen2.5vl:7b",
            "prompt": prompt,
            "images": [image_data],
            "stream": False
        }
    )

    # print(response.json())  
    return response.json()["response"]

result = analyze_driving_image("driving_image.png")
print(result)