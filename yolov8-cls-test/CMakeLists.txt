cmake_minimum_required(VERSION 3.15)

project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES_DIR "src/*.cpp")

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenVINO REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${OpenVINO_INCLUDE_DIRS})

add_executable(test yolov8_cls_ov_infer.cpp ${SOURCES_DIR})

target_link_libraries(test
                    PRIVATE openvino::runtime
                    ${OpenVINO_LIBRARIES}
                    ${OpenCV_LIBS}
                    ${EIGEN3_LIBS})
