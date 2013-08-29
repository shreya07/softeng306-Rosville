/*
 * Gate.h
 *
 *  Created on: Aug 14, 2013
 *      Author: surbhi
 */

#ifndef Gate_H_
#define Gate_H_

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"
#include "Robot.h"

class Gate:Robot
{
public:
  bool isHorizontal;
  bool isOpen;
  std::string directionToOpen;
  double initialX;
  double initialY;

  Gate(std::string robot_name, int argc, char **argv);
  ~Gate();
  ros::NodeHandle run();
  ros::Publisher RobotNode_stage_pub;
  bool shouldMoveGate;
  double destination;
  geometry_msgs::Twist moveMessage;
  void stageOdom_callback (nav_msgs::Odometry msg);
  void Gate_callback(std_msgs::String);
  void moveGate();


};

#endif /* Gate_H_ */
