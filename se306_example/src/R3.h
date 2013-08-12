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

class R3
{
public:
  R3(std::string robot_name, int argc, char **argv);
  virtual ~R3();
  void run();
  void stageOdom_callback (nav_msgs::Odometry msg);
  //void stageOdom_callback(nav_msgs::Odometry& msg);
private:
  std::string robot_name;
  int argc;
  char **argv;
  std::list<ros::Subscriber> subsList;
  std::list<ros::Publisher> pubsList;
};

#endif /* R3_H_ */
