from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros2_test_client',# 替换为你的第一个节点的包名
            executable='ros2_test_client',  # 替换为你的第一个节点的可执行文件名
            name='ros2_test_client',# 替换为你的第一个节点的名字
            output='screen',#在屏幕上输出
        ),
        Node(
            package='ros2_test_service',# 替换为你的第二个节点的包名
            executable='ros2_test_service',  # 替换为你的第二个节点的可执行文件名
            name='ros2_test_service',# 替换为你的第二个节点的名字
            output='screen',
        ),
    ])
