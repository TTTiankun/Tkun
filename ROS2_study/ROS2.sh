#！/bin/bash
#ROS2的常用命令以及学习

#启动ROS2
#用法：ros2 run <package_name> <executable_name>
ros2 run turtlesim turtlesim_node

#显示ROS2的节点
#用法：ros2 node list
ros2 node list

#显示节点的信息
#用法：ros2 node info /<node_name>
ros2 node info turtlesim_node

#重新映射节点名称
#用法：ros2 run <package_name> <executable_name> --ros-args -r __node:=<node_name>
ros2 run turtlesim turtlesim_node --rod-args --ros-args -r __node:=my_turtle

#显示ROS2的主题
#用法：ros2 topic list
ros2 topic list

#ROS2功能包获取
#用法：sudo apt install ros-<distro>-<package_name>
sudo apt install ros-humble-turtlesim
#有时候也需要手动安装依赖项

#与功能包相关的命令
#用法：ros2 pkg <command> <package_name>
#创建功能包
ros2 pkg create --build-type ament_cmake <package_name>
#type选项：ament_cmake、ament_python、ament_lint_auto、ament_pep257、ament_pep8、ament_uncrustify、ament_xmllint、ament_flake8、ament_cmake_lint、ament_cmake_pep257、ament_cmake_pep8、ament_cmake_uncrustify、ament_cmake_xmllint、ament_cmake_flake8
#列出可执行文件（某一个包）
ros2 pkg executables <package_name>
#列出所有的包
ros2 pkg list
#输出某个包所在路径的前缀
ros2 pkg prefix <package_name>
#列出某个包的描述文件的清单
ros2 pkg xml <package_name>

#创建一个CPP节点(面向对象编程思想)

#创建一个资源文件夹
mkdir src
cd src

#创建一个功能包
#用法：ros2 pkg create <programme name> --build-type <build-type> --dependencies <dependencies> <package_name>
ros2 pkg create ros2_test_node --build-type ament_cmake --dependencies rclcpp 

#在src文件夹创建一个节点文件 cpp
touch ros2_test_node.cpp

#CMakelist.txt文件最后需要加上的东西
add_executable(ros2_test_node src/ros2_test_node.cpp) #节点的名字是ros2_test
ament_target_dependencies(ros2_test_node rclcpp)

install(TARGETS
  ros2_test_node #节点的名字
  DESTINATION lib/${PROJECT_NAME})

#编译
#用法：colcon build --packages-select <package_name>
colcon build --packages-select ros2_test_node

#设置环境变量
source install/setup.bash

#运行
#用法：ros2 run <package_name> <executable_name>
ros2 run ros2_test_node ros2_test_node

#ROS2的发布订阅模型
#存在发布者（publisher）和订阅者（subscriber），发布者发布消息，订阅者订阅消息，发布者和订阅者之间通过主题（topic）进行通信
#发布者发布的消息类型和订阅者订阅的消息类型必须一致，否则会出现错误
#发布者和订阅者之间的通信是异步的，发布者发布的消息，订阅者不一定能够接收到，订阅者订阅的消息，发布者不一定能够接收到
#发布者和订阅者之间的通信是无状态的，发布者发布的消息，订阅者不一定能够接收到，订阅者订阅的消息，发布者不一定能够接收到
#发布者和订阅者之间的通信是无连接的，发布者发布的消息，订阅者不一定能够接收到，订阅者订阅的消息，发布者不一定能够接收到
#发布者和订阅者之间的通信是不可靠的，发布者发布的消息，订阅者不一定能够接收到，订阅者订阅的消息，发布者不一定能够接收到

#同一个主题可以有多个发布者和订阅者，一个节点可以是发布多个主题，一个主题可以有多个消息类型，一个节点可以接受多个主题
#一个信息只能有一个发布者，一个信息只能有一个订阅者，一个节点可以发布多个信息，一个节点可以订阅多个信息

#RQT工具查看话题 （rqt_grapher）
#用法：rqt_graph 即可查看
#创建一个发布者
ros2 run demo_nodes_cpp talker
#创建一个订阅者
ros2 run demo_nodes_cpp listener
#查看话题
rqt_graph

