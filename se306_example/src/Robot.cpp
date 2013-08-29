/*
 * Robot.cpp
 *
 *  Created on: 12/08/2013
 *      Author: wasiq
 */

#include "Robot.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <string>


#include <sstream>
#include "math.h"

Robot::Robot(std::string robot_name, int argc, char **argv)
{
  this-> robot_name = robot_name;
  this-> argc = argc;
  this-> argv = argv;
  this->px=0;
  this->py=0;

  //this->robot_number = robot_number;
}

Robot::~Robot()
{
  // TODO Auto-generated destructor stub
}


ros::NodeHandle Robot::run(){
  //running the ros init command
  ros::init(argc, argv, robot_name);


  ros::NodeHandle n("~");

//ros::init(argc, argv, robot_name+robot_number);

  //n.getParam("name",robot_name);
 // ROS_INFO(ros::this_node::getName().c_str());

  robot_name=ros::this_node::getName();

  /*The next two lines convert an int to a String*/
  //subscribe to the position message of this class


  //ROS_INFO(robot_name.c_str());
  std_msgs::String odom;
  odom.data= "odom";
  ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>(odom.data.c_str(),1000, &Robot::stageOdom_callback,this);

  /*add the subscriber to the subscriber list
   * use the iterator to move to the back of the list and add to it
   * copy and paste this if you need to add another cubscriber or pucblisher to
   * the list*/
  std::list<ros::Subscriber>::iterator it;
  it = subsList.end();
  subsList.insert(it,StageOdo_sub);

  /*return the nodehandler object for use in other classes.
   * each robot class will have overriden this method
   * if you are planning to extend the class you create further
   * retrun the nodehadler
   * otherwise return a null object*/

  return n;
}

