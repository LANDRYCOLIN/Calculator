#!/bin/bash
# 脚本名称：launch.sh
# 功能：在两个终端中启动 ROS 2 包 calculator_2 中的两个节点 calculator_publisher 和 calculator_subscriber

# 设置 ROS 2 环境
cd ~/ros2_ws/src/calculator_2
source install/setup.bash

# 启动 calculator_publisher 节点
echo "在新终端启动节点 calculator_publisher..."
gnome-terminal -- bash -c "ros2 run calculator_2 calculator_publisher; exec bash"

# 启动 calculator_subscriber 节点
echo "在新终端启动节点 calculator_subscriber..."
gnome-terminal -- bash -c "ros2 run calculator_2 calculator_subscriber; exec bash"

# 提示用户
echo "所有节点已启动。两个新终端窗口已打开。"