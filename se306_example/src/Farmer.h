/*
 * Farmer.h
 *
 *  Created on: 15/08/2013
 *      Author: george
 */

#ifndef FARMER_H_
#define FARMER_H_
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"
#include "Robot.h"

class Farmer : Robot
{
public:
  double distance;
  geometry_msgs::Twist RobotNode_cmdvel;
  double linear_x;
  double angular_z;
  double theta;
  void StageLaser_callback(sensor_msgs::LaserScan msg);

  Farmer(std::string robot_name, int argc, char **argv, double px, double py, int robot_number);

  ~Farmer();

  ros::NodeHandle run();

  void stageOdom_callback(nav_msgs::Odometry msg);

};

#endif /* FARMER_H_ */
