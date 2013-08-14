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
#include "Robot.h"
//#include <thread>

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 *  */
R3::R3(std::string robot_name, int argc, char **argv,double px,double py, int robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
    //can do extra stuff here if you like
}
/*destrustor
 * I have not implemented it here but you should*/
R3::~R3()
{
  // TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void R3::stageOdom_callback(nav_msgs::Odometry msg){
  ROS_INFO("HELLO");
}

/*The run method that we use to run the robot*/
ros::NodeHandle R3::run(){
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
  ros::Rate loop_rate(10);
  /*define the while loop here*/
  while (ros::ok())
  {
    //ROS_INFO("OK");
    ros::spinOnce();
    loop_rate.sleep();
  }
  //hij
  return n;
}

int main(int argc, char **argv)
{
  R3 robot = R3("RobotNode3",argc,argv,0.00,0.00,3);
  robot.run();
  return 0;
}

