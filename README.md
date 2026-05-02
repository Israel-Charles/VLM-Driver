# VLM-Driver

A small-scale vehicle built to test Vision-Language
Model (VLM) in making the vehicle autonomous. A single forward-facing RGB camera streams frames into a VLM,
which returns discrete driving decisions (steering label and speed label).
Those labels are mapped to Ackermann steering commands and sent to a VESC
motor controller that drives the car.

The platform follows the open-source F1TENTH (RoboRacer) design philosophy
and is built on a Traxxas chassis with an NVIDIA Jetson ORIN AGX 64GB as the onboard
compute, plus an Intel RealSense D435i camera.

## What this repository contains

```
VLM-Driver/
  firmware/vesc/          VESC motor controller setup guide
  mechanical/assembly/    Step-by-step physical build documentation
  software/
    setup/                Host setup guides (ROS 2, RealSense, Hokuyo, etc.)
    subsystem_ws/         ROS 2 workspace for the vehicle subsystems
                          (drive-by-wire, teleop, sensors, camera)
    autonomy_ws/          ROS 2 workspace for the autonomy stack
                          (VLM driver node, baseline CV, command mapper)
    initial_random_test/  Early standalone scripts for prompting a VLM
    test_input/           Sample images and videos for offline testing
  .gitignore
```

## Hardware

The build is documented in `mechanical/assembly/`. Major components:

- Traxxas 1/10-scale RC car chassis (stock ESC and receiver are removed)
- VESC (Vedder Electronic Speed Controller) for motor and steering servo
- NVIDIA Jetson NX as the onboard computer
- Intel RealSense D435i RGB-D camera (RGB stream is the input to the VLM)
- Hokuyo UST-10LX LiDAR (used by the subsystem stack, optional for VLM-only
  driving)
- LiPO battery, powerboard, Wi-Fi card and antennas
- USB game controller (PS4 DualShock or Logitech F-710) for teleop and as
  a deadman switch

## Software architecture

The software is organized into two ROS 2 (Humble) workspaces.

### Subsystem workspace (`software/subsystem_ws`)

Brings up the lower-level vehicle. Launching `subsystem_stack/bringup.launch.py`
starts:

- `joy` and `joy_teleop` for joystick input
- `ackermann_to_vesc` and `vesc_to_odom` for drive-by-wire and odometry
- `vesc_driver` low-level VESC driver
- `urg_node` Hokuyo LiDAR driver
- `ackermann_mux` to multiplex Ackermann command sources (teleop vs.
  autonomy) with a deadman switch
- `realsense_rgb_node` to publish the D435i RGB stream

Key topics:

| Topic                       | Type                       | Purpose                |
|-----------------------------|----------------------------|------------------------|
| `/drive`                    | `AckermannDriveStamped`    | Autonomy commands in   |
| `/scan`                     | `LaserScan`                | LiDAR scan out         |
| `/odom`                     | `Odometry`                 | Wheel odometry out     |
| `/sensors/imu/raw`          | `Imu`                      | VESC IMU out           |
| `/camera/color/image_raw`   | `Image`                    | RGB camera out         |

A deadman button on the controller must be held for any drive command
(teleop or autonomous) to take effect.

### Autonomy workspace (`software/autonomy_ws`)

Contains the autonomy pipeline:

- `vlm_driver` - main package. Loads a VLM onto the GPU at startup,
  subscribes to the camera image topic, prompts the model on each frame,
  parses the JSON response into steering and speed labels, maps those
  labels to Ackermann commands, and publishes to `/drive`. Models can be
  loaded, unloaded, and switched at runtime via ROS services.
- `baseline_cv` - a non-VLM OpenCV baseline used for comparison against
  the VLM pipeline.
- `command_mapper` - converts discrete driving decisions into
  `AckermannDriveStamped`.
- `vlm_driver_msgs` - custom messages (`DrivingDecisions`,
  `PipelineMetrics`).
- `model_oa` - an offboard option that hosts the VLM on a remote server
  (via `modal deploy`) and queries it over HTTP, useful when the on-device
  GPU is not large enough for the chosen model.

Supported VLMs (configured in `vlm_driver/config/models.yaml`):