# ROS2话题相关的命令行工具(ros2 topic)
#用法：ros2 topic <command> <topic_name>
#列出所有的话题
ros2 topic list
#列出某个话题的类型
ros2 topic type <topic_name> #类型：std_msgs/msg/String
#列出某个话题的信息
ros2 topic info <topic_name>
#列出某个话题的发布者
ros2 topic pub --help
#列出某个话题的订阅者
ros2 topic echo --help
#打印某个话题的消息
ros2 topic echo <topic_name>
#查看消息的接口的具体类型
ros2 inferface show std_msgs/msg/String
#手动发布消息
#用法：ros2 topic pub <topic_name> <msg_type> <msg_content>
ros2 topic pub /chatter std_msgs/msg/String "{data: 'hello'}"

#创建一个发布者(有机会可以查看ROS2官方文档获取API用法)

#进入资源文件夹
cd src

#创建一个功能包
ros2 pkg create ros2_test_publisher --build-type ament_cmake --dependencies rclcpp std_msgs
#含义：创建一个名为ros2_test_publisher的功能包，使用ament_cmake编译，依赖于rclcpp和std_msgs

#在src文件夹创建一个发布者文件 cpp
touch ros2_test_publisher.cpp

#CMakelist.txt文件最后需要加上的东西
add_executable(ros2_test_publisher src/ros2_test_publisher.cpp) #节点的名字是ros2_test
ament_target_dependencies(ros2_test_publisher rclcpp std_msgs) #依赖于rclcpp和std_msgs

install(TARGETS
  ros2_test_publisher #节点的名字
  DESTINATION lib/${PROJECT_NAME})

#编译
colcon build --packages-select ros2_test_publisher

#设置环境变量
source install/setup.bash

#运行
ros2 run ros2_test_publisher ros2_test_publisher

#创建一个订阅者(有机会可以查看ROS2官方文档获取API用法)
ros2 pkg create ros2_test_subscriber --build-type ament_cmake --dependencies rclcpp std_msgs

#在src文件夹创建一个订阅者文件 cpp
touch ros2_test_subscriber.cpp

#CMakelist.txt文件最后需要加上的东西
add_executable(ros2_test_subscriber src/ros2_test_subscriber.cpp) #节点的名字是ros2_test
ament_target_dependencies(ros2_test_subscriber rclcpp std_msgs) #依赖于rclcpp和std_msgs

install(TARGETS
  ros2_test_subscriber #节点的名字
  DESTINATION lib/${PROJECT_NAME})

#编译
colcon build --packages-select ros2_test_subscriber

#设置环境变量
source install/setup.bash

#运行
ros2 run ros2_test_subscriber ros2_test_subscriber

#查看ros2的接口类型
ros2 interface package sensor_msgs

#ros2关于接口的CLI工具（ros2）
#用法：ros2 <command> <options>
#列出所有的接口
ros2 interface list
#查看所有接口的包
ros2 interface package 
#查看某个包下的接口
#用法：ros2 interface package <package_name>
ros2 interface package sensor_msgs
#查看某个接口详细的内容
#用法：ros2 interface show <interface_name>
ros2 interface show sensor_msgs/msg/Image
#查看摸个接口的所有属性
#用法：ros2 interface proto <interface_name>
ros2 interface proto sensor_msgs/msg/Image

#ros2提供四种通讯方式
#1.话题（topic）：发布者和订阅者之间的通信方式，发布者发布消息，订阅者订阅消息，发布者和订阅者之间通过主题（topic）进行通信
#2.服务（service）：客户端和服务器之间的通信方式，客户端发送请求，服务器接受请求并且返回响应，客户端和服务器之间通过服务（service）进行通信
#3.参数（parameter）：参数服务器和客户端之间的通信方式，客户端可以从参数服务器中获取参数，也可以向参数服务器中设置参数，客户端和参数服务器之间通过参数（parameter）进行通信
#4.动作（action）：客户端和服务器之间的通信方式，客户端发送目标，服务器接受目标并且返回结果，客户端和服务器之间通过动作（action）进行通信

#自定义话题接口
#进入工作空间
cd src
#创建一个功能包
ros2 pkg create ros2_test_interfaces --build-type ament_cmake --dependencies rclcpp std_msgs
#创建并进入msg
mkdir msg && cd msg
#创建一个文件
touch TestInterfaces.msg #给通讯接口命名的时候中间不能有符号，开头不能有数字，开头必须大写！
#编写msg文件的内容
#编译msg文件
colcon build --packages-select ros2_test_interfaces

