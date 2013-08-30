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
#include "../msg_gen/cpp/include/se306_example/FollowSheep.h"
#include "../msg_gen/cpp/include/se306_example/eatGrass.h"
#include "../msg_gen/cpp/include/se306_example/cover.h"

class newSheep:Robot
{
public:
	double distance;
	geometry_msgs::Twist RobotNode_cmdvel;
	double linear_x;
	double angular_z;
	double theta;
	bool followGhost;
	int width;
	int length;
	double PX_INIT;
	double PY_INIT;
	ros::Publisher RobotNode_stage_pub;
	ros::Publisher Request_pub;
	ros::Publisher Reply_pub;
	ros::Publisher Stop_pub;
	ros::Publisher Eat_pub;
	ros::Publisher cover_pub;
	ros::Publisher sheepSoldReplyFarmer;
	bool once;
	double health;
	bool replyReceived;
	bool requestSent;
	bool grassDetected;
	bool grassReached;
	bool eaten;
	bool swarmDetected;
	double otherSheep_angular_z;
	double otherSheep_linear_x;
	double otherSheep_theta;
	double old_ang_z;
	std::string grassName;
	int gPX;
	int gPY;
	std::string grassNumber;


	void StageLaser_callback(sensor_msgs::LaserScan msg);
	newSheep(std::string robot_name, int argc, char **argv);
	~newSheep();
	ros::NodeHandle run();
	void swarmStuff();
	void stageOdom_callback (nav_msgs::Odometry msg);
	void identityReply_callBack(se306_example::IdentityReply reply);
	void identityRequest_callBack(se306_example::IdentityRequest request);
	bool doesIntersect(float x, float y);
	void ghostcmd(geometry_msgs::Twist msg);
	std::list<double> calculateTheta(double theta, double distance);
	double yawFromQuaternion(double x, double y, double z, double w);
	void grassEaten(std_msgs::String msg);
	void grassThings();
	void sellHandler(std_msgs::String msg);
  //double y;
};

#endif /* R3_H_ */
