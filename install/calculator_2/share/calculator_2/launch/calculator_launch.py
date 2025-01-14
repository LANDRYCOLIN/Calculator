import launch
from launch import LaunchDescription
from launch_ros.actions import Node  # 导入 Node 组件

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='calculator_2',
            executable='calculator_publisher',
            name='calculator_publisher',
            output='screen'
        ),
        Node(
            package='calculator_2',
            executable='calculator_subscriber',
            name='calculator_subscriber',
            output='screen'
        ),
    ])
