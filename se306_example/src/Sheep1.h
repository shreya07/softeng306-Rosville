/*
 * R3.h
 *
 *  Created on: 12/08/2013
 *      Author: wasiq
 */

#ifndef R3_H_
#define R3_H_
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>


#include <sstream>
#include "math.h"
#include "Robot.h"
#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"

class Sheep1:Robot
{
public:
	double distance;
	geometry_msgs::Twist RobotNode_cmdvel;
	double linear_x;
	double constLinear;
	double angular_z;
	double theta;
	double nodeDistance;
	double targetTheta;
	bool followGhost;
	int width;
	int length;
	double abs_cmd_vel_linear_x;
	double abs_cmd_vel_angular_z;
	double prevpx;
	double prevpy;
	double PX_INIT;
	double PY_INIT;
	ros::Publisher RobotNode_stage_pub;
	ros::Publisher Request_pub;
	ros::Publisher Reply_pub;
	ros::Publisher Stop_pub;

	void StageLaser_callback(sensor_msgs::LaserScan msg);
	Sheep1(std::string robot_name, int argc, char **argv, double px, double py,std::string robot_number);
	~Sheep1();
	ros::NodeHandle run();
	void stageOdom_callback (nav_msgs::Odometry msg);
	void identityReply_callBack(se306_example::IdentityReply reply);
	void identityRequest_callBack(se306_example::IdentityRequest request);
	bool doesIntersect(float x, float y);
	void stageFollow_callback(std_msgs::String msg);
	void ghostcmd(geometry_msgs::Twist msg);
	std::list<double> calculateTheta(double theta, double distance);
	double yawFromQuaternion(double x, double y, double z, double w);

  //double y;
};

#endif /* R3_H_ */
