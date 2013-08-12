/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: wasiq
 */

#include "R3.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

R3::R3(std::string robot_name, int argc, char **argv)
{
  this-> robot_name = robot_name;
  this-> argc = argc;
  this-> argv = argv;

  // TODO Auto-generated constructor stud
}

R3::~R3()
{
  // TODO Auto-generated destructor stub
}

void R3::stageOdom_callback(nav_msgs::Odometry msg){
  ROS_INFO("HELLO");
}


void R3::run(){
  ros::init(argc, argv, robot_name);
  ros::NodeHandle n;
  //R3 robot;
  //ros::Subscriber scan_filter_sub_= n.subscribe("scan", 50, &R3::stageOdom_callback, this);
  ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom",1000, &R3::stageOdom_callback,this);
  //ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel",1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    int x=0; //ROS_INFO("OK");
    ros::spinOnce();

    loop_rate.sleep();
  }
}

int main(int argc, char **argv)
{
  R3 robot = R3("RobotNode2",argc,argv);
  robot.run();
  return 0;
}
//void R3::stageOdom_callback(nav_msgs::Odometry& msg){

//}