- Qwen2.5-VL 3B / 7B
- Qwen3-VL 2B / 4B
- LLaVA 1.5 7B
- LLaVA-OneVision 0.5B
- Llama 3.2 11B Vision (gated, requires accepting the license)

The label-to-command mapping is configurable. Defaults:

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

Sign convention follows ROS REP-103 (positive yaw is left).

## Getting started

### 1. Build the car

Follow the assembly guides in order:

1. `mechanical/assembly/01_component_prep.md`
2. `mechanical/assembly/02_mounting_deck_prep.md`
3. `mechanical/assembly/03_final_assembly.md`

### 2. Configure the VESC

Follow `firmware/vesc/vesc_setup.md`. This installs the VESC Tool, updates
firmware, enables servo output, and runs the motor detection wizard.

> Always place the car on a stand with the wheels free to spin during VESC
> configuration and any motor test.

### 3. Set up the Jetson ORIN AGX

Work through `software/setup/` in roughly this order:

1. `ros2_install.md` - install ROS 2 Humble on Ubuntu 22.04
2. `udev_rules_setup.md` - stable device names for VESC, LiDAR, RealSense
3. `realsense_camera_setup.md` - librealsense and ROS bindings
4. `hokuyo_10lx_setup.md` - LiDAR driver (option to add LiDAR)
5. `nomachine_setup.md` - remote desktop into the Jetson (optional)
6. `tips_and_tricks.md` - troubleshooting and convenience tips

### 4. Build the subsystem workspace

```bash
cd software/subsystem_ws
rosdep update
rosdep install --from-paths src --ignore-src -r -y
colcon build --symlink-install
source install/setup.bash
ros2 launch subsystem_stack bringup.launch.py
```

Verify teleop works (hold the deadman, drive with the joystick) before
moving on to autonomy.

### 5. Build and run the VLM driver

In a second terminal on the Jetson:

```bash
cd software/autonomy_ws
pip install --upgrade transformers accelerate huggingface_hub torch \
                      pillow pyyaml "qwen-vl-utils[decord]" hf_transfer
colcon build --packages-select vlm_driver --symlink-install
source install/setup.bash
```

If you want to use a gated model (for example Llama 3.2 Vision), set a
Hugging Face token in your shell:

```bash
export HF_TOKEN=hf_your_token_here
```

Pre-download the VLMs you want to use:

```bash
ros2 launch vlm_driver download.launch.py
# or just one
ros2 launch vlm_driver download.launch.py only:=qwen2_5_vl_3b
```

Then launch the driver node:

```bash
ros2 launch vlm_driver vlm_driver.launch.py selected_model:=qwen2_5_vl_3b
```

With the subsystem stack also running and the deadman held, the car will
start driving from the camera feed.

See `software/autonomy_ws/src/vlm_driver/README.md` for the full topic and
service interface, runtime model switching, and tuning tips.

## Runtime behavior

1. The VLM is loaded onto the GPU once at startup and kept resident.
2. Each camera frame is stored in a single-slot buffer; older unused
   frames are dropped so inference always runs on the latest image.
3. A timer at `inference_rate_hz` runs the model on the latest frame. If a
   previous inference is still in flight, the tick is skipped rather than
   queued.
4. The model is asked to return JSON with `steering_label`, `speed_label`,
   `confidence`, `emergency_stop`, and `reason`.
5. Labels are mapped to steering degrees and speed m/s. If
   `emergency_stop` is true, speed is forced to zero. If `confidence` is
   below `min_confidence_for_motion`, speed is also forced to zero.
6. The result is published as `AckermannDriveStamped` on `/drive`.


## Safety

- Always test on a stand with wheels free before driving.
- Keep the joystick deadman in reach. Releasing it cuts drive commands to
  the VESC.
- Treat LiPO batteries with respect: never leave them unattended while
  charging, never short the leads, and stop using a pack that bloats,
  smokes, or smells off.
- Cap `speed_map_mps` low (1.0 m/s or less) on first runs and raise it
  only after the model behaves predictably.

## Acknowledgements

The vehicle build follows the open-source F1TENTH (RoboRacer) ecosystem.
The subsystem workspace incorporates upstream packages from F1TENTH and
the broader ROS 2 community, including `ackermann_msgs`, `urg_node`,
`teleop_tools`, `vesc`, `ackermann_mux`, and `cv_bridge`.
