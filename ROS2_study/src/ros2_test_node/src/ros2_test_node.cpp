//编写一个ros2节点的步骤
/*
1.导入库文件
2.初始化客户端库
3.创建节点对象
4.spin循环节点
5.关闭客户端库
*/

#include <rclcpp/rclcpp.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    //初始化客户端库
    rclcpp::init(argc, argv);
    //创建节点对象
    auto node = std::make_shared<rclcpp::Node>("ros2_test_node");
    //打印信息
    RCLCPP_INFO(node->get_logger(), "Hello ROS2");
    //spin循环节点
    rclcpp::spin(node);
    //关闭客户端库
    rclcpp::shutdown();
    return 0;
}