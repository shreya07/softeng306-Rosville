/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: Shreya
 */

#include "GhostSheep.h"
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

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 *  */
GhostSheep::GhostSheep(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
	//can do extra stuff here if you like
	//this-> x = px;
	//this-> y = py;
	distance = 15;
	linear_x = 0.0;
	angular_z = 0.0;
	theta = 0.0;
	constLinear = -0.2;
	nodeDistance = 30;
	targetTheta = 0;
	width = 1;
	length = 2;
	followSheep = true;


}
/*destrustor
 * I have not implemented it here but you should*/
GhostSheep::~GhostSheep()
{
	// TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void GhostSheep::stageOdom_callback(nav_msgs::Odometry msg){
	//int x = msg.linear.x;
	px = 15 + msg.pose.pose.position.x;
	py =20 + msg.pose.pose.position.y;
}

void GhostSheep::stagecmd_callback(geometry_msgs::Twist msg){
	//int x = msg.linear.x;
	if(followSheep) {
		linear_x = msg.linear.x;
		angular_z = msg.angular.z;
	} else {
		if(distance <= 1) {
			linear_x = 0.2;
			angular_z = 0;
		} else {
			linear_x = 0;
			angular_z = 0;
		}

	}

}

void GhostSheep::StageLaser_callback(sensor_msgs::LaserScan msg)
{
	distance = msg.ranges[20];
	se306_example::IdentityRequest request;
	ROS_INFO("distance: %f", distance);
	if(distance <= 10) {
		request.sender = robot_name;
		request.px = this->px+distance+(width/2.0);
		request.py = py;
		Request_pub.publish(request);
		//std_msgs::String status;
		//status.data = "stop";
		//Stop_pub.publish(status);
		ROS_INFO("Request sent");
	}


}

void GhostSheep::identityReply_callBack(se306_example::IdentityReply reply)
{
	ROS_INFO("reply received");
	if(reply.destination.compare(robot_name)==0) {
		if(reply.type.compare("grass")==0) {
			ROS_INFO("Grass detected");
			followSheep = false;
			std_msgs::String status;
			status.data = "follow";
			Follow_pub.publish(status);
		} else  {
			ROS_INFO("Don't know what it is");
		}
	}

}


/*The run method that we use to run the robot*/
ros::NodeHandle GhostSheep::run(){
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
	Request_pub = n.advertise<se306_example::IdentityRequest>("identityRequest", 1000);
	Reply_pub = n.advertise<se306_example::IdentityReply>("identityReply", 1000);
	Follow_pub = n.advertise<std_msgs::String>("Sheep"+robot_number+"/follow", 1000);

	std::stringstream ss;
	ss<<robot_name;

	ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>(robot_name+robot_number+"/odom",1000, &GhostSheep::stageOdom_callback, this);
	ros::Subscriber stageOdo_sub1 = n.subscribe<geometry_msgs::Twist>("Sheep"+robot_number+"/cmd_vel",1000, &GhostSheep::stagecmd_callback, this);
	ros::Subscriber StageLaser_sub3 = n.subscribe<sensor_msgs::LaserScan>(robot_name+robot_number+"/base_scan",1000, &GhostSheep::StageLaser_callback, this);
	ros::Subscriber StageOdo_sub4 = n.subscribe<se306_example::IdentityReply>("identityReply",1000, &GhostSheep::identityReply_callBack,this);

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

		theta += angular_z*9.0;

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
	GhostSheep robot = GhostSheep("Block",argc,argv,15,20,"One");
	robot.run();
	return 0;
}


