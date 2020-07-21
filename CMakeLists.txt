cmake_minimum_required(VERSION 2.8.3)
project(jaka_controller_tcp_ros)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  message_generation
  roscpp
  rospy
  sensor_msgs
  std_msgs
  universal_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES jaka_controller_tcp_ros
  CATKIN_DEPENDS actionlib message_generation roscpp rospy sensor_msgs std_msgs universal_msgs
)

set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  /usr/include/jsoncpp
)

## Declare a C++ library
add_library(${PROJECT_NAME}
  src/libs/config.cpp
  src/libs/robot_client_tcp.cpp
)

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${OpenCV_LIBS} jsoncpp)

add_executable(jaka_ros_node src/jaka_ros_node.cpp)
target_link_libraries(jaka_ros_node ${PROJECT_NAME})

add_executable(jaka_robot_client_tcp_test src/robot_client_tcp_test.cpp)
target_link_libraries(jaka_robot_client_tcp_test ${PROJECT_NAME})

add_executable(jaka_Shutdown src/jaka_Shutdown.cpp)
target_link_libraries(jaka_Shutdown ${PROJECT_NAME})