#在CMakelist.txt文件中添加

#查找sensor_msgs库
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 声明 ROS 2 消息生成 添加相关消息依赖
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Testinterfaces.msg"  # 这里是你的IDL文件
  DEPENDENCIES sensor_msgs  # 这里是你的依赖项，例如 sensor_msgs
)

#修改package.xml文件 提前检查相关依赖项是否添加 若不添加编译时也不会报错
  <depend>sensor_msgs</depend>
  <build_depend>rosidl_default_generators</build_depend>
  <exec_depend>rosidl_default_runtime</exec_depend>
  <member_of_group>rosidl_interface_packages</member_of_group>
#重新配置环境
source install/setup.bash

#测试接口
ros2 interface package ros2_test_interfaces #查看包
ros2 interface show ros2_test_interfaces/msg/TestInterfaces #查看接口
ros2 interface proto ros2_test_interfaces/msg/TestInterfaces #查看接口的所有属性

#服务
#启动服务端
#用法：ros2 run <package_name> <executable_name>
ros2 run examples_rclpy_minimal_service service

#查看服务列表
#用法：ros2 service list
ros2 service list

#手动调用服务端
#用法：ros2 service call <service_name> <service_type> <service_content>
ros2 service call /add_two_ints example_interfaces/srv/AddTwoInts "{a: 1, b: 2}"

#也可以使用rqt的服务调用工具来调用服务端
#用法：rqt

#查看服务的类型
#用法：ros2 service type <service_name>、
ros2 service type /add_two_ints

#查找使用某一服务的接口
#用法：ros2 interface package <package_name>
ros2 interface package example_interfaces

#创建一个服务接口 （借钱）
#进入工作空间并进入原来的那个功能包
cd src && cd ros2_test_interfaces

#创建一个服务接口
mkdir srv && cd srv

#创建一个文件
touch TestInterfaces.srv #给通讯接口命名的时候中间不能有符号，开头不能有数字，开头必须大写！

#编写srv文件的内容
#服务文件的内容：一个是请求的数据类型和名称，一个是响应的数据类型和名称！！！ 中间用---隔开
#修改CMakelist.txt文件

#添加新的服务生成
"srv/TestInterfaces.srv"  # 这里是你的IDL文件
#由于使用的是原本的数据类型，所以不需要添加依赖项
#之前添加依赖项的原因是因为使用了sensor_msgs库和rosidl_default_generators库来进行数据类型的自定义 

#验证服务接口
ros2 interface package ros2_test_interfaces #查看包
ros2 interface show ros2_test_interfaces/srv/TestInterfaces #查看接口
ros2 interface proto ros2_test_interfaces/srv/TestInterfaces #查看接口的所有属性

#创建一个服务接口（买书）
#进入工作空间并进入原来的那个功能包
cd src && cd ros2_test_interfaces

#创建一个服务接口
cd srv

#创建一个文件
touch SellBook.srv #给通讯接口命名的时候中间不能有符号，开头不能有数字，开头必须大写！

#编写srv文件的内容
#服务文件的内容：一个是请求的数据类型和名称，一个是响应的数据类型和名称！！！ 中间用---隔开
#修改CMakelist.txt文件
"srv/SellBook.srv"  # 这里是你的IDL文件

#编译
colcon build --packages-select ros2_test_interfaces
#重新配置环境
source install/setup.bash
#验证服务接口
ros2 interface package ros2_test_interfaces #查看包
ros2 interface show ros2_test_interfaces/srv/SellBook #查看接口
ros2 interface proto ros2_test_interfaces/srv/SellBook #查看接口的所有属性 

#编写一个服务端
#步骤：1.导入服务接口 2.创建服务端回调函数 3.声明并创建服务端函数 4.编写回调函数逻辑处理请求
#在编写服务端的时候如果要使用自己定义的数据类型接口，需要在CMakelist.txt和package.xml文件中添加依赖项,也要在cpp文件中添加相关的头文件

#一些基础的知识
#死锁
#死锁是指两个或者两个以上的进程在执行过程中，因争夺资源而造成的一种互相等待的现象，若无外力作用，这些进程都将无法向前推进，此时称系统处于死锁状态或系统产生了死锁，这些永远在互相等待的进程称为死锁进程

