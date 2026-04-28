#!/bin/bash
echo "{\"model\": \"qwen2.5vl:7b\", \"prompt\": \"What do you see?\", \"stream\": false, \"images\": [\"$(base64 -i "$1")\"]}" > /tmp/request.json
curl http://[PUBLIC_IP_GOES_HERE]:11434/api/generate -d @/tmp/request.json