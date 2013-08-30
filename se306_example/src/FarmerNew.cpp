/*
 * FarmerNew.cpp
 *
 *  Created on: 28/08/2013
 *      Author: raoul
 */

#include "FarmerNew.h"
#include "std_msgs/String.h"

FarmerNew::FarmerNew(std::string robot_name, int argc, char **argv) :
Robot(robot_name, argc, argv)
{
  money = 0;
}

FarmerNew::~FarmerNew()
{
  // TODO Auto-generated destructor stub
}

void FarmerNew::stageOdom_callback(nav_msgs::Odometry msg)
{
  //This is the call back function to process odometry messages coming from Stage.
  px = initialX + msg.pose.pose.position.x;
  py = initialY + msg.pose.pose.position.y;
  //  ROS_INFO("Current x position is: %f", px);
  //  ROS_INFO("Current y position is: %f", py);

  ///
}

void FarmerNew::Teleop_callback(geometry_msgs::Twist msg)
{
  linear_x = linear_x + msg.linear.x;
  angular_z = angular_z + msg.angular.z;
  //ROS_INFO("Linear x is: %f", linear_x);
  //ROS_INFO("Angular z is: %f", angular_z);

}


void FarmerNew::sell_callback(std_msgs::String msg)
{
  money = money + 5;
  ROS_INFO("Farmer:%f", money);
}

ros::NodeHandle FarmerNew::run()
{
  ros::NodeHandle n = Robot::run();
  if(!n.getParam("px", this->initialX)){
    ROS_ERROR("[Farmer][%s] px not set",robot_name.c_str());


  }

  if(!n.getParam("py", initialY)){
    ROS_ERROR("[Farmer][%s] py not set",robot_name.c_str());

  }

  ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>(robot_name + "/odom", 1000,
                                                                 &FarmerNew::stageOdom_callback, this);
  ros::Subscriber Teleop_sub = n.subscribe<geometry_msgs::Twist>("/base_controller/command", 1000,
                                                                 &FarmerNew::Teleop_callback, this);
  ros::Subscriber sold_sub = n.subscribe<std_msgs::String>("SheepOne/sheepSoldReplyFarmer", 1000,
                                                                 &FarmerNew::sell_callback, this);
  ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>(robot_name + "/cmd_vel", 1000);
  ros::Rate loop_rate(10);

  /*define the while loop here*/
  while (ros::ok())
  {

    RobotNode_cmdvel.linear.x = linear_x;
    //RobotNode_cmdvel.linear.y = 0.2;
    RobotNode_cmdvel.angular.z = angular_z;
    RobotNode_stage_pub.publish(RobotNode_cmdvel);
    //RobotNode_stage_pub.publish(grass);
    //ROS_INFO("OK");
    ros::spinOnce();
    loop_rate.sleep();
    //            linear_x = 0;
    //            angular_z = 0;
  }

  return n;
}

int main(int argc, char **argv)
{
  FarmerNew robot = FarmerNew("Farmer", argc, argv);

  robot.run();
  return 0;
}

