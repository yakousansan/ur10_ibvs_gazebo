# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

ROS2 workspace for Image-Based Visual Servoing (IBVS) on a UR10 robotic arm in Gazebo simulation. An eye-in-hand Intel RealSense D455 camera detects rectangle corners in the image and drives them toward target positions by computing and sending joint velocity commands.

## Build & Run

```bash
colcon build
source install/setup.bash
ros2 launch ibvs ur10_gazebo.launch.py
```

The launch file starts Gazebo, robot_state_publisher, ros2_control (velocity controller), ibvs_node, and ik_node.

## Architecture

Four packages under `src/`:

- **ibvs** — Core visual servoing node. Subscribes to camera image + camera info, detects rectangle corners (OpenCV), computes camera velocity (ViSP), converts to joint velocities via Jacobian pseudoinverse. Publishes to `/ur_joint_velocity_controller/commands`.
- **ik** — Jacobian computation node. Uses Pinocchio to compute 6×6 Jacobian from `/joint_states`, publishes as flat 36-element `Float64MultiArray` on `/jacobian_matrix`.
- **ur_description** — UR10 URDF (xacro), Gazebo world, controller config (`ur_joint_velocity_controller` and `joint_state_broadcaster`).
- **camera_image** — Debug utility to display camera images in OpenCV windows (disabled in launch file).

Key data flow: Gazebo → camera images → ibvs_node (corner detection → ViSP velocity → TF2 frame transform → Jacobian pseudoinverse) → joint velocities → ros2_control. The ik_node runs independently, publishing the Jacobian at 30Hz.

Convergence threshold: RMSE of feature error < 0.01 (normalized image coordinates). The system logs error and joint velocity data to CSV under `src/ibvs/data/`.

## Key Dependencies (External C++ Libraries)

- **ViSP** — Visual servo control law (`vpServo`, `vpFeaturePoint`, `vpCameraParameters`)
- **Pinocchio** — Kinematics and Jacobian computation from URDF
- **Eigen3** — Linear algebra (pseudoinverse, matrix ops)
- **OpenCV** — Image processing and corner detection

## Important Notes

- The Jacobian interface between `ik` and `ibvs` nodes is a flat 36-element array reshaped to 6×6 — this is by design (see `src/ik/src/ik.md`).
- The `depth_callback` in ibvs.cpp is a stub — depth-based features are not yet implemented.
- Gravity is disabled on all UR10 links in Gazebo to isolate control behavior.
- Camera TF frame is `kinect_link`, robot base frame is `base_link`.
- CSV data paths in ibvs.cpp are hardcoded to `/home/p/ws_demo2/src/ibvs/data/`.
