cmake_minimum_required(VERSION 3.15)

project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src/)

# Find packages if needed
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

# Executable
add_executable(test main.cpp ${SOURCES})

# Link libraries
target_link_libraries(test ${OpenCV_LIBS} 
                            ${EIGEN3_LIBS}
                            m         )
