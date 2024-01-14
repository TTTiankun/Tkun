#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"
#include <iostream>
//这个是一个基础版的客户端，只能发送一个请求，等待一个响应
class Client_test02 : public rclcpp::Node {
public:
    Client_test02(std::string name) : Node(name) {
        // 打印消息
        RCLCPP_INFO(this->get_logger(), "%s has been started.", name.c_str());
        // 创建客户端
        add_ints_client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        
    }

    void send_request_around(){
        send_request(std::rand()%10, std::rand()%10);
    }

    void send_request(int a, int b) {
        RCLCPP_INFO(this->get_logger(), "Sending request: %d + %d", a, b);

        // 等待服务端上线
        while (!add_ints_client->wait_for_service(std::chrono::seconds(1))) {
            if (!rclcpp::ok()) { // rclcpp::ok()返回false表示节点已关闭
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Service not available, waiting again...");
        }

        // 创建请求
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>(); // 创建请求
        request->a = a; // 设置请求参数
        request->b = b;

        // 发送请求
        auto future_result = add_ints_client->async_send_request(
            request, std::bind(&Client_test02::result_callback, this, std::placeholders::_1));

        //使用异步请求，等待响应
        rclcpp::spin_until_future_complete(this->get_node_base_interface(), future_result);
    }

private:
    // 声明客户端
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_client;


   void result_callback(const rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture result_future) {
    // 获取响应
    auto response = result_future.get(); //含义：等待响应结果，直到响应结果返回
    if (response) {
        RCLCPP_INFO(
            this->get_logger(),
            "Result is %d", (int)response->sum); // 打印响应结果
    } else {
        RCLCPP_ERROR(this->get_logger(), "Failed to get response.");// 响应失败
    }

    

}

};

int main() {
    // 初始化ROS
    rclcpp::init(0, NULL);
    // 创建节点
    auto node = std::make_shared<Client_test02>("client_test02");
    // 发送请求
    node->send_request(3,8);
    // 循环等待回调函数
    // 关闭ROS
    rclcpp::shutdown();
    return 0;
}
