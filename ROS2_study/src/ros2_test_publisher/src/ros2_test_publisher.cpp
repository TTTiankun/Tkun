//创建一个发布者的流程
/*
导入接口的类型
使用this->create_publisher创建发布者
编写发布的逻辑
*/
//导入接口的类型
#include"std_msgs/msg/u_int32.hpp"
#include"std_msgs/msg/string.hpp"
#include"rclcpp/rclcpp.hpp"
#include<iostream>
#include <locale>
//创建一个发布者的类
class MinimalPublisher : public rclcpp::Node
{

public:
    
    //构造函数
    MinimalPublisher(std::string name):Node(name)
    {
        //打印消息
        RCLCPP_INFO(this->get_logger(), "%s has been started",name.c_str());
        //创建一个发布者
        publisher = this->create_publisher<std_msgs::msg::String>("topic_name",10);//创建一个发布者，话题名字为topic_name，缓冲区大小为10
        //发布话题的名字非常重要，订阅者订阅的话题名字必须和发布者发布的话题名字一致！！！！！
        //发布话题的类型也非常重要，订阅者订阅的话题类型必须和发布者发布的话题类型一致！！！！！
        //创建一个定时器，500ms触发一次，定期发布
        timer_=this->create_wall_timer(std::chrono::milliseconds(500),std::bind(&MinimalPublisher::timer_callback,this));
        //bind函数的作用是将timer_callback函数绑定到this指针上
        //chrono::milliseconds(500)表示500ms c++11的写法
    }

private:
   
    //创建一个回调函数
    void timer_callback() 
    {
        //编写发布的逻辑
        std_msgs::msg::String messages;//创建一个消息
        messages.data = "Hello World";//赋值
        //打印消息
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", messages.data.c_str());
        //发布消息
        publisher->publish(messages);
    }

    //声明一个发布者指针
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
    //声明一个定时器指针
    rclcpp::TimerBase::SharedPtr timer_;
    
};

int main(int argc, char * argv[])
{
    //初始化ROS2
    rclcpp::init(argc, argv);
    //创建一个发布者
    auto node = std::make_shared<MinimalPublisher>("ROS2_test_publisher");
    //创建一个回调函数
    rclcpp::spin(node);
    //关闭ROS2
    rclcpp::shutdown();
    return 0;
}

