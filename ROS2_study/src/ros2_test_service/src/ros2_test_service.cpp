#include"example_interfaces/srv/add_two_ints.hpp"
#include"rclcpp/rclcpp.hpp"
#include<iostream>


class Service_test01:public rclcpp::Node{
public:
    Service_test01(std::string name):Node(name){
        //打印消息
        RCLCPP_INFO(this->get_logger(),"%s has been started.", name.c_str());

        //创建服务
        add_ints_server = this->create_service<example_interfaces::srv::AddTwoInts>(
            "add_two_ints",
            std::bind(&Service_test01::add_ints_callback,this,std::placeholders::_1,std::placeholders::_2));
    }

private:
    //收到函数的处理请求
    void add_ints_callback(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
                           std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response){
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(),"request: %ld + %ld = %ld",request->a,request->b,response->sum);
    }

    //创建一个服务
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_server;
    //含义：创建一个服务，服务类型为example_interfaces::srv::AddTwoInts，服务名为add_two_ints
};

int main(){
    //初始化ROS
    rclcpp::init(0,NULL);
    //创建节点
    auto node = std::make_shared<Service_test01>("service_test01");
    //循环等待回调函数
    rclcpp::spin(node);
    //关闭ROS
    rclcpp::shutdown();
    return 0;
}