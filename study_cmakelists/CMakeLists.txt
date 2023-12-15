# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

# 添加可执行文件并链接源文件
add_executable(hello main.cpp hello.cpp)
