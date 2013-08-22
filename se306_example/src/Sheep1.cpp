/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: Shreya
 */

#include "Sheep1.h"
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

#include "IdentityRequest.h"
#include "IdentityReply.h"

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 *  */
Sheep1::Sheep1(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
	//can do extra stuff here if you like
	//this-> x = px;
	//this-> y = py;
	distance = 15;
	linear_x = 0.2;
	angular_z = 0.0;
	theta = 120.0*M_PI/180.0;
	constLinear = -0.2;
	nodeDistance = 30;
	targetTheta = 0;
	width = 1;
	length = 2;

}
/*destrustor
 * I have not implemented it here but you should*/
Sheep1::~Sheep1()
{
	// TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void Sheep1::stageOdom_callback(nav_msgs::Odometry msg){
	//int x = msg.linear.x;
	px = 15 + msg.pose.pose.position.x;
	py =20 + msg.pose.pose.position.y;
}


void Sheep1::StageLaser_callback(sensor_msgs::LaserScan msg)
{
	distance = msg.ranges[0];

}

void Sheep1::identityReply_callBack(se306_example::IdentityReply)
{
	ROS_INFO("reply received");
}

void Sheep1::identityRequest_callBack(se306_example::IdentityRequest request)
{
	ROS_INFO("Request received");
	bool result = doesIntersect(request.px, request.py);
	ROS_INFO("does intersect?"+result);

}

bool Sheep1::doesIntersect(int x, int y) {
	int leftX = px-(width/2.0);
	int rightX = px+(width/2.0);
	int top = py+(length/2.0);
	int bottom = py-(length/2.0);
	if(leftX >= x && rightX <= x) {
		if(top <= y && bottom >= y) {
			ROS_INFO("Whithin bounds");
			return true;
		}
	}
	return false;
}

/*The run method that we use to run the robot*/
ros::NodeHandle Sheep1::run(){
	/*always call this line it defines the Nodehandler
	 * it also creates the callback for the postion message*/
	ros::NodeHandle n = Robot::run();
	/*To define a new message
	 * std::stringstream ss;
	 * ss<<robot_name;
	 * ros::Subscriber name_of_message = n.subscribe<nav_msgs::Odometry>("robot_"+ss.str()+"/message_name",1000, &Robot::callback_function,this);
	 *
	 * Then add to the list of subscribers
	 *   std::list<ros::Subscriber>::iterator it;
	 *   it = subsList.end();
	 *   subsList.insert(it,StageOdo_sub);
	 *
	 * Publishers are defined in exactly the same way as they are in the given examoles
	 * But you must add them to the publisherList*/
	//advertise() function will tell ROS that you want to publish on a given topic_
	//to stage
	RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>(robot_name+robot_number+"/cmd_vel",1000);
	//ros::Publisher RobotNode_stage_pub1 = n.advertise<geometry_msgs::Twist>("grass",1000);
	ros::Publisher RobotNode_stage_pub1 = n.advertise<se306_example::IdentityRequest>("identityRequest", 1000);
	ros::Publisher RobotNode_stage_pub2 = n.advertise<se306_example::IdentityReply>("identityReply", 1000);
	std::stringstream ss;
	ss<<robot_name;
	ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>(robot_name+robot_number+"/odom",1000, &Sheep1::stageOdom_callback, this);
	ros::Subscriber stageOdo_sub1 = n.subscribe<se306_example::IdentityRequest>("identityRequest",1000, &Sheep1::identityRequest_callBack, this);
	ros::Subscriber StageOdo_sub2 = n.subscribe<se306_example::IdentityReply>("identityReply",1000, &Sheep1::identityReply_callBack);
	ros::Subscriber StageLaser_sub3 = n.subscribe<sensor_msgs::LaserScan>(robot_name+robot_number+"/base_scan",1000, &Sheep1::StageLaser_callback, this);

	std::list<ros::Subscriber>::iterator it;
	it = subsList.end();
	subsList.insert(it,stageOdo_sub);

	//double th = 90*M_PI/2.0;
	ros::Rate loop_rate(10);
	nav_msgs::Odometry odom;
	geometry_msgs::Quaternion odom_quat;

	//se306_example::Grass grass;

	/*define the while loop here*/
	while (ros::ok())
	{

		// RobotNode_cmdvel.angular.x = 0.2;
		//RobotNode_cmdvel.angular.y = 0.5;

		RobotNode_cmdvel.linear.x = linear_x;
		//RobotNode_cmdvel.linear.y = 0.2;
		RobotNode_cmdvel.angular.z = angular_z;

		RobotNode_stage_pub.publish(RobotNode_cmdvel);
		//RobotNode_stage_pub.publish(grass);
		//ROS_INFO("OK");
		ros::spinOnce();
		loop_rate.sleep();
	}
	return n;

}

int main(int argc, char **argv)
{
	Sheep1 robot = Sheep1("Sheep",argc,argv,15,20,"One");

	robot.run();
	return 0;
}


