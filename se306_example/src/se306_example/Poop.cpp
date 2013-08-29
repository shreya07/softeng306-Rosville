/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: Shreya
 */

#include "Poop.h"
#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include "Custom.h"

#include <sstream>
#include "math.h"
#include "Robot.h"
#include "std_msgs/Bool.h"

#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"

Poop::Poop(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
	distance = 15;
	linear_x = 0.0;
	angular_z = 0.0;
	theta = 120.0*M_PI/180.0;
	constLinear = -0.2;
	nodeDistance = 30;
	targetTheta = 0;
	width = 1;
	length = 2;
	doStop = false;

}
/*destrustor
 * I have not implemented it here but you should*/
Poop::~Poop()
{
	// TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void Poop::stageOdom_callback(nav_msgs::Odometry msg){
	//int x = msg.linear.x;
	px = 15 + msg.pose.pose.position.x;
	py = 20 + msg.pose.pose.position.y;
}

void Poop::stagecmd_callback(geometry_msgs::Twist msg){
	//int x = msg.linear.x;
	if(doStop) {
		linear_x = 0;
		angular_z = 0;
	} else {
		linear_x = msg.linear.x;
		angular_z = msg.angular.z;
	}

}


void Poop::stageStop_callback(std_msgs::String msg)
{
	if(msg.data.compare("stop") == 0) {
		if(!doStop) {
			doStop = true;
		}
	}

}

void Poop::requestPoop(const std_msgs::String::ConstPtr& request) {
	if (request->data.compare("Request") == 0) {
		linear_x = 0;
		angular_z = 0;
	}
}


/*The run method that we use to run the robot*/
ros::NodeHandle Poop::run(){

	ros::NodeHandle n = Robot::run();

	publishPoop = n.advertise<geometry_msgs::Twist>(robot_name+robot_number+"/cmd_vel",1000);


	// initialize subscribers listen to sheep position and velocity
	sheepVel = n.subscribe<geometry_msgs::Twist>("SheepOne/cmd_vel",1000, &Poop::stagecmd_callback, this);
	poopReq = n.subscribe<std_msgs::String>("poop", 1000, &Poop::requestPoop, this);

	// Add subscribers to subscriber list
	std::list<ros::Subscriber>::iterator it;
	it = subsList.end();
	subsList.insert(it,sheepPos);
	subsList.insert(it,sheepVel);

	// set to 10 messages per second
	ros::Rate loop_rate(10);

	// initialize type variables to use in publishing
	nav_msgs::Odometry odom;
	geometry_msgs::Quaternion odom_quat;

	/*define the while loop here*/
	while (ros::ok())
	{
		// set poop velocity to match sheep poop
		poopVel.linear.x = linear_x;
		poopVel.angular.z = angular_z;

		publishPoop.publish(poopVel);

		ros::spinOnce();
		loop_rate.sleep();
	}
	return n;

}

int main(int argc, char **argv)
{
	Poop robot = Poop("Poop",argc,argv,5,1,"One");
	robot.run();
	return 0;
}


