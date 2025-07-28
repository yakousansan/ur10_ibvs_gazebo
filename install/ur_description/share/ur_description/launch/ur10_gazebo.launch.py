from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
import os
import xacro
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition

def generate_launch_description():
    # URDF/XACRO文件路径
    share_dir = get_package_share_directory('ur_description')
    xacro_file = os.path.join(share_dir, 'urdf', 'ur10.urdf.xacro')
    robot_description_config = xacro.process_file(xacro_file)
    robot_description = robot_description_config.toxml()

    # 控制器配置文件路径
    controllers_yaml = os.path.join(share_dir, 'config', 'ur10_gazebo_controllers.yaml')
    # 设置仿真时间参数
    use_sim_time = {'use_sim_time': True}
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        name='use_sim_time',
        default_value='True',
        description='Use simulation (Gazebo) clock if true')
    # 启动Gazebo仿真环境
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory('gazebo_ros'), 'launch', 'gazebo.launch.py')
        ]),
        launch_arguments={
            'world': os.path.join(share_dir, 'worlds', 'gazebo_world.world'),
            'use_sim_time': 'true'
            }.items()
    )

    # 机器人状态发布节点
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description}, use_sim_time]
    )

    # 在Gazebo中生成机器人实体
    # spawn_entity = Node(
    #     package='gazebo_ros',
    #     executable='spawn_entity.py',
    #     arguments=[
    #         '-entity', 'ur10_robot',
    #         '-topic', 'robot_description',
    #         '-x', '0.0',  
    #         '-y', '0.0',  
    #         '-z', '0.0',  
    #         '-Y', '0.0',  
    #     ],
    #     output='screen'
    # )
    
    # 启动controller_manager
    controller_manager = Node(
        package='controller_manager',
        executable='ros2_control_node',
        parameters=[
            controllers_yaml, 
            use_sim_time
            ],
        output='screen'
    )

    # 加载关节状态广播器
    spawn_joint_state_broadcaster = Node(
        package='controller_manager',
        executable='spawner',
        arguments = [
            "joint_state_broadcaster",
            '--controller-manager', 
            '/controller_manager'
        ],
        output='screen'
    )

    # 速度控制器
    spawn_velocity_controller = Node(
        package='controller_manager',
        executable='spawner',
        arguments=['--controller-manager', 
                   '/controller_manager', 
                   'ur_joint_velocity_controller'
        ],
        output='screen'
    )

    # 获取相机彩色/深度图
    camera_image_node = Node(
        package='camera_image',
        executable='camera_image',
        name='camera_image_node', 
        output='screen',           
        parameters=[{'use_sim_time': True}]
    )
    # 相机内参获取及角点检测
    ibvs_node = Node(
        package='ibvs',
        executable='ibvs',
        name='ibvs_node', 
        output='screen',           
        parameters=[{'use_sim_time': True}]
    )

    return LaunchDescription([
        declare_use_sim_time_cmd,
        gazebo,
        robot_state_publisher,
        # spawn_entity,
        controller_manager,
        spawn_joint_state_broadcaster,
        spawn_velocity_controller,
        #camera_image_node,
        ibvs_node
    ])
