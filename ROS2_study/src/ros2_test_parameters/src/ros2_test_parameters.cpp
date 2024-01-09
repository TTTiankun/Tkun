#include<chrono>
#include"rclcpp/rclcpp.hpp"
#include<iostream>
/*
常用函数：

1.声明和初始化一个参数 declare_parameter
2.通过参数姓名获取阐述的描述 describe_parameter(name)
3.通过参数的名字获取一个参数 get_parameter
4.设置参数的值 set_parameter
*/

class Parameters_test01:public rclcpp::Node{
public:
//构造函数，有一个参数的节点名称
explicit Parameters_test01(std::string name):Node(name){
    //打印节点名称
    RCLCPP_INFO(this->get_logger(),"%s has started already",this->get_name());
    this->declare_parameter("rcl_log_level",0);//声明并初始化一个参数
    this->get_parameter("rcl_log_level",log_level);
    //设置日志级别
    this->get_logger().set_level((rclcpp::Logger::Level)log_level);//设置日志级别 含义：设置日志级别为log_level
    using namespace std::chrono_literals;
    timer = this->create_wall_timer(1s,std::bind(&Parameters_test01::timer_callback,this));//创建定时器 含义：每隔1s调用一次timer_callback函数
}
private:
    void timer_callback(){
        this->get_parameter("rcl_log_level",log_level); //获取参数
        //设置日志级别
        this->get_logger().set_level((rclcpp::Logger::Level)log_level);//设置日志级别 含义：设置日志级别为log_level
        std::cout<<"----------------------------------------------------------"<<std::endl;

        RCLCPP_DEBUG(this->get_logger(),"我是DEBUG级别的日志");
        RCLCPP_INFO(this->get_logger(),"我是INFO级别的日志");
        RCLCPP_WARN(this->get_logger(),"我是WARN级别的日志");
        RCLCPP_ERROR(this->get_logger(),"我是ERROR级别的日志");
        RCLCPP_FATAL(this->get_logger(),"我是FATAL级别的日志");
    }
    rclcpp::TimerBase::SharedPtr timer; //创建定时器
    int log_level; //日志级别
};


int main(){
    rclcpp::init(0,nullptr); //初始化ROS2
    auto node = std::make_shared<Parameters_test01>("parameters_test01"); //创建节点
    rclcpp::spin(node); //节点开始运行
    rclcpp::shutdown(); //关闭ROS2
    return 0;
}