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
#include "Custom.h"

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
	ros::Publisher RobotNode_stage_pub;

	void StageLaser_callback(sensor_msgs::LaserScan msg);
  Sheep1(std::string robot_name, int argc, char **argv, double px, double py,std::string robot_number);
  ~Sheep1();
  ros::NodeHandle run();
  void stageOdom_callback (nav_msgs::Odometry msg);
  void stageOdom_callback1 (se306_example::Custom grass);
  void turnSheep(void);
  double computeTheta(double x, double y);

  //double y;
};

#endif /* R3_H_ */
