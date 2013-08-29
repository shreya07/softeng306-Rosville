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

class GhostSheep:Robot
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
	int width;
	int length;
	ros::Publisher RobotNode_stage_pub;
	ros::Publisher Request_pub;
	ros::Publisher Reply_pub;
	ros::Publisher Follow_pub;
	bool doStop;
	bool followSheep;

  GhostSheep(std::string robot_name, int argc, char **argv, double px, double py,std::string robot_number);
  ~GhostSheep();
  ros::NodeHandle run();
  void stageOdom_callback (nav_msgs::Odometry msg);
  void stagecmd_callback (geometry_msgs::Twist msg);
  void stageStop_callback (std_msgs::String msg);
  void identityReply_callBack(se306_example::IdentityReply reply);
  void identityRequest_callBack(se306_example::IdentityRequest request);
  bool doesIntersect(float x, float y);
  void StageLaser_callback(sensor_msgs::LaserScan msg);
  std::list<double> calculateTheta(double theta, double distance);
  void changeFollow(bool follow);
  double yawFromQuaternion(double x, double y, double z, double w);

  //double y;
};

#endif /* R3_H_ */
