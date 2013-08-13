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

class R3:Robot
{
public:
  R3(std::string robot_name, int argc, char **argv, double px, double py,int robot_number);
  ~R3();
  ros::NodeHandle run();
  void stageOdom_callback (nav_msgs::Odometry msg);
};

#endif /* R3_H_ */
