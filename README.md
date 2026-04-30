# IBVS - Image-Based Visual Servoing for UR10

<p align="center">
  <img src="docs/ur.png" width="600" alt="UR10 IBVS Gazebo Simulation">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/ROS2-Humble-blue" alt="ROS2 Humble">
  <img src="https://img.shields.io/badge/Gazebo-Simulation-green" alt="Gazebo">
  <img src="https://img.shields.io/badge/License-MIT-yellow" alt="License">
</p>

<p align="center">
  <a href="README_zh-CN.md">中文</a> | <b>English</b>
</p>

---

### Overview

This project is an **Eye-in-Hand Image-Based Visual Servoing (IBVS)** system built on **ROS2 Humble**, designed to control a **Universal Robots UR10** 6-DOF robotic arm in a **Gazebo** simulation environment.

An Intel RealSense D455 depth camera is mounted on the robot's end-effector. The system detects four corners of a rectangular target in the camera image, computes the error between current and desired features, generates camera velocity commands using the ViSP visual servoing library, and converts them to joint velocities through TF2 coordinate transforms and Jacobian pseudoinverse computation. The joint velocities are then sent to a ros2 velocity controller, driving the robot until the target corners converge to their desired positions in the image.

### System Architecture

```
                  Gazebo Simulation
                  ┌──────────────────────────────────────────────┐
                  │   UR10 Robot + D455 Camera + Target Object   │
                  └────┬──────────┬──────────────┬──────────────┘
                       │          │              │
            /rgb/image_raw  /joint_states  /rgb/camera_info
                       │          │              │
                       ▼          │              │
              ┌────────────────┐  │              │
              │   ibvs_node    │◄─┘              │
              │                │◄────────────────┘
              │  · Corner detection (OpenCV)     │
              │  · Visual servo (ViSP)           │
              │  · Camera→Base velocity (TF2)    │
              │  · Base→Joint velocity (J⁻¹)    │
              └───────┬────────┘  ▲
                      │           │
 /ur_joint_velocity   │   /jacobian_matrix (6×6)
 _controller/commands │           │
                      │    ┌──────┴────────┐
                      │    │   ik_node     │
                      │    │               │
                      │    │  · Pinocchio  │
                      │    │    FK         │
                      │    │  · Jacobian   │
                      │    │  · EE Pose    │
                      │    └───────────────┘
                      ▼
            ┌─────────────────────┐
            │   ros2_control      │
            │  (velocity ctrl)    │
            └─────────────────────┘
```

**Data flow:**

1. Gazebo publishes simulated camera images and joint states
2. `ibvs_node` receives the RGB image, detects rectangle corners via OpenCV (Canny edge detection + contour finding + polygon approximation), and converts them to ViSP feature points using camera intrinsics from `/rgb/camera_info`
3. `ibvs_node` computes the visual error between detected corners and target positions (4 corners near image center). If RMSE > 0.01, ViSP computes a 6-DOF camera velocity command
4. TF2 provides the `kinect_link` to `base_link` transform, converting camera-frame velocity to base-frame velocity
5. `ik_node` continuously computes and publishes the 6×6 Jacobian matrix using Pinocchio at 30Hz
6. `ibvs_node` uses the Jacobian pseudoinverse to convert base-frame velocity into 6 joint velocities
7. Joint velocities are published to `/ur_joint_velocity_controller/commands`

### Features

- **Rectangle corner detection** — OpenCV-based Canny edge detection and contour analysis, automatically identifies and sorts rectangle corners clockwise
- **Visual servo control** — Classic Eye-in-Hand IBVS control law using ViSP (λ=0.3)
- **Real-time Jacobian computation** — Pinocchio dynamics library loads the URDF model and computes the 6×6 Jacobian matrix in real-time
- **Coordinate transforms** — TF2-based velocity transformation from camera frame to base frame
- **Experiment data logging** — Automatic CSV recording of feature errors and joint velocities for offline analysis
- **Convergence detection** — Servo automatically stops when feature error RMSE drops below 0.01

### Dependencies

| Category | Dependencies |
|----------|-------------|
| **ROS2** | ROS2 Humble, rclcpp, std_msgs, sensor_msgs, geometry_msgs, cv_bridge, tf2_ros, image_transport, controller_manager |
| **Simulation** | Gazebo, gazebo_ros2_control, robot_state_publisher, xacro |
| **C++ Libraries** | OpenCV, ViSP (Visual Servoing Platform), Eigen3, Pinocchio |

### Installation & Build

**1. Install ROS2 Humble**

