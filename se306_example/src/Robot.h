/*
 * Robot.h
 *
 *  Created on: 12/08/2013
 *      Author: wasiq
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

/*This is the base class for all the robot classes*/
class Robot
{
public:
  /*constructor
  * @param robot_name = "RobotName1" or the number of the robot that you are using.
  * Basically it is the string that you put in the ros::init folder
  * argc, argv are from the main method
  * px, py is the original position of the robot
  * robot_number is the numebr of the robot that you created
  * for example if your robot_name ="RobotNode1" then your robot_number is 1*/
  Robot(std::string robot_name, int argc, char **argv,double px,double py, int robot_number);

  /*destructor
   * This is to free up memory, please implement this and free up all your memory
   * e.g set all your fields etc*/
  virtual ~Robot();

  /*the run method that everyone uses to run their robot. A tutorial is available on R3.cpp*/
  ros::NodeHandle run();

  /* the callback function for the position. You need to implement this yourself*/
  virtual void stageOdom_callback (nav_msgs::Odometry msg)=0;
protected:
  std::string robot_name;
  int argc;
  char **argv;
  double px;
  double py;
  int robot_number;

  /*lists of subscribers and publishers, please remember to add your publishers and
   * subscribers to this list*/
  std::list<ros::Subscriber> subsList;
  std::list<ros::Publisher> pubsList;
};

#endif /* ROBOT_H_ */
