/*
 * FarmerNew.h
 *
 *  Created on: 28/08/2013
 *      Author: raoul
 */

#ifndef FARMERNEW_H_
#define FARMERNEW_H_

#include "Robot.h"
#include "std_msgs/String.h"

class FarmerNew : public Robot
{
public:
  geometry_msgs::Twist RobotNode_cmdvel;
  double linear_x;
  double angular_z;
  double money;
  FarmerNew(std::string robot_name, int argc, char **argv, double px, double py, std::string robot_number);
  virtual ~FarmerNew();
  void stageOdom_callback(nav_msgs::Odometry msg);
  void StageLaser_callback(sensor_msgs::LaserScan msg);
  void Teleop_callback(geometry_msgs::Twist msg);
  void sell_callback(std_msgs::String);
  ros::NodeHandle run();
};

#endif /* FARMERNEW_H_ */
