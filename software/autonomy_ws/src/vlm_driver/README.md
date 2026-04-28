# vlm_driver

ROS 2 (Humble) package that uses a Vision-Language Model to drive a small
autonomous vehicle. A node subscribes to a camera image topic, sends each
frame to a selected VLM with an obstacle-avoidance prompt, parses the JSON
output, maps the labels to steering and speed, and publishes
`AckermannDriveStamped` to `/drive`.

The model is loaded into GPU once at startup and kept resident so subsequent
frames have low load overhead. Models can be loaded, unloaded, and switched
at runtime via services.


## Supported models

Listed in `config/models.yaml`. Out of the box:

- Qwen/Qwen2.5-VL-7B-Instruct
- Qwen/Qwen2.5-VL-3B-Instruct
- Qwen/Qwen3-VL-2B-Instruct
- Qwen/Qwen3-VL-4B-Instruct
- llava-hf/llava-1.5-7b-hf
- llava-hf/llava-onevision-qwen2-0.5b-ov-hf
- meta-llama/Llama-3.2-11B-Vision-Instruct  (gated, need to accept license to download)


## Requirements

- ROS 2 Humble on Ubuntu 22.04
- NVIDIA GPU with CUDA-capable PyTorch (Jetson Orin or a desktop GPU)
- Python 3.10
- ~80-90 GB free disk if you download every model in the registry

Python deps (install into the same Python ROS uses):

```
pip install --upgrade transformers accelerate huggingface_hub torch \
                       pillow pyyaml "qwen-vl-utils[decord]" hf_transfer
```


## Build

From your colcon workspace:

```
cd ~/ros2_ws
colcon build --packages-select vlm_driver --symlink-install
source install/setup.bash
```

`--symlink-install` lets you edit YAML and Python without rebuilding.


## Hugging Face token

A token is only required for gated models (Llama 3.2 Vision) but it also
removes the unauthenticated rate-limit warning on public models.

The package looks for a token in this order:

1. ROS parameter `hf_token` (or `--hf-token` for the downloader)
2. Environment variable `HF_TOKEN`
3. Environment variable `HUGGING_FACE_HUB_TOKEN`
4. Token saved by `huggingface-cli login`

Recommended: keep the token out of the repo. Set it once in your shell:

```
echo 'export HF_TOKEN=hf_your_token_here' >> ~/.bashrc
source ~/.bashrc
```

or run `huggingface-cli login` once.


## Download models

Edit `config/models.yaml` and set `model_root` to a folder with enough free
space, then run:

```
ros2 launch vlm_driver download.launch.py
```

Useful overrides:

```
# only one model
ros2 launch vlm_driver download.launch.py only:=qwen2_5_vl_3b

# different output folder
ros2 launch vlm_driver download.launch.py model_root:=/path/to/models

# pass a token explicitly (not committed)
ros2 launch vlm_driver download.launch.py hf_token:=hf_xxx
```

Already-downloaded models are skipped (presence of `config.json` in the
target folder is the cache check).


## Run the driver node

Make sure your camera node is publishing first, then:

```
ros2 launch vlm_driver vlm_driver.launch.py
```

Switch which model is loaded at startup:

```
ros2 launch vlm_driver vlm_driver.launch.py selected_model:=qwen2_5_vl_3b
```

Override the YAML at launch time:

```
ros2 launch vlm_driver vlm_driver.launch.py params:=/path/to/my_params.yaml
```


## Topics

Subscribed:

| Topic                      | Type             | Notes                       |
|----------------------------|------------------|-----------------------------|
| `/camera/color/image_raw`  | `sensor_msgs/Image` | RGB camera, configurable |

Published:

| Topic    | Type                                | Notes                  |
|----------|-------------------------------------|------------------------|
| `/drive` | `ackermann_msgs/AckermannDriveStamped` | Steering and speed   |


## Services

All under the node's namespace (`/vlm_driver_node` by default):

| Service           | Type             | Purpose                                  |
|-------------------|------------------|------------------------------------------|
| `~/load_model`    | `std_srvs/Trigger` | Load the currently selected model      |
| `~/unload_model`  | `std_srvs/Trigger` | Free the model from GPU                |
| `~/switch_model`  | `std_srvs/Trigger` | Read `selected_model` param and reload |

Switch model at runtime:

```
ros2 param set /vlm_driver_node selected_model qwen3_vl_2b
ros2 service call /vlm_driver_node/switch_model std_srvs/srv/Trigger
```

Free the GPU:

```
ros2 service call /vlm_driver_node/unload_model std_srvs/srv/Trigger
```


## Configuration

Two YAML files under `config/`:

- `models.yaml` - registry of models. Each entry has a `repo_id`, a local
  `subfolder`, a `family` (used to pick the right loader), and an `enabled`
  flag. Also defines `model_root`.
- `vlm_driver.yaml` - runtime parameters: which model to load, topic names,
  inference rate, prompt, label-to-value mappings, fallback labels,
  confidence threshold, and the HF token (leave empty in the file).

Label mappings (defaults):

```
steering_map_deg:
  hard_left: 30.0
  left: 20.0
  slight_left: 10.0
  straight: 0.0
  slight_right: -10.0
  right: -20.0
  hard_right: -30.0

speed_map_mps:
  stop: 0.0
  slow: 1.0
  medium: 2.0
  fast: 3.0
```

Sign convention follows ROS REP-103 (positive yaw is left). Verify on the
bench before driving.


## How it works

1. On startup, the node reads `models.yaml`, resolves the local path of the
   selected model, and loads it onto the GPU. If the model is missing on
   disk it is downloaded automatically.
2. Each camera frame is stored in a single-slot buffer. Old frames are
   dropped (`drop_stale_frames: true`).
3. A timer at `inference_rate_hz` pulls the latest frame, converts it to a
   PIL image, and runs `model.generate(...)` with the configured prompt.
   If a previous inference is still running, the tick is skipped instead of
   queued.
4. The model output is parsed loosely as JSON. Recognized fields:
   `steering_label`, `speed_label`, `confidence`, `emergency_stop`, `reason`.
5. Labels are mapped to steering degrees and speed m/s. If `emergency_stop`
   is true, speed is forced to `stop`. If `confidence` is below
   `min_confidence_for_motion`, speed is forced to 0.
6. The result is published as `AckermannDriveStamped` on `/drive`.


## Real-time notes

`inference_rate_hz` is a cap, not a guarantee. Actual throughput depends on
model size and hardware:

- 7B models on Jetson Orin: roughly 0.3 to 1 Hz
- 2B - 4B models on Jetson Orin: roughly 1 to 3 Hz
- 0.5B (LLaVA-OneVision): potentially 5 Hz or above

Tune the cap so it matches what the model can sustain. If generation takes
longer than the period, the timer simply skips the next tick.


## Quick health checks

```
# camera arriving?
ros2 topic hz /camera/color/image_raw

# drive commands going out?
ros2 topic hz /drive
ros2 topic echo /drive

# what params are loaded?
ros2 param dump /vlm_driver_node
```