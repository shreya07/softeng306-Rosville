/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: wasiq
 */

#include "Sheep1.h"
#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include "Custom.h"

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
Sheep1::Sheep1(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
    //can do extra stuff here if you like
	//this-> x = px;
	//this-> y = py;
	distance = 30;
	linear_x = -0.2;
	angular_z = 0.0;
	theta = 120.0*M_PI/180.0;
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
	//ROS_INFO("x: %f", msg.pose.pose.orientation.x);
	//ROS_INFO("y: %f", msg.pose.pose.orientation.y);
	//ROS_INFO("W: %f", msg.pose.pose.orientation.w);
	//ROS_INFO("z: %f", msg.pose.pose.orientation.z);
	// w = 1 robot moving -x direction
	if(msg.pose.pose.orientation.w == 1) {
		theta = 0;
	} else if(msg.pose.pose.orientation.w >= 0.7 && msg.pose.pose.orientation.z >= 0.7) {
	// w = 0.7 and z = 0.7 robot moving -y direction
		theta = 270;
	} else if(msg.pose.pose.orientation.z <= -0.7) {
	// z = -0.7 robot moving +y direction
		theta = 90;
	} else if(msg.pose.pose.orientation.w == -1){
	// w = -1 robot moving +x direction
		theta = 180;
	}
}

void Sheep1::stageOdom_callback1(se306_example::Custom grass){
	/*if(theta == 0) {
		if(((10+msg.pose.pose.position.y) < (py+1)) && ((10+msg.pose.pose.position.y) > (py-1))) {
			distance = px - (3+msg.pose.pose.position.x);
		}
	}
	ROS_INFO("x: %f", (3+msg.pose.pose.position.x));
	ROS_INFO("y: %f", (10+msg.pose.pose.position.y));*/

	if(theta == 0) {
		if(((grass.py) < (py+1)) && ((grass.py) > (py-1))) {
			distance = px - (grass.px);
		}
	}
	ROS_INFO("x: %f", grass.px);
	ROS_INFO("y: %f", grass.py);

}

void Sheep1::StageLaser_callback(sensor_msgs::LaserScan msg)
{
	int i;
	for(i=0; i<10; i++) {
		distance += msg.ranges[i];
		//ROS_INFO("distance: %f", msg.ranges[i]);
	}
	distance = distance/10;
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
  ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>(robot_name+robot_number+"/cmd_vel",1000);
  //ros::Publisher RobotNode_stage_pub1 = n.advertise<geometry_msgs::Twist>("grass",1000);
  ros::Publisher RobotNode_stage_pub1 = n.advertise<se306_example::Custom>("sheep", 1000);

  std::stringstream ss;
  ss<<robot_name;
  //ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>(("robot_"+ss.str()+"/message_name"),1000, R3::stageOdom_callback);
  //ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>(robot_name+robot_number+"/cmd_vel",1000, &Sheep1::stageOdom_callback, this);
  ros::Subscriber stageOdo_sub1 = n.subscribe<se306_example::Custom>("grass",1000, &Sheep1::stageOdom_callback1, this);

  ros::Subscriber StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>(robot_name+robot_number+"/base_scan",1000, &Sheep1::StageLaser_callback, this);

  //std::list<ros::Subscriber>::iterator it;
  //it = subsList.end();
  //subsList.insert(it,stageOdo_sub);

  //double th = 90*M_PI/2.0;
  ros::Rate loop_rate(10);
  nav_msgs::Odometry odom;
  geometry_msgs::Quaternion odom_quat;

  //se306_example::Grass grass;

  /*define the while loop here*/
  while (ros::ok())
  {

	 // RobotNode_cmdvel.angular.x = 0.2;
	  //RobotNode_cmdvel.angular.y = 0.5;

	  if(distance <= 1.0) {
		  RobotNode_cmdvel.linear.x = 0.5;
	  		RobotNode_cmdvel.linear.y = 0.0;
	  		RobotNode_cmdvel.angular.z = 18.0;
	  		//odom_quat = tf::createQuaternionMsgFromYaw(th);
	  		//odom.pose.pose.orientation = odom_quat;
	  	} else {
	  		RobotNode_cmdvel.linear.x = linear_x;
	  		RobotNode_cmdvel.linear.y = 0.2;
	  		RobotNode_cmdvel.angular.z = angular_z;
	  	}
	  RobotNode_stage_pub.publish(RobotNode_cmdvel);
	  //RobotNode_stage_pub.publish(grass);
    //ROS_INFO("OK");
    ros::spinOnce();
    loop_rate.sleep();
  }
  return n;
}

int main(int argc, char **argv)
{
		Sheep1 robot = Sheep1("Sheep",argc,argv,5,10,"One");

		robot.run();
  return 0;
}



