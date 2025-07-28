from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution, Command
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue
import os

def generate_launch_description():
    # 直接指定ur10.urdf文件路径
    urdf_file = PathJoinSubstitution([
        FindPackageShare("ur_description"),
        "urdf",
        "ur10.p.urdf" 
    ])

    # 读取URDF文件内容
    robot_description_content = Command(['cat ', urdf_file])
    robot_description = {
        "robot_description": ParameterValue(value=robot_description_content, value_type=str)
    }

    # RViz配置文件路径
    rviz_config_file = PathJoinSubstitution([
        FindPackageShare("ur_description"),
        "rviz",
        "view_robot.rviz"
    ])

    # 定义要启动的节点
    nodes_to_start = [
        # 关节状态发布器
        Node(
            package="joint_state_publisher_gui",
            executable="joint_state_publisher_gui",
        ),
        # 机器人状态发布器
        Node(
            package="robot_state_publisher",
            executable="robot_state_publisher",
            output="both",
            parameters=[robot_description],
        ),
        # RViz可视化
        Node(
            package="rviz2",
            executable="rviz2",
            name="rviz2",
            output="log",
            arguments=["-d", rviz_config_file],
        ),
    ]

    return LaunchDescription(nodes_to_start)
