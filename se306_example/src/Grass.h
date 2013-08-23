
/*
 * Grass.h
 *
 *  Created on: Aug 14, 2013
 *      Author: ace
 */

#ifndef GRASS_H_
#define GRASS_H_
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "stdio.h"
#include "string.h"
#include "Custom.h"

#include <sstream>
#include "math.h"
#include "Robot.h"
<<<<<<< HEAD
#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"
=======
>>>>>>> 0498468de2cc94a1e8a8ebf96325be88663aae09

class Grass:Robot
	{
	public:
<<<<<<< HEAD
		Grass(std::string robot_name, int argc, char **argv, double px, double py,std::string robot_number);
=======
		Grass(std::string robot_name, int argc, char **argv, double px, double py,int robot_number);
>>>>>>> 0498468de2cc94a1e8a8ebf96325be88663aae09
		~Grass();
		ros::NodeHandle run();
		void stageOdom_callback (nav_msgs::Odometry msg);
		void rainfall_callback (const std_msgs::String::ConstPtr& msg);
		void spinCallback(se306_example::Custom msg);
		void grow(double moisture);
<<<<<<< HEAD
		void identityReply_callBack(se306_example::IdentityReply reply);
		void identityRequest_callBack(se306_example::IdentityRequest request);
		bool doesIntersect(float x, float y);
		void eatenCallback(const std_msgs::String::ConstPtr& msg);
	protected:
		double angular_z;
		std::string message;
		int width;
		int maxHeight;
		int length;
		ros::Subscriber laser;
		double height = 0.0;
		double moistCont = 0.0;
		ros::Publisher Request_pub;
		ros::Publisher Eaten_pub;
		ros::Publisher Reply_pub;
=======
	protected:
		double angular_z;
		ros::Subscriber laser;
		//std_msgs::String heightOfGrass;
		//std_msgs::String moisture;
		//geometry_msgs::Twist angular;
		//ros::Subscriber receive_rainfall;
		//ros::Publisher moistureContent;
		//ros::Publisher height;
		//ros::Publisher spin;
		double height = 0.0;
		double moistCont = 0.0;
>>>>>>> 0498468de2cc94a1e8a8ebf96325be88663aae09
	};

#endif /* GRASS_H_ */

