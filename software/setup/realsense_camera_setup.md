# Intel RealSense D435i Setup Guide for Ubuntu 20.04, 22.04, and Newer with ROS 2

This guide explains how to prepare the Intel RealSense D435i camera for use on Ubuntu systems and integrate it with ROS 2.

The D435i includes:

* Stereo depth camera
* RGB camera
* IMU (accelerometer + gyroscope)
* USB 3.0 interface

For best results, always use a USB 3.0 port and quality USB 3.0 cable.

Intel RealSense `librealsense` currently supports Ubuntu 20.04, 22.04, and newer LTS releases.

---

## 1. Hardware Preparation

Before software setup:

Connect D435i directly to USB 3.0 port.

Check detection:

```bash
lsusb
```

You should see Intel device similar to:

```bash
8086:0b3a Intel Corp.
```

---

## 2. Install RealSense SDK (librealsense)

Use official Debian packages whenever possible.

### Method A (Via Debian Packages)

Install dependencies:

```bash
sudo apt update
sudo apt install git wget curl build-essential cmake pkg-config \
libusb-1.0-0-dev libgtk-3-dev libglfw3-dev
```

Register the server's public key:

```bash
# Ensure the directory exists
sudo mkdir -p /etc/apt/keyrings
```

```bash
# Download and dearmor
curl -sSf https://librealsense.realsenseai.com/Debian/librealsenseai.asc | \
gpg --dearmor | sudo tee /etc/apt/keyrings/librealsenseai.gpg > /dev/null
```

Note: The keyring contains both the new RS public key and the Intel public key for old repos, ensuring compatibility with both new and existing packages.

Make sure apt HTTPS support is installed: `sudo apt install apt-transport-https`

Add the server to the list of repositories:

```bash
echo "deb [signed-by=/etc/apt/keyrings/librealsenseai.gpg] https://librealsense.realsenseai.com/Debian/apt-repo `lsb_release -cs` main" | \
sudo tee /etc/apt/sources.list.d/librealsense.list
sudo apt update
```

Install packages:

```bash
sudo apt install librealsense2-utils librealsense2-dev
```

The official RealSense ROS wrapper recommends installing librealsense packages before wrapper setup.

---

### Method B (If Packages Fail - Build from source)

Build from source:

```bash
git clone https://github.com/IntelRealSense/librealsense.git
cd librealsense
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

Use this if newer kernels or package conflicts exist.

---

## 3. Test Camera

Run:

```bash
realsense-viewer
```

Verify:

* RGB image visible
* Depth stream visible
* IMU active
* USB 3 connection detected

---

## 4. Install ROS 2 RealSense Wrapper

Install prebuilt package:

```bash
sudo apt update
sudo apt install ros-$ROS_DISTRO-realsense2-camera
sudo apt install ros-$ROS_DISTRO-realsense2-description
```

Official wrapper packages are available through ROS repositories for supported distros.

---

## 5. Launch Camera in ROS 2

Run:

```bash
ros2 launch realsense2_camera rs_launch.py
```

This starts:

* RGB stream
* Depth stream
* Point cloud (optional)
* IMU
* Camera info topics

---

## 6. Verify ROS Topics

Check:

```bash
ros2 topic list
```

Typical topics:

```bash
/camera/color/image_raw
/camera/depth/image_rect_raw
/camera/imu
/camera/gyro/sample
/camera/accel/sample
/camera/color/camera_info
```

Preview image:

```bash
ros2 run rqt_image_view rqt_image_view
```

---

## 7. Common Problems and Fixes

### Camera Not Found

Use:

```bash
lsusb
```

Try:

* Better USB cable
* Direct motherboard port
* Powered hub
* Reboot after install

---

### USB 2 Instead of USB 3

Symptoms:

* Low FPS
* Missing RGB
* Lag

Fix:

* Replace cable
* Use blue USB port
* Avoid front panel ports

---

### Permission Errors

Run:

```bash
sudo usermod -aG video $USER
newgrp video
```

Then relogin.

---

### Kernel Issues on Newer Ubuntu

Some kernels may need source build or newer librealsense version. Recent releases support many Ubuntu kernels including 20.04 / 22.04 / 24.04 lines.

---

## 8. Performance Tuning

Use lower resolutions if CPU limited:

```bash
depth_module.profile:=640x480x30
rgb_camera.profile:=640x480x30
```

Disable streams not needed:

```bash
enable_color:=false
enable_depth:=true
```

---
