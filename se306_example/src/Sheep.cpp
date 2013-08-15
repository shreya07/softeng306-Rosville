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

double x;
double y;

float distance;

void StageOdom_callback(nav_msgs::Odometry msg)
{
	//This is the call back function to process odometry messages coming from Stage.
	px = 5 + msg.pose.pose.position.x;
	py =10 + msg.pose.pose.position.y;
	ROS_INFO("Current x position is: %f", px);
	ROS_INFO("Current y position is: %f", py);
}

void StageOdom_callback1(nav_msgs::Odometry msg)
{
	//This is the call back function to process odometry messages coming from Stage.
	x = 5 + msg.pose.pose.position.x;
	y =10 + msg.pose.pose.position.y;
	ROS_INFO("Current x position is: %f", x);
	ROS_INFO("Current y position is: %f", y);
}


void StageLaser_callback(sensor_msgs::LaserScan msg)
{
	//This is the callback function to process laser scan messages
	//you can access the range data from msg.ranges[i]. i = sample number

	int i;
	/*for(i=0; i<msg.ranges.size(); i++) {
		//distance += msg.ranges[i];
		ROS_INFO("distance: %f", msg.ranges[i]);
	}*/
	distance = msg.ranges[0];

	ROS_INFO("max angle: %f", msg.angle_max);
	ROS_INFO("min angle: %f", msg.angle_min);

	ROS_INFO("max distance: %f", msg.range_max);

}

int main(int argc, char **argv)
{

 //initialize robot parameters
	//Initial pose. This is same as the pose that you used in the world file to set	the robot pose.
	theta = M_PI/2.0;
	px = 5;
	py = 10;

	//Initial velocity
	linear_x = 0.2;
	angular_z = 0.0;

//You must call ros::init() first of all. ros::init() function needs to see argc and argv. The third argument is the name of the node
ros::init(argc, argv, "RobotNode0");

//NodeHandle is the main access point to communicate with ros.
ros::NodeHandle n;

//advertise() function will tell ROS that you want to publish on a given topic_
//to stage
ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>("robot_0/cmd_vel",1000);

//subscribe to listen to messages coming from stage
ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_0/odom",1000, StageOdom_callback);
ros::Subscriber StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_0/base_scan",1000,StageLaser_callback);
ros::Subscriber StageOdo_sub1 = n.subscribe<nav_msgs::Odometry>("robot_1/odom",1000, StageOdom_callback1);
ros::Subscriber StageOdo_sub2 = n.subscribe<nav_msgs::Odometry>("robot_2/odom",1000, StageOdom_callback1);

ros::Rate loop_rate(10);

//a count of howmany messages we have sent
int count = 0;

////messages
//velocity of this RobotNode
geometry_msgs::Twist RobotNode_cmdvel;

while (ros::ok())
{

	//messages to stage
	RobotNode_cmdvel.linear.x = linear_x;
	RobotNode_cmdvel.angular.z = angular_z;

	//publish the message
	RobotNode_stage_pub.publish(RobotNode_cmdvel);

	//int point = RobotNode_cmdvel.Ptr;
	if(distance <= 1.0) {
		linear_x = -linear_x;
	}


	ros::spinOnce();

	loop_rate.sleep();
	++count;
}

return 0;

}
