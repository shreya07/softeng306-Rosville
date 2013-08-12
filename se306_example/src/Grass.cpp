// headers
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include <math.h>

// position of robot
double px;
double py;
double pz;

int grow(int value) {
	pz = value+pz;
	return 0;
}

void Stagemsg_callback(nav_msgs::Odometry msg) {
	pz = pz + msg.pose.pose.position.z;
	ROS_INFO("Current z position is: %f", pz);
}

void Stagelaser_callback(sensor_msgs::LaserScan msg) {

}

// main method
int main(int argc, char **argv) {

	// initialise variables
	px = 25;
	py = 16;
	pz = 1;

	// initialize the node
	ros::init(argc, argv, "Grass");

	// create a handle for the node
	ros::NodeHandle nh;

	// publish messages to the stage
	ros::Publisher Grass_stage_pub = nh.advertise<nav_msgs::Odometry>("robot_3/odom", 1000);

	// subscribe to messages coming from stage
	ros::Subscriber StageOdo_sub = nh.subscribe<nav_msgs::Odometry>("robot_3/odom", 1000, Stagemsg_callback);
	ros::Subscriber Stagelaser_sub = nh.subscribe<sensor_msgs::LaserScan>("robot_3/base_scan", 1000, Stagelaser_callback);

	// set messages/sec to send
	ros::Rate rate(10);

	// count to keep track of how many messages being sent
	int count = 0;

	// publish co-ordinates using this variable
	nav_msgs::Odometry incrementZ;

	while (ros::ok()) {

		// messages to put on stage
		incrementZ.twist.twist.linear.z = pz + grow(count);

		// publish the message to the stage
		Grass_stage_pub.publish(incrementZ);

		ros::spinOnce();

		// sleep for remainder of sending messages IF waiting
		rate.sleep();

		// increment count
		++count;
		if (count > 100) {
			count = 0;
		}
	}
}
