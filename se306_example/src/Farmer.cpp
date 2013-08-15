/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: wasiq
 */

#include "Farmer.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"
#include "Robot.h"

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 * */
Farmer::Farmer(std::string robot_name, int argc, char **argv, double px, double py, int robot_number) :
    Robot(robot_name, argc, argv, px, py, robot_number)
{
  //can do extra stuff here if you like
//this-> x = px;
//this-> y = py;
  distance = 30.000000;
  linear_x = -2.0;
  angular_z = 0.0;
  theta = 0.0;
}
/*destrustor
 * I have not implemented it here but you should*/
Farmer::~Farmer()
{
  // TODO Auto-generated destructor stub
}

//This is the call back function to process odometry messages coming from Stage.
void Farmer::stageOdom_callback(nav_msgs::Odometry msg)
{
  px = 5 + msg.pose.pose.position.x;
  py = 10 + msg.pose.pose.position.y;
}

// this is the callback function of the laser scan
void Farmer::StageLaser_callback(sensor_msgs::LaserScan msg)
{
  // distance to the nearest wall straight ahead
  distance = msg.ranges[0];
}

/*The run method that we use to run the robot*/
ros::NodeHandle Farmer::run()
{
  /*always call this line it defines the Nodehandler
   * it also creates the callback for the postion message*/
  ros::NodeHandle n = Robot::run();
  /*To define a new message
   * std::stringstream ss;
   * ss<<robot_name;
   * ros::Subscriber name_of_message = n.subscribe<nav_msgs::Odometry>("robot_"+ss.str()+"/message_name",1000, &Robot::callback_function,this);
   *
   * Then add to the list of subscribers
   *   std::list<ros::Subscriber>::iterator it;
   *   it = subsList.end();
   *   subsList.insert(it,StageOdo_sub);
   *
   * Publishers are defined in exactly the same way as they are in the given examoles
   * But you must add them to the publisherList*/

  // define stageOdo_sub
  // add stageOdo_sub to the subscriberList
  std::stringstream ss;
  ss << robot_name;
  ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_" + ss.str() + "/odom", 1000,
                                                                 &Farmer::stageOdom_callback, this);
  std::list<ros::Subscriber>::iterator its;
  its = subsList.end();
  subsList.insert(its, stageOdo_sub);

  // define StageLaser_sub
  // add StageLaser_sub to the subscriberList
  std::stringstream ss;
  ss << robot_name;
  ros::Subscriber StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_" + ss.str() + "/base_scan", 1000,
                                                                       &Farmer::StageLaser_callback, this);
  std::list<ros::Subscriber>::iterator its;
  its = subsList.end();
  subsList.insert(its, StageLaser_sub);

  // define RobotNode_stage_pub
  // add RobotNode_stage_pub to the publisherList
  std::stringstream ss;
  ss << robot_name;
  ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>("robot_" + ss.str() + "/cmd_vel", 1000, this);

  std::list<ros::Publisher>::iterator itp;
  itp = pubsList.end();
  pubsList.insert(itp, RobotNode_stage_pub);

  // frequency at 10Hz
  ros::Rate loop_rate(10);

  /*define the while loop here*/
  while (ros::ok())
  {
    // check if a wall is within sight
    if (distance <= 15.0)
    {
      // move away while turning
      RobotNode_cmdvel.linear.x = 4.0;
      RobotNode_cmdvel.angular.z = 20;
    }
    else
    {
      // continue to walk
      RobotNode_cmdvel.linear.x = linear_x;
      RobotNode_cmdvel.angular.z = angular_z;
    }

    //publish the message
    RobotNode_stage_pub.publish(RobotNode_cmdvel);

    ros::spinOnce();

    loop_rate.sleep();
  }
  return n;
}

int main(int argc, char **argv)
{
  Farmer robot = Farmer("RobotNode2", argc, argv, 10, 10, 2);

  robot.run();
  return 0;
}
