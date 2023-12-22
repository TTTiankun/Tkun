cmake_minimum_required(VERSION 3.15)

project(test01)


find_package(OpenVINO REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${OpenVINO_INCLUDE_DIRS})
link_directories(${LINK_DIR})


add_executable(test Matrix.cpp)

target_link_libraries(test 
                    PRIVATE openvino::runtime
                    ${OpenVINO_LIBRARIES}
                    ${OpenCV_LIBS}
                    ${EIGEN3_LIBS})
                    
