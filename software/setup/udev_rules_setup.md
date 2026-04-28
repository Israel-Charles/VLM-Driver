# Setting up **udev rules** for connected devices

## Equipment Required

* Fully built vehicle
* Host or pit computer, or
* External monitor/display, HDMI cable, keyboard, mouse

Warning:

This section covers native Linux setup for Ubuntu 20.04+ using ROS 2. If you are using an older Ubuntu release, or encounter dependency or driver conflicts, use a containerized or Docker-based setup instead.

---

## 1. udev Rules Overview

When USB or serial devices are connected, Linux may assign dynamic names such as:

```bash
/dev/ttyACM0
/dev/ttyACM1
/dev/video0
/dev/video1
```

These names can change after reboot, reconnect, or based on device connection order. That creates problems for launch files, scripts, and system services that expect stable device paths.

### Purpose of udev Rules

udev rules allow you to create predictable names, permissions, and symlinks for hardware devices.

Examples:

```bash
/dev/sensors/lidar
/dev/sensors/motor_controller
/dev/sensors/vesc
dev/cameras/realsense
dev/cameras/camera
/dev/input/joypad
```

This is strongly recommended systems with multiple USB peripherals.

---

## Common Rule Structure

Rules typically match one or more device attributes:

* `idVendor`
* `idProduct`
* `serial`
* `KERNEL`
* `SUBSYSTEM`

Then apply actions such as:

* create symlink
* set permissions
* assign group ownership

Example:

```bash
KERNEL=="ttyACM[0-9]*", ATTRS{idVendor}=="1234", ATTRS{idProduct}=="5678", MODE="0666", GROUP="dialout", SYMLINK+="sensors/example_device"
```

---

## Example Rules

### Hokuyo Lidar

```bash
sudo nano /etc/udev/rules.d/99-hokuyo.rules
```

```bash
KERNEL=="ttyACM[0-9]*", ACTION=="add", ATTRS{idVendor}=="15d1", MODE="0666", GROUP="dialout", SYMLINK+="sensors/hokuyo"
```

### VESC

```bash
sudo nano /etc/udev/rules.d/99-vesc.rules
```

```bash
KERNEL=="ttyACM[0-9]*", ACTION=="add", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="5740", MODE="0666", GROUP="dialout", SYMLINK+="sensors/vesc"
```

### Logitech F710 Wireless Gamepad

```bash
sudo nano /etc/udev/rules.d/99-joypad-f710.rules
```

```bash
KERNEL=="js[0-9]*", ACTION=="add", ATTRS{idVendor}=="046d", ATTRS{idProduct}=="c21f", SYMLINK+="input/joypad-f710"
```


### Intel RealSense D435i RGB Video Component

The Intel RealSense D435i presents multiple USB interfaces (camera, IMU, metadata). To get just the RGB video output do the following

```bash
sudo nano /etc/udev/rules.d/99-realsense-d435i-rgb.rules
```

Example rule:

```bash
SUBSYSTEM=="video4linux", ACTION=="add", ATTRS{idVendor}=="8086", ATTRS{idProduct}=="0b3a", ENV{ID_USB_INTERFACE_NUM}=="03", ENV{ID_V4L_CAPABILITIES}==":capture:", SYMLINK+="video/realsense-d435i-rgb"
```

Notes:

* Intel vendor ID is `8086`
* You can obtain the serial number with the RealSense viewer or `lsusb -v`

---

## Apply Rules

After creating or editing rules:

```bash
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Then reconnect the device or reboot.

---

## Verify Devices

```bash
ls /dev/sensors
ls /dev/input
ls /dev/video
```

For USB devices:

```bash
lsusb
```

---

## Troubleshooting

## Find Device Attributes

Use this to inspect matchable values for a device:

```bash
udevadm info --name=/dev/ttyACM0 --attribute-walk
```

or:

```bash
udevadm info --name=/dev/video0 --attribute-walk
```

---

## Watch Real-Time Device Events

```bash
sudo dmesg -w
```

Then plug in the device and observe assigned paths or errors.

---

## Test a Rule

```bash
udevadm test /sys/class/tty/ttyACM0
```

or:

```bash
udevadm test /sys/class/video4linux/video0
```

Use the path corresponding to the device being tested.