#互斥
#互斥是指某一资源同时只允许一个访问者对其进行访问，具有唯一性和排它性，但互斥无法限制访问者对资源的访问顺序，即访问是无序的

#占有并等待
#占有并等待是指一个进程在请求资源的同时，对已经获得的资源保持不放

#不可抢占
#不可抢占是指进程已经获得的资源，在未使用完之前，不能被其他进程强行夺走，即只能在进程完成任务后自己释放

#循环等待
#循环等待是指存在一种进程资源的循环等待链，链中每一个进程已获得的资源同时被链中下一个进程所请求

#多线程
#多线程是指从软件或者硬件上实现多个线程并发执行的技术，这些线程可以运行在同一个或者不同的进程中，多线程可以提高应用程序的并发性，但是也会带来一些问题，比如死锁

#编写一个简单的服务端
#创建一个新的包
ros2 pkg create ros2_test_service --build-type ament_cmake --dependencies rclcpp std_msgs example_interfaces
#进入包
cd src && cd ros2_test_service
#进入资源文件夹
cd src
#创建一个cpp文件
touch ros2_test_service.cpp
#编写cpp文件的内容
#导入服务接口 #include "example_interfaces/srv/add_two_ints.hpp"
#修改CMakelist.txt文件
find_package(example_interfaces REQUIRED)

add_executable(ros2_test_service src/ros2_test_service.cpp)
ament_target_dependencies(ros2_test_service rclcpp std_msgs example_interfaces)

install(TARGETS
  ros2_test_service #节点的名字
  DESTINATION lib/${PROJECT_NAME})

#修改package.xml文件
  <depend>example_interfaces</depend>

#编译
colcon build --packages-select ros2_test_service
#重新配置环境
source install/setup.bash
#运行
ros2 run ros2_test_service ros2_test_service
#测试
ros2 service list
ros2 service type /add_two_ints
ros2 service call /add_two_ints example_interfaces/srv/AddTwoInts "{a: 1, b: 2}"

#编写一个简单的客户端
#创建一个新的包
ros2 pkg create ros2_test_client --build-type ament_cmake --dependencies rclcpp std_msgs example_interfaces
#进入包
cd src && cd ros2_test_client
#进入资源文件夹
cd src
#创建一个cpp文件
touch ros2_test_client.cpp
#编写cpp文件的内容
#导入服务接口 #include "example_interfaces/srv/add_two_ints.hpp"
#修改CMakelist.txt文件
find_package(example_interfaces REQUIRED)

ament_package()
add_executable(ros2_test_client src/ros2_test_client.cpp)
ament_target_dependencies(ros2_test_client rclcpp std_msgs example_interfaces)

install(TARGETS
  ros2_test_client #节点的名字
  DESTINATION lib/${PROJECT_NAME})

#修改package.xml文件
  <depend>example_interfaces</depend>

#编译
colcon build --packages-select ros2_test_client
#重新配置环境
source install/setup.bash
#运行
ros2 run ros2_test_client ros2_test_client
#测试 打开服务端
source install/setup.bash
ros2 run ros2_test_service ros2_test_service

#体验参数
#打开乌龟模拟器
ros2 run turtlesim turtlesim_node
ros2 run turtlesim turtle_teleop_key

#查看参数列表
#用法：ros2 param list
ros2 param list

#查看参数的值
#用法：ros2 param get <parameter_name>
ros2 param get  turtlesim background_b

#设置参数的值
#用法：ros2 param set <parameter_name> <parameter_value>
ros2 param set turtlesim background_b 150

#查看参数的描述
#用法：ros2 param describe <parameter_name>
ros2 param describe turtlesim background_b

#储存参数
#用法：ros2 param dump <file_name> <node_name>
ros2 param dump /home/humble/turtlesim.yaml /turtlesim

#加载参数
#用法：ros2 param load <file_name> <node_name>
ros2 param load /home/humble/turtlesim.yaml /turtlesim

#删除参数
#用法：ros2 param delete <parameter_name>
ros2 param delete turtlesim background_b

#打印日志 （参数）
#创建一个新的包
ros2 pkg create ros2_test_parameters --build-type ament_cmake --dependencies rclcpp std_msgs example_interfaces
#进入包
cd src && cd ros2_test_parameters
#进入资源文件夹
cd src
#创建一个cpp文件
touch ros2_test_parameters.cpp
#编写cpp文件的内容
#修改CMakelist.txt文件
find_package(example_interfaces REQUIRED)

