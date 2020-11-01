//C++
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

//Customed
#include "robot_client_tcp.h"

int main(int argc, char **argv)
{
	// RobotClient robotclient("192.168.51.15");

	RobotClient robotclient;
	robotclient.SetIP("192.168.51.15");


	robotclient.PowerOn();

	robotclient.Enable();

	robotclient.SetAout(0, 7, 1);

	std::cout<<"ready to -- SetRate";
	float rapid_ratio=0.6;
	robotclient.SetRate(rapid_ratio);

	std::vector<float> jointpose;
	jointpose={0,90,0,90,-90,45};
	float vel=50;
	robotclient.MoveJ(jointpose,vel);

	// getchar();

	std::vector<float> cartpose;
	cartpose={-313.956, 116.250, 469.512, -157.792, 20.705, 49.107};
	robotclient.MoveE(cartpose,vel);

	// getchar();

	cartpose={-313.956, 116.250, 520.520, -157.792, 20.705, 49.107};
	robotclient.MoveE(cartpose,vel);

	// getchar();

	cartpose={-313.956, 116.250, 469.512, -157.792, 20.705, 49.107};
	robotclient.MoveE(cartpose,vel);

	// getchar();

	cartpose={-313.956, 116.250, 520.520, -157.792, 20.705, 49.107};
	robotclient.MoveE(cartpose,vel);

	// getchar();

	robotclient.SetAout(2,0,256);
	robotclient.SetAout(2,2,255);
	robotclient.SetAout(2,1,0);
	robotclient.SetAout(2,0,2304);

	std::vector<float> joint,cart;
	for (int i = 0; i < 10; ++i)
	{
		robotclient.GetRobotPose(joint,cart);
		std::cout<<"joint = ";
		for(int i=0;i<6;i++)
		{
			std::cout<<joint[i]<<" ";
		}
		std::cout<<std::endl;
		std::cout<<"cart = ";
		for(int i=0;i<6;i++)
		{
			std::cout<<cart[i]<<" ";
		}
		std::cout<<std::endl;
	}
	return 0;
}