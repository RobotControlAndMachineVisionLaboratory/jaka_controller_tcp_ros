//C++
#include <iostream>
#include <vector>
#include <boost/thread.hpp>

//ROS
#include <ros/ros.h>
#include <ros/package.h>
#include <sensor_msgs/JointState.h>

//gRPC related
#include "robot_client_tcp.h"

//MSG
#include "universal_msgs/Command.h"
#include "universal_msgs/RobotMsg.h"

std::string robot_IP = "192.168.51.15";
std::string command_Topic_Name = "command";
std::string robotMsg_Topic_Name = "jaka_pose";

class jaka_ros_node
{
public:
	jaka_ros_node():robotclient(robot_IP)
	{
		cmd_sub=nh.subscribe(command_Topic_Name, 1, &jaka_ros_node::CommandCallback,this);
		robot_pub=nh.advertise<universal_msgs::RobotMsg>(robotMsg_Topic_Name, 1);
	}
	// void start();
	// void stop();
	int pubRobotPoseOnce();

private:
	ros::NodeHandle nh;
	ros::Subscriber cmd_sub;
	ros::Publisher robot_pub;
	RobotClient robotclient;
	void CommandCallback(const universal_msgs::Command::ConstPtr &msg);
};

// void jaka_ros_node::start()
// {
// 	int reply_int = robotclient.LogIn(username, password);
// 	robotclient.MtnAbort();
// 	return;
// }

// void jaka_ros_node::stop()
// {
// 	printf("stoping the robot!\n");
// 	robotclient.MtnAbort();
// 	sleep(1);
// 	printf("ready to shut down!\n");

// 	int reply_int = robotclient.LogOut(username, password);
// 	return;
// }

void jaka_ros_node::CommandCallback(const universal_msgs::Command::ConstPtr &msg)
{
	if (msg->type == 0)
	{
		std::cout<<"empty Command!"<<std::endl;
		return ;
	}else if (msg->type == 1)
	{
		std::cout<<"Move Line Pose!"<<std::endl;
		return ;
	}else if (msg->type == 2)
	{
		std::cout<<"Move Joint Pose!"<<std::endl;
		robotclient.MoveE(msg->pose, msg->speed);
		return ;
	}else if (msg->type == 3)
	{
		std::cout<<"DIO Command!"<<std::endl;
		// robotclient.DIO(msg->io_type, msg->io_id, msg->dio_value);
		return ;
	}else if (msg->type == 4)
	{
		std::cout<<"Stop Command!"<<std::endl;
		// robotclient.MtnAbort();
		return ;
	}else if (msg->type == 5)
	{
		std::cout<<"Move Tool Command!"<<std::endl;
		robotclient.MoveE(msg->pose, msg->speed);
		return ;
	}else if (msg->type == 6)
	{
		std::cout<<"Move Joint-Multiple Command!"<<std::endl;
		return ;
	}else if (msg->type == 7)
	{
		std::cout<<"Move Line-Multiple Command!"<<std::endl;
		return ;
	}else if (msg->type == 8)
	{
		std::cout<<"JOG Mode!"<<std::endl;
		robotclient.Jog(msg->jogmode, msg->jogcoord, msg->jogaxis,msg->speed,msg->increase);
		return ;
	}else if (msg->type == 9)
	{
		std::cout<<"Move Joint Joint-Angle Command!"<<std::endl;
		std::vector<float> jnt(6,0.0);
		sleep(0.01);
		robotclient.MoveJ(msg->joint, msg->speed);
		return ;
	}else if (msg->type == 10)
	{
		std::cout<<"AIO Command!"<<std::endl;
		robotclient.SetAout(msg->io_type, msg->io_id, msg->aio_value);
		return ;
	}else{
		std::cout<<"Unknown Command!"<<std::endl;
		return ;
	}
}

int jaka_ros_node::pubRobotPoseOnce()
{
	std::vector<float> jnt;
	std::vector<float> cart;
	robotclient.GetRobotPose(jnt, cart);

	std::vector<double> q_actual(6,0.0);
	std::vector<double> tool_vector(6,0.0);
	for (int i = 0; i < 6; ++i)
	{
		q_actual[i]=double(jnt[i]);
		tool_vector[i]=double(cart[i]);
	}

	std::cout << "Joint: [ " << q_actual[0] << ", " << q_actual[1] << ", " << q_actual[2]
	<< ", " << q_actual[3] << ", " << q_actual[4] << ", " << q_actual[5] << " ]" << std::endl;
	std::cout << "Cart: [ " << tool_vector[0] << ", " << tool_vector[1] << ", " << tool_vector[2]
	<< ", " << tool_vector[3] << ", " << tool_vector[4] << ", " << tool_vector[5] << " ]" << std::endl;

	universal_msgs::RobotMsg msg;
	msg.header.stamp = ros::Time::now();
	msg.data.q_actual=q_actual;
	msg.data.tool_vector=tool_vector;
	robot_pub.publish(msg);
}


int main(int argc, char **argv)
{
	if (argc == 2)
		robot_IP = argv[1];
	ros::init(argc, argv, "jaka_ros_node");
	jaka_ros_node node;

	ros::Rate loop_rate(125);
	while(ros::ok())
	{
		node.pubRobotPoseOnce();
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}