//创建一个订阅者的流程
/*
1.导入订阅的话题的接口类型
2.创建订阅回调函数
3.声明并创建订阅者
4.编写订阅回调处理逻辑 
*/

//导入接口的类型
#include"rclcpp/rclcpp.hpp"
#include"std_msgs/msg/u_int32.hpp"
#include"std_msgs/msg/string.hpp"
#include<iostream>

//表示预期函数的两个参数
using std::placeholders::_1;
using std::placeholders::_2;

//创建一个订阅者的类
class MinimalSubscriber : public rclcpp::Node
{
public:
    //构造函数，有一个参数，表示节点的名字
    MinimalSubscriber(std::string name):Node(name)
    {
        //打印消息
        RCLCPP_INFO(this->get_logger(), "%s has been started",name.c_str());
        //创建一个订阅者
        subscription = this->create_subscription<std_msgs::msg::String>("topic_name",10,std::bind(&MinimalSubscriber::topic_callback,this,_1));
    }

private:

    //声明订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription;

    //创建一个回调函数
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) {
        //编写订阅的逻辑
        double speed = 0.0f;//创建一个变量用来记录接收速度
        if(msg->data == "Hello World"){
            speed = 0.2f;
        }
        //打印消息
        RCLCPP_INFO(this->get_logger(), "I heard: '%s',the speed is %f", msg->data.c_str(),speed);
    }
};

int main(int argc, char * argv[]){
    //初始化ROS2
    rclcpp::init(argc, argv);
    //创建一个订阅者
    auto node = std::make_shared<MinimalSubscriber>("ROS2_test_subscriber");
    //创建一个回调函数
    rclcpp::spin(node);
    //关闭ROS2
    rclcpp::shutdown();
    return 0;
}