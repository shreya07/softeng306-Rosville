/*
 * PoisonGrass.h
 *
 *  Created on: Aug 26, 2013
 *      Author: George Chang
 */

#ifndef POISONGRASS_H_
#define POISONGRASS_H_
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

#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"

class PoisonGrass:Robot
	{
	public:
		PoisonGrass(std::string robot_name, int argc, char **argv);
		~PoisonGrass();
		ros::NodeHandle run();
		void stageOdom_callback (nav_msgs::Odometry msg);
		void rainfall_callback (const std_msgs::String::ConstPtr& msg);
		void spinCallback(se306_example::Custom msg);
		void grow(double moisture);
		void identityReply_callBack(se306_example::IdentityReply reply);
		void identityRequest_callBack(se306_example::IdentityRequest request);
		bool doesIntersect(float x, float y);
		void eatenCallback(const std_msgs::String::ConstPtr& msg);
	protected:
		double soilQual;
		double maxSoilQuality;
		double maxMoistCont;
		double angular_z;
		std_msgs::String message;
		int width;
		int maxHeight;
		int length;
		ros::Subscriber laser;
		double height;
		double moistCont;
		ros::Publisher Request_pub;
		ros::Publisher Eaten_pub;
		ros::Publisher Reply_pub;
		ros::Publisher spin;
	};


#endif /* POISONGRASS_H_ */
