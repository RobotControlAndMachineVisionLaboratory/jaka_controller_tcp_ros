#include "robot_client_tcp.h"

RobotClient::RobotClient()
{}

RobotClient::RobotClient(std::string address) {
	std::cout << "construction Function of Class RobotClient!" << std::endl;
	std::cout << "Connecting to IP address : " << address << std::endl;
	const char *address_ptr = address.c_str();
    // 创建socketrqt
	if ((socketrqt = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "create socket error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(0);
	}

	memset(&servaddr_rqt, 0, sizeof(servaddr_rqt));
    // 指定IP地址版本为IPV4
	servaddr_rqt.sin_family = AF_INET;
    // 设置端口10001
	servaddr_rqt.sin_port = htons(10001);
    // IP地址转换函数
	if (inet_pton(AF_INET, address_ptr, &servaddr_rqt.sin_addr) <= 0) {
		std::cout << "inet_pton error for " << address_ptr;
		exit(-1);
	}

	if (connect(socketrqt, (struct sockaddr *) &servaddr_rqt, sizeof(servaddr_rqt)) < 0) {
		std::cout << "connect error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}

	std::cout << "Socket connects successfully!" << std::endl;
}

void RobotClient::SetIP(std::string address) {
	std::cout << "Connecting to IP address : " << address << std::endl;
	const char *address_ptr = address.c_str();
    // 创建socketrqt
	if ((socketrqt = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "create socket error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(0);
	}

	memset(&servaddr_rqt, 0, sizeof(servaddr_rqt));
    // 指定IP地址版本为IPV4
	servaddr_rqt.sin_family = AF_INET;
    // 设置端口10001
	servaddr_rqt.sin_port = htons(10001);
    // IP地址转换函数
	if (inet_pton(AF_INET, address_ptr, &servaddr_rqt.sin_addr) <= 0) {
		std::cout << "inet_pton error for " << address_ptr;
		exit(-1);
	}

	if (connect(socketrqt, (struct sockaddr *) &servaddr_rqt, sizeof(servaddr_rqt)) < 0) {
		std::cout << "connect error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	std::cout << "Socket connects successfully!" << std::endl;
}

void RobotClient::PowerOn() {
	// 上电
	std::cout << "Power Started!" << std::endl;
	string_tmp = "{\"cmdName\":\"power_on\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
}

void RobotClient::Enable() {
    // 使能
	std::cout << "Enable Started!" << std::endl;
	string_tmp = "{\"cmdName\":\"enable_robot\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
}

void RobotClient::PowerOff() {
	// 断电
	std::cout << "Power Off!" << std::endl;
	string_tmp = "{\"cmdName\":\"power_off\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
}

void RobotClient::Disable() {
    // 下使能
	std::cout << "Disable Started!" << std::endl;
	string_tmp = "{\"cmdName\":\"disable_robot\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
}

RobotClient::~RobotClient(){
    // 下使能
	std::cout << "Disable Started!" << std::endl;
	string_tmp = "{\"cmdName\":\"disable_robot\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';

    // 断电
	std::cout << "Power Off!" << std::endl;
	string_tmp = "{\"cmdName\":\"power_off\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';

	close(socketrqt);
	std::cout<<"Class RobotClient Unconstructed!"<<std::endl;
}

void RobotClient::SetAout(const int &type, const int &aoutid, const float &value) {
	std::cout << "RobotClient::SetAout Started!" << std::endl;
    // SetAout
	string_tmp = "{\"cmdName\":\"set_analog_output\",\"type\":" + std::to_string(type) + ",\"index\":" +
	std::to_string(aoutid) + ",\"value\":" + std::to_string(value) + "}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::SetDout(const int &type, const int &doutid, const int &value){
	std::cout << "RobotClient::SetDout Started!" << std::endl;
    // SetDout
	string_tmp = "{\"cmdName\":\"set_digital_output\",\"type\":" + std::to_string(type) + ",\"index\":" +
	std::to_string(doutid) + ",\"value\":" + std::to_string(value) + "}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::MoveJ(const std::vector<float> &joint_vector, const float &velocity) {
	std::cout << "RobotClient::MoveJ Started!" << std::endl;

	string_tmp = "{\"cmdName\":\"joint_move\",\"jointPosition\":[" + std::to_string(joint_vector[0]) + "," +
	std::to_string(joint_vector[1]) + "," + std::to_string(joint_vector[2]) + "," +
	std::to_string(joint_vector[3]) + "," + std::to_string(joint_vector[4]) + "," +
	std::to_string(joint_vector[5]) + "]" + ",\"speed\":" + std::to_string(velocity) + ",\"relFlag\":0}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;

	string_tmp = "{\"cmdName\":\"wait_complete\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::MoveE(const std::vector<float> &cart_vector, const float &velocity) {
	std::cout << "RobotClient::MoveE Started!" << std::endl;

	string_tmp = "{\"cmdName\":\"end_move\",\"endPosition\":[" + std::to_string(cart_vector[0]) + "," +
	std::to_string(cart_vector[1]) + "," + std::to_string(cart_vector[2]) + "," +
	std::to_string(cart_vector[3]) + "," + std::to_string(cart_vector[4]) + "," +
	std::to_string(cart_vector[5]) + "]" + ",\"speed\":" + std::to_string(velocity) + "}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;

	string_tmp = "{\"cmdName\":\"wait_complete\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::SetRate(const float &rate_value) {
	std::cout << "RobotClient::SetRate Started!" << std::endl;

    // SetRate
	string_tmp = "{\"cmdName\":\"rapid_rate\",\"rate_value\":" + std::to_string(rate_value) + "}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::JogStop(const int &jogcoord, const int &axis){
	std::cout << "RobotClient::JogStop Started!" << std::endl;

	string_tmp = "{\"cmdName\":\"set_tool_id\",\"tool_id\":0}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;

	string_tmp = "{\"cmdName\":\"jog\",\"jog_mode\":0,\"coord_map\":" + std::to_string(jogcoord) + ",\"jnum\":" +
	std::to_string(axis) + "}";
	std::cout << string_tmp << std::endl;
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::Jog(const int &jogmode, const int &jogcoord, const int &axis, const float &speed, const float &coord) {
	std::cout << "RobotClient::Jog Started!" << std::endl;

	string_tmp = "{\"cmdName\":\"set_tool_id\",\"tool_id\":0}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;

	string_tmp = "{\"cmdName\":\"jog\",\"jog_mode\":2,\"coord_map\":" + std::to_string(jogcoord) + ",\"jnum\":" +
	std::to_string(axis) + ",\"jogvel\":" + std::to_string(speed) + ",\"poscmd\":" + std::to_string(coord) + "}";
	// std::cout << string_tmp << std::endl;
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;

	string_tmp = "{\"cmdName\":\"wait_complete\"}";
	cmd_ptr = string_tmp.c_str();
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;
}

void RobotClient::GetRobotPose(std::vector<float>&joint, std::vector<float>&cart) {
	// std::cout << "RobotClient::GetRobotPose Started!" << std::endl;
	float Arr[6], Arr2[6];
    // get data
	cmd_ptr = "{\"cmdName\":\"get_data\"}";
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
    // 延时0.1s，以便于接受完所有信息
	usleep(2e5);
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;

	int joint_size ;
	int cart_size;
	while(1) {
		joint_size = 0;
		cart_size = 0;
		if (reader.parse(buf, root)) {
			joint_size = root["joint_actual_position"].size();
			cart_size = root["actual_position"].size();
            // 解析成功，读取到的数据正确：退出循环
			if (joint_size == 6 && cart_size == 6) {
				for (Json::Value::ArrayIndex i = 0; i < joint_size; ++i) {
					Arr[(int) i] = root["joint_actual_position"][i].asFloat();
				}
				for (Json::Value::ArrayIndex i = 0; i < cart_size; ++i) {
					Arr2[(int) i] = root["actual_position"][i].asFloat();
				}
				break;
			}
            // 解析成功，但是读取到的数据不正确：重新发送命令，重新解析
			else {
				cmd_ptr = "{\"cmdName\":\"get_data\"}";
				if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
					std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
					exit(-1);
				}
				usleep(2e5);
				int rec_len = recv(socketrqt, buf, MAXLINE, 0);
				buf[rec_len] = '\0';
				// std::cout << "Reveived: " << buf << std::endl;
			}
		}
        // 解析不成功：重新发送命令，重新解析
		else {
			cmd_ptr = "{\"cmdName\":\"get_data\"}";
			if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
				std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
				exit(-1);
			}
			usleep(2e5);
			int rec_len = recv(socketrqt, buf, MAXLINE, 0);
			buf[rec_len] = '\0';
			// std::cout << "Reveived: " << buf << std::endl;
		}
	}

	joint.clear();
	joint.push_back(Arr[0]);
	joint.push_back(Arr[1]);
	joint.push_back(Arr[2]);
	joint.push_back(Arr[3]);
	joint.push_back(Arr[4]);
	joint.push_back(Arr[5]);

	cart.clear();
	cart.push_back(Arr2[0]);
	cart.push_back(Arr2[1]);
	cart.push_back(Arr2[2]);
	cart.push_back(Arr2[3]);
	cart.push_back(Arr2[4]);
	cart.push_back(Arr2[5]);
}

void RobotClient::Shutdown() {
	std::cout << "RobotClient::Shutdown Started!" << std::endl;

	cmd_ptr = "{\"cmdName\":\"shutdown\"}";
	// std::cout << "Send command to server:" << cmd_ptr << std::endl;
	if (send(socketrqt, cmd_ptr, strlen(cmd_ptr), 0) < 0) {
		std::cout << "send msg error:" << strerror(errno) << "(errno:" << errno << ")" << std::endl;
		exit(-1);
	}
	int rec_len = recv(socketrqt, buf, MAXLINE, 0);
	buf[rec_len] = '\0';
	// std::cout << "Reveived: " << buf << std::endl;
}