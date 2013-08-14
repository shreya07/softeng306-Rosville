/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: wasiq
 */

#include "Sheep1.h"
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
 *  */
Sheep1::Sheep1(std::string robot_name, int argc, char **argv,double px,double py, int robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
    //can do extra stuff here if you like
	//this-> x = px;
	//this-> y = py;
}
/*destrustor
 * I have not implemented it here but you should*/
Sheep1::~Sheep1()
{
  // TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void Sheep1::stageOdom_callback(nav_msgs::Odometry msg){
	//int x = msg.linear.x;
	px = 5 + msg.pose.pose.position.x;
	py =10 + msg.pose.pose.position.y;
}

/*The run method that we use to run the robot*/
ros::NodeHandle Sheep1::run(){
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
//advertise() function will tell ROS that you want to publish on a given topic_
		//to stage
		ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>("robot_0/cmd_vel",1000);

  std::stringstream ss;
  ss<<robot_name;
  //ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>(("robot_"+ss.str()+"/message_name"),1000, R3::stageOdom_callback);
  ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_0/odom",1000, &Sheep1::stageOdom_callback,this);
  //ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_0/odom",1000, &Sheep1::stageOdom_callback);
  //ros::Subscriber stageOdo_sub1 = n.subscribe<nav_msgs::Odometry>("robot_1/odom",1000, &Sheep1::stageOdom_callback);
  std::list<ros::Subscriber>::iterator it;
  it = subsList.end();
  subsList.insert(it,stageOdo_sub);


  ros::Rate loop_rate(10);

  /*define the while loop here*/
  while (ros::ok())
  {
    //ROS_INFO("OK");
    ros::spinOnce();
    loop_rate.sleep();
  }
  return n;
}

int main(int argc, char **argv)
{
	int i;
	for(i=0; i<5; i++) {
		std::stringstream ss;
		ss<<i;
		Sheep1 robot = Sheep1(("RobotNode"+ss.str()),argc,argv,0.00,0.00,i);

		robot.run();
	}
  return 0;
}

