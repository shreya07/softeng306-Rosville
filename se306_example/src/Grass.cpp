/*
 * Grass.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: Kirushi Arunthavasothy
 */

#include "Grass.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <sstream>
#include "math.h"
#include "Robot.h"


// INITIALIZE MOISTURE AND HEIGHT


// INITIALIZE ANGULAR Z
double angular_z;


Grass::Grass(std::string robot_name, int argc, char **argv,double px,double py, int robot_number):Robot(robot_name,argc,argv,px,py,robot_number) {

}

Grass::~Grass()
{
	// TODO Auto-generated destructor stub
}

// CALL BACK METHOD TO DELEGATE ITS POSITION
void Grass::stageOdom_callback(nav_msgs::Odometry msg){

}

// CHECKS RAINFALL AND INCREMENTS/DECREMENTS MOISTURE LEVEL
void Grass::rainfall_callback(const std_msgs::String::ConstPtr& rainfall) {

	//ROS_INFO("I heard: [%s]", rainfall->data.c_str());

	if (rainfall->data.compare("Sunny")==0) {
		moistCont = moistCont + 1;
	} else if (rainfall->data.compare("Raining")==0) {
		moistCont = moistCont - 1;
	}

	//grow(moistCont);
}

// INCREASES AND DECREASES HEIGHT DEPENDING ON MOISTURE
void Grass::grow(double moisture) {

	if (moisture > 0) {
		height = height+moisture/100;
	} else if (moisture < 5 && height != 0) {
		height = height-moisture/10;
	}
}

ros::NodeHandle Grass::run(){

	ros::NodeHandle n = Robot::run();

	// LISTEN TO RECIEVE RAINFALL
	ros::Subscriber receive_rainfall = n.subscribe<std_msgs::String>("robot_4/status",1000, &Grass::rainfall_callback, this);

	// ADD SUBSCRIBERS TO LIST
	std::list<ros::Subscriber>::iterator it;
	it = subsList.end();
	subsList.insert(it,receive_rainfall);

	// TO CHANGE ANGULAR VELOCITY SET A PUBLISHER TO LISTEN ON CMD_VEL
	ros::Publisher spin = n.advertise<geometry_msgs::Twist>("robot_4/cmd_vel",1000);

	// CREATE MOISTURE AND HEIGHT TOPICS TO PUBLISH TOWARDS
	//ros::Publisher moistureContent = n.advertise<std_msgs::String>("weather/moisture",1000);
	//ros::Publisher grassHeight = n.advertise<std_msgs::String>("grass/height", 1000);



	// ADD PUBLISHERS TO LIST
	std::list<ros::Publisher>::iterator iter;
	iter = pubsList.end();
	pubsList.insert(iter, spin);
	//pubsList.insert(iter, moistureContent);
	//pubsList.insert(iter, grassHeight);


	// SENDING AT 10 MESSAGES A SECOND
	ros::Rate loop_rate(10);


	// INITIALIZE VARIABLES TO PUBLISH
	std_msgs::String heightOfGrass;
	std_msgs::String moisture;
	geometry_msgs::Twist angular;


	while (ros::ok())
	{
	        grow(this->moistCont);
		ROS_INFO("Value is [%lf]", angular.angular.z);
		// SET ANGULAR VELOCITY
		angular.angular.z = angular_z;

		// CHANGE TYPE TO STRING TO MATCH REQUIREMENTS
		//heightOfGrass = boost::lexical_cast<std_msgs::String>(height);
		//moisture = boost::lexical_cast<std_msgs::String>(moistCont);

		// PUBLISH
		spin.publish(angular);
		//grassHeight.publish(heightOfGrass);
		//moistureContent.publish(moisture);
		ROS_INFO("Current value of Moisture is %f",this->moistCont);
		ROS_INFO("Current value of Height is %f",this->height);

		ros::spinOnce();
		loop_rate.sleep();
	}
	return n;
}

int main(int argc, char **argv)
{
	angular_z = 0.2;
	Grass robot = Grass("RobotNode4",argc,argv,0.00,0.00,3);
	robot.run();
	return 0;
}