Refer to the [ROS2 official documentation](https://docs.ros.org/en/humble/Installation.html).

**2. Install external dependencies**

```bash
# OpenCV (usually included with ROS2)
sudo apt install libopencv-dev

# ViSP
sudo apt install libvisp-dev

# Eigen3
sudo apt install libeigen3-dev

# Pinocchio
sudo apt install robotpkg-py3*-pinocchio
```

**3. Build the workspace**

```bash
cd ~/ws_demo2
colcon build
source install/setup.bash
```

### Usage

**Launch the full simulation system:**

```bash
ros2 launch ibvs ur10_gazebo.launch.py
```

This command sequentially starts:
1. Gazebo simulation environment (with UR10 robot and target object)
2. `robot_state_publisher` (publishes robot TF)
3. `ros2_control_node` (controller manager)
4. `joint_state_broadcaster` (joint state broadcaster)
5. `ur_joint_velocity_controller` (velocity controller)
6. `ibvs_node` (visual servoing node)
7. `ik_node` (Jacobian computation node)

**Enable debug camera view (optional):**

Uncomment `camera_image_node` in `src/ibvs/launch/ur10_gazebo.launch.py` to enable OpenCV image display windows.

### Package Structure

```
src/
├── ibvs/                           # Core visual servoing package
│   ├── include/ibvs.h              # VisualServoInit class declaration
│   ├── src/ibvs.cpp                # Full IBVS implementation (~712 lines)
│   ├── launch/ur10_gazebo.launch.py # System launch file
│   └── data/                       # CSV experiment data
│       ├── error_data/             # Feature error logs
│       └── joint_vel_data/         # Joint velocity logs
│
├── ik/                             # Jacobian computation package
│   ├── include/ik.h                # IKNode class declaration
│   ├── src/ik.cpp                  # Pinocchio Jacobian implementation (~246 lines)
│   └── src/ik_test.cpp             # Standalone test program
│
├── ur_description/                 # UR10 robot description package
│   ├── urdf/ur10.urdf.xacro        # UR10 + D455 camera URDF
│   ├── config/ur10_gazebo_controllers.yaml # Controller configuration
│   ├── worlds/gazebo_world.world   # Gazebo simulation world
│   └── meshes/ur10/                # 3D model files (DAE/STL)
│
└── camera_image/                   # Camera image debug utility
    └── src/camera_image.cpp        # OpenCV image display node
```

### ROS2 Topics & Controllers

**Subscribed topics:**

| Topic | Message Type | Description |
|-------|-------------|-------------|
| `/rgb/image_raw` | `sensor_msgs/Image` | RGB camera image |
| `/depth/image_raw` | `sensor_msgs/Image` | Depth image (not yet used) |
| `/rgb/camera_info` | `sensor_msgs/CameraInfo` | Camera intrinsics |
| `/joint_states` | `sensor_msgs/JointState` | Joint states |
| `/jacobian_matrix` | `std_msgs/Float64MultiArray` | 6×6 Jacobian matrix (36 elements) |

**Published topics:**

| Topic | Message Type | Description |
|-------|-------------|-------------|
| `/ur_joint_velocity_controller/commands` | `std_msgs/Float64MultiArray` | 6 joint velocity commands |

**Controller configuration:**

- `ur_joint_velocity_controller` — `velocity_controllers/JointGroupVelocityController`, controls all 6 joints of UR10
- `joint_state_broadcaster` — `joint_state_broadcaster/JointStateBroadcaster`

### Parameters & Configuration

| Parameter | Value | Description |
|-----------|-------|-------------|
| Servo gain λ | 0.3 | ViSP visual servo control law gain |
| Convergence threshold | RMSE < 0.01 | Feature error in normalized image coordinates |
| Camera resolution | 640 × 480 | D455 simulated camera resolution |
| Camera frame rate | 30 Hz | Gazebo simulated camera publish rate |
| Jacobian publish rate | 30 Hz | ik_node computation and publish rate |
| Target corners | (320±100, 240±100) | 4 desired corners near image center (pixel coordinates) |

### Experiment Data

CSV files are automatically generated in `src/ibvs/data/` during runtime:

- **`error_data/`** — Records per-frame feature error and RMSE
- **`joint_vel_data/`** — Records per-frame 6 joint velocity commands

File naming format: `{type}_{MMDD}_{HHmmss}.csv`

### Acknowledgments

- [ViSP](https://visp.inria.fr/) — Visual Servoing Platform
- [Pinocchio](https://stack-of-tasks.github.io/pinocchio/) — Rigid body dynamics library
- [Universal Robots ROS2 Driver](https://github.com/UniversalRobots/Universal_Robots_ROS2_Driver) — UR10 model reference

### License

This project is licensed under the MIT License.
