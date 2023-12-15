cmake_minimum_required(VERSION 3.15)

project(test)



find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})




add_executable(test test.cpp)

target_link_libraries(test ${OpenCV_LIBS})