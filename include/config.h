#ifndef _CV_CONFIG_H_
#define _CV_CONFIG_H_

#include <memory>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
class Config
{
	private:
		static Config* config_;
		cv::FileStorage file_;

		Config(){};   //private constructor makes a singleton

	public:
		~Config();

		//set a new config file
		static void setParameterFile(const std::string& fileName);

		//access the parameter values
		template<typename T>
		static T get(const std::string& key)
		{
			T res;
			if (Config::config_->file_[key].isNone())
			{
				std::cout<<"key[" << key << "] in parameter file is None! Check Spell First! Aborting ..."<<std::endl;
				exit(-1);
			}
			else
			{
				Config::config_->file_[key] >> res;
			}
			return res;
		}
};

#endif
