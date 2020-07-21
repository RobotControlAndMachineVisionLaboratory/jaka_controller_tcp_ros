# This ROS package is for the basic motor functions of JAKA robot. 
![alt text](images/JAKA_Zu_7.jpg "JAKA Zu 7 Robot")

# Abstract
- Project name: **jaka_controller_tcp_ros**
- This repo is a cmake project for the basic motor functions of JAKA robot.
- Communication protocol is: `TCP/IP`.
- APP/Robot-Firmware/servo-Firmware version: `1.4.11.17/1.4.11_21RC/R-1.10_2.126`

## Dependency

jsoncpp:

``` bash
sudo apt-get install libjsoncpp-dev
```

This should install json related header files in `/usr/include/jsoncpp` as we use in the `CMakeLists.txt`.

## Build and Test

```bash
cd ${base_path_to_your_catkin_workspace}
catkin_make
```

The executable node can be run as:

```bash
./bin/robot_client_tcp_test
```
