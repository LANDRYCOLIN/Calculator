import launch
from launch import LaunchDescription
from launch.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='calculator_2', 
            executable='calculator_publisher',
            name='calculator_publisher_node', 
            output='screen'
        ),
        Node(
            package='calculator_2',
            executable='calculator_subscriber',
            name='calculator_subscriber_node',
            output='screen'
        )
    ])
