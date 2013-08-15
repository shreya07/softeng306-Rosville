/*
 * Truck.h
 *
 *  Created on: Aug 14, 2013
 *      Author: surbhi
 */

#ifndef TRUCK_H_
#define TRUCK_H_

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"
#include "Robot.h"

class Truck:Robot
{
public:
  Truck(std::string robot_name, int argc, char **argv, double px, double py,int robot_number);
  ~Truck();
  ros::NodeHandle run();
  void stageOdom_callback (nav_msgs::Odometry msg);
};

#endif /* TRUCK_H_ */
