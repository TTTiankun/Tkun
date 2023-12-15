cmake_minimum_required(VERSION 3.15)

project(test)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(test test_s.cpp)

target_link_libraries(test ${OpenCV_LIBS}
                            ${EIGEN3_LIBS})