add_executable(ros2_test_parameters src/ros2_test_parameters.cpp) #节点的名字是ros2_test
ament_target_dependencies(ros2_test_parameters rclcpp std_msgs)#添加依赖

install(TARGETS
  ros2_test_parameters #节点的名字
  DESTINATION lib/${PROJECT_NAME})

#修改package.xml文件
  <depend>example_interfaces</depend>
#编译
colcon build --packages-select ros2_test_parameters
#重新配置环境
source install/setup.bash
#运行
ros2 run ros2_test_parameters ros2_test_parameters
#测试
ros2 param list #查看参数列表
#运行过程中修改参数
ros2 param set /parameters_test01 rcl_log_level 10
#参数级别
#0：UNSET
#10：DEBUG
#20：INFO
#30：WARN
#40：ERROR
#50：FATAL

#体验action （乌龟模拟器）
#启动乌龟模拟器
ros2 run turtlesim turtlesim_node

#启动乌龟模拟器的键盘控制
ros2 run turtlesim turtle_teleop_key

#按下F可以停止小乌龟正在进行的动作 这就是action的作用

#action的CLI工具（ros2）
#用法：ros2 <command> <options>

#列出所有的action
ros2 action list
ros2 action list -t #列出所有的action的类型

#查看action的类型
ros2 action info /turtle1/rotate_absolute

#发送action的目标
#用法：ros2 action send_goal <action_name> <action_type> <goal_content>
ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "{theta: 1.57}" #输入yaml类型的数据
ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "{'theta': 30}" --feedback #可以实时刷新当前的角度位置

#编写launch文件 
#launch文件的作用
#1.启动多个节点
#2.启动多个节点的时候可以设置节点的参数
#3.启动多个节点的时候可以设置节点的命名空间
#4.启动多个节点的时候可以设置节点的重定向

#在其中一个需要的节点的install包下面创建一个launch文件
cd install/ros2_test_service/share/ros2_test_service
#创建一个launch文件
touch test_launch.py
#编写launch文件的内容
#1.单终端运行
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros2_test_client',# 替换为你的第一个节点的包名
            executable='ros2_test_client',  # 替换为你的第一个节点的可执行文件名
            name='ros2_test_client',# 替换为你的第一个节点的名字
            output='screen',
        ),
        Node(
            package='ros2_test_service',# 替换为你的第二个节点的包名
            executable='ros2_test_service',  # 替换为你的第二个节点的可执行文件名
            name='ros2_test_service',# 替换为你的第二个节点的名字
            output='screen',
        ),
    ])
#运行
ros2 launch ros2_test_service test_launch.py

#可以使用ros2bag去记录话题
#用法：ros2 bag record <topic_name>
#录制某一个话题
ros2 bag record /rosout
#记录所有的话题
ros2 bag record -a
#自定义录制话题（两个）
ros2 bag record -o my_turtle /turtle1/cmd_vel /turtle1/pose

#录制话题
#用法：ros2 bag record <topic_name>
#文件名默认是rosbag2_YYYY_MM_DD_HH_MM_SS #文件的格式是.db3 #文件的位置在log文件夹下
#查看话题信息
#用法：ros2 bag info <bag_file_name>
ros2 bag info rosbag2_2024_01_08-20_46_12/rosbag2_2024_01_08-20_46_12_0.db3
#播放话题
#用法：ros2 bag play <bag_file_name>
ros2 bag play rosbag2_2024_01_08-20_46_12/rosbag2_2024_01_08-20_46_12_0.db3
#播放话题并且设置速度
#用法：ros2 bag play <bag_file_name> -r<rate>
ros2 bag play rosbag2_2024_01_08-20_46_12/rosbag2_2024_01_08-20_46_12_0.db3 -r 10
#播放话题并且设置速度和循环播放
#用法：ros2 bag play <bag_file_name> -r<rate> -l
ros2 bag play rosbag2_2024_01_08-20_46_12/rosbag2_2024_01_08-20_46_12_0.db3 -r 10 -l

#RVIZ2 数据可视化软件
#可以通过这个软件查看仿真的情况
#启动RVIZ2
rviz2
#Gazebo仿真软件 可以进行ros2仿真
#启动Gazebo
gazebo

#2024.01.09 学习告一段落 还差ROS2中的action没有学习。



