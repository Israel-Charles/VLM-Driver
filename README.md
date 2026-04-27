# VLM-Driver

Run the model with: 
```modal deploy model.py```

Stop it with:
```modal app stop example-sglang-low-latency```

For Ollama,
Change [PUBLIC_IP] to the actual ip before running ollama_query_vlm.sh
To make the script executable:

```
chmod +x ollama_query_vlm.sh
```
Then run
```
./ollama_query_vlm.sh ./image.png
```
./image.png is the name of the image you want to send. The path here assumes the image is in the same directory you're currently in.