#ifndef __JAKA_ROBOT_CLIENT_TCP_H_
#define __JAKA_ROBOT_CLIENT_TCP_H_

#define MAXLINE 8192

#include <string>
#include <vector>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json/json.h>

class RobotClient {
public:
    RobotClient(std::string address);

    RobotClient();

    ~RobotClient();

    //设置运动速度倍率
    void SetRate(const float &rate_value);

    //设置模拟量的输出
    void SetAout(const int &type, const int &doutid, const float &value);

    //获取机器人关节姿态和末端姿态
    void GetRobotPose(std::vector<float> &jnt, std::vector<float> &cart);

    //关节形式运动
    void MoveJ(const std::vector<float> &joint_vector, const float &velocity);

    //末端形式运动[xyzrpy]
    void MoveE(const std::vector<float> &cart_vector, const float &velocity);

    //末端步进运动
    void Jog(const int &jogmode, const int &jogcoord, const int &axis, const float &speed, const float &coord);

    //步进运动停止
    void JogStop(const int &jogcoord, const int &axis);

    //关闭机器人和控制器
    void Shutdown();

private:
    Json::Reader reader;
    Json::Value root;
    int socketrqt, socketrcv;
    struct sockaddr_in servaddr_rqt, servaddr_rcv;
    char buf[MAXLINE];
    const char *cmd_ptr;
    std::string string_tmp;
};

#endif
