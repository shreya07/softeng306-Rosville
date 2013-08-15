
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

class Grass:Robot
	{
	public:
		Grass(std::string robot_name, int argc, char **argv, double px, double py,int robot_number);
		~Grass();
		ros::NodeHandle run();
		void stageOdom_callback (nav_msgs::Odometry msg);
		void rainfall_callback (const std_msgs::String::ConstPtr& msg);
		void spinCallback(se306_example::Custom msg);
		void grow(double moisture);
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
	};

#endif /* GRASS_H_ */

