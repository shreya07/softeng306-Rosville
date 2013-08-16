#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//velocity of the robot
double linear_x;
double angular_z;

//pose of the robot
double px;
double py;
double theta;

//distance of the robot to the nearest wall, max distance set at 30
double minDistance = 30.000000;

// truck is set to nowhere in sight
// border(truck) is set to nowhere in sight
bool truck = false;
bool border = false;

void StageOdom_callback(nav_msgs::Odometry msg) {
	//This is the call back function to process odometry messages coming from Stage.
	px = -5.0 + msg.pose.pose.position.x;
	py = 5.0 + msg.pose.pose.position.y;
	//ROS_INFO("Current x position is: %f", px);
	//ROS_INFO("Current y position is: %f", py);

	// Truck range: -25 <= px <= -21 , 47 <= py
	// Border range: 50.0 <= py
	if ((-25.0 <= px) && (px <= -21.0) && (47.0 <= py)) {
//		ROS_INFO("px = %f", px);
//		ROS_INFO("py = %f", py);
		truck = true;

		if (49.0 <= py) {
//			ROS_INFO("py = %f", py);
			border = true;
		}
	} else {
		truck = false;
		border = false;
	}
}

void StageLaser_callback(sensor_msgs::LaserScan msg) {
	minDistance = msg.ranges[0];
}

int main(int argc, char **argv) {

	//initialize robot parameters
	//Initial pose. This is same as the pose that you used in the world file to set	the robot pose.
	theta = 0.0;
	px = 10;
	py = 20;

	//Initial velocity
	linear_x = -2.0;
	angular_z = 0.0;

//You must call ros::init() first of all. ros::init() function needs to see argc and argv. The third argument is the name of the node
	ros::init(argc, argv, "RobotNode2");

//NodeHandle is the main access point to communicate with ros.
	ros::NodeHandle n;

//advertise() function will tell ROS that you want to publish on a given topic_
//to stage
	ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>(
			"robot_2/cmd_vel", 1000);

//subscribe to listen to messages coming from stage
	ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>(
			"robot_2/odom", 1000, StageOdom_callback);
	ros::Subscriber StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>(
			"robot_2/base_scan", 1000, StageLaser_callback);

	ros::Rate loop_rate(10);

//a count of how many messages we have sent
	int count = 0;

////messages
//velocity of this RobotNode
	geometry_msgs::Twist RobotNode_cmdvel;

	while (ros::ok()) {

		// farmer sees the truck, starts to walk/spin towards it
		if (truck) {
//			count++;

//			if (count < 20)
//			{
			ROS_INFO("Truck is here!");
//			ROS_INFO("count = %d", count);
			RobotNode_cmdvel.linear.x = -1;
			RobotNode_cmdvel.angular.z = -0.7;
//			}

			// farmer sees the border, stops
			if (border) {
//			if (count < 40)
//			{
				ROS_INFO("Border is here!");
				RobotNode_cmdvel.linear.x = 0;
				RobotNode_cmdvel.angular.z = 0;
//			} else {
//				RobotNode_cmdvel.linear.x = 7;
//				RobotNode_cmdvel.angular.z = 0;
//			}
			}
		} else {
//			count = 0;
			// farmer see the wall and avoid the wall
			if (minDistance <= 15.0) {
				RobotNode_cmdvel.linear.x = 3;
				RobotNode_cmdvel.angular.z = 20;

				// no wall in sight , farmer keep walking
			} else {
				RobotNode_cmdvel.linear.x = linear_x;
				RobotNode_cmdvel.angular.z = angular_z;
			}
		}

		//publish the message
		RobotNode_stage_pub.publish(RobotNode_cmdvel);

		ros::spinOnce();

		loop_rate.sleep();
		++count;
	}

	return 0;

}

