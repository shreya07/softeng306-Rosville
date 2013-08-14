#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//velocity of the robot
double linear_x; // Move forward or backward (+/-)
double angular_z; // Turn counter-clockwise or clockwise (+ for counter / - for clockwise)

//pose of the robot
double px;
double py;
double theta;

void StageOdom_callback(nav_msgs::Odometry msg)
{
	//This is the call back function to process odometry messages coming from Stage. 	
	px = 5 + msg.pose.pose.position.x;
	py =10 + msg.pose.pose.position.y;
	ROS_INFO("Current x position is: %f", px);
	ROS_INFO("Current y position is: %f", py);
}


void StageLaser_callback(sensor_msgs::LaserScan msg)
{
	//This is the callback function to process laser scan messages
	//you can access the range data from msg.ranges[i]. i = sample number
//	int numberOfvaluesInRange = (msg.angle_max - msg.angle_min)/msg.angle_increment;	
//	ROS_INFO ("Number of values in range id : %d",numberOfvaluesInRange);

//	for (int i = 0; i < numberOfvaluesInRange; i++)
//	{
//		ROS_INFO("ranges[%d] = %f",i,msg.ranges[i]);
//	}	
}

// Method:Copy_callback takes inputs of linear and angular velocity
void Copy_callback(geometry_msgs::Twist msg) {
	linear_x = msg.linear.x;
	angular_z = msg.angular.z;
}

int main(int argc, char **argv)
{

 //initialize robot parameters
	//Initial pose. This is same as the pose that you used in the world file to set	the robot pose.
	theta = M_PI/2.0;
	px = 10;
	py = 20;
	
	//Initial velocity
	linear_x = 5;
	angular_z = 0;
	
//You must call ros::init() first of all. ros::init() function needs to see argc and argv. The third argument is the name of the node
ros::init(argc, argv, "Farmer");

//NodeHandle is the main access point to communicate with ros.
ros::NodeHandle n;

//advertise() function will tell ROS that you want to publish on a given topic_
//to stage
ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>("robot_3/cmd_vel",1000); 

//subscribe to listen to messages coming from stage
// robot_num, seems like can't change this name. However can stage appeared name in stage!
ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_3/odom",1000, StageOdom_callback);
ros::Subscriber StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_3/base_scan",1000,StageLaser_callback);
//ros::Subscriber RobotCopy_sub = n.subscribe<geometry_msgs::Twist>("robot_0/cmd_vel",1000, Copy_callback);

ros::Rate loop_rate(10);

//a count of howmany messages we have sent
int count = 0;

////messages
//velocity of this RobotNode
geometry_msgs::Twist RobotNode_cmdvel;
double px2 = 1.0; // Current Farmer position x
double SIGN = 1.0;
//double px2 = StageOdom_callback.msg.pose.pose.position.x;
//double py2 = 10+msg.pose.pose.position.y;

while (ros::ok())
{
	//messages to stage
	RobotNode_cmdvel.linear.x = (SIGN * linear_x);
	RobotNode_cmdvel.angular.z = angular_z;

	//publish the message
	ROS_INFO("px2: %f", px2);
	RobotNode_stage_pub.publish(RobotNode_cmdvel);

	// Farmer currently walks at 0.1 per cycle
	px2 = px2 + (SIGN * 0.1);

	// Farmer reached the far left wall
	if (px2 < 0.0)
	{
		ROS_INFO("I walk back again!");
		SIGN = 1.0;
	}
	// Farmer reached the far right wall
	else if (px2 > 40.5)
	{
		ROS_INFO("I walk back again!");
		SIGN = -1.0;
	}

//	if ((px == px2) && (py == py2))
//	{
//		// When hit the boundary, move back a few steps
//		ROS_INFO("Ouch! I hit the wall.");
//		ROS_INFO("I walk back!");
//
//		linear_x = -linear_x;
//
//		// Turn counter-clockwise on the spot by 90 degrees
//		
//	}
//
//	// Update current positions x,y
//	px2 = px;
//	py2 = py;

	ros::spinOnce();

	loop_rate.sleep();
	++count;
} 	

return 0;

}
