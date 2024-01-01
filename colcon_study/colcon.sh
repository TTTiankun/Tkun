#!/bin/bash

#这个文档是关于一些colcon的简答学习

#安装colcon
sudo apt install python3-colcon-common-extensions

#创建一个工作区文件夹
mkdir test && cd test

#下载一个ros2的测试源码
git clone https://github.com/ros2/examples.git src/examples -b humble

#编译工程
colcon build

#文件结构
├── colcon.sh
└── test
    ├── build
    │   ├── COLCON_IGNORE
    │   ├── examples_rclcpp_minimal_action_client
    │   ├── examples_rclcpp_minimal_action_server
    │   ├── examples_rclcpp_minimal_client
    │   ├── examples_rclcpp_minimal_composition
    │   ├── examples_rclcpp_minimal_publisher
    │   ├── examples_rclcpp_minimal_service
    │   ├── examples_rclcpp_minimal_subscriber
    │   ├── examples_rclcpp_minimal_timer
    │   ├── examples_rclcpp_multithreaded_executor
    │   ├── examples_rclpy_executors
    │   ├── examples_rclpy_minimal_action_client
    │   ├── examples_rclpy_minimal_action_server
    │   ├── examples_rclpy_minimal_client
    │   ├── examples_rclpy_minimal_publisher
    │   ├── examples_rclpy_minimal_service
    │   └── examples_rclpy_minimal_subscriber
    ├── install
    │   ├── COLCON_IGNORE
    │   ├── examples_rclcpp_multithreaded_executor
    │   ├── examples_rclpy_executors
    │   ├── examples_rclpy_minimal_action_client
    │   ├── examples_rclpy_minimal_action_server
    │   ├── examples_rclpy_minimal_client
    │   ├── examples_rclpy_minimal_publisher
    │   ├── examples_rclpy_minimal_service
    │   ├── examples_rclpy_minimal_subscriber
    │   ├── local_setup.bash
    │   ├── local_setup.ps1
    │   ├── local_setup.sh
    │   ├── _local_setup_util_ps1.py
    │   ├── _local_setup_util_sh.py
    │   ├── local_setup.zsh
    │   ├── setup.bash
    │   ├── setup.ps1
    │   ├── setup.sh
    │   └── setup.zsh
    ├── log
    │   ├── build_2023-12-29_23-25-59
    │   ├── COLCON_IGNORE
    │   ├── latest -> latest_build
    │   └── latest_build -> build_2023-12-29_23-25-59
    └── src
        └── examples

#运行一个自己编写的节点

#进入安装目录
source install/setup.bash

#运行一个ros2的节点 订阅节点
ros2 run examples_rclcpp_minimal_subscriber subscriber_member_function

#运行一个ros2的节点 发布节点(要再开一个终端)
ros2 run examples_rclcpp_minimal_publisher publisher_member_function

#只编译一个包
#用法：colcon build --packages-select 包名
colcon build --packages-select examples_rclcpp_minimal_publisher

#编译多个包
#用法：colcon build --packages-select 包名1 包名2
colcon build --packages-select examples_rclcpp_minimal_publisher examples_rclcpp_minimal_subscriber

#不编译测试单元
#用法：colcon build --packages-select 包名 --cmake-args -DCMAKE_BUILD_TYPE =Release
colcon build --packages-select examples_rclcpp_minimal_publisher --cmake-args -DCMAKE_BUILD_TYPE=Release

#运行编译包的测试单元
#用法：colcon test --packages-select 包名
colcon test --packages-select examples_rclcpp_minimal_publisher

#允许用过改变src目录下的部分文件来改变install
colcon build --symlink-install 

#可以进一步学习colocn的一些用法 查看官方文档网址：https://colcon.readthedocs.io/en/released/user/quick-start.html
#或者通过指令：colcon --help
