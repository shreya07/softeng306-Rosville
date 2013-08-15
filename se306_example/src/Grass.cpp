/*
 * Grass.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: Kirushi Arunthavasothy
 */

#include "Grass.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Custom.h"

#include <sstream>
#include "math.h"
#include "Robot.h"

Grass::Grass(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number) {
  moistCont = 0;
  height = 0;
  angular_z = 0.2;
}

Grass::~Grass()
{
  // TODO Auto-generated destructor stub
}

// CALL BACK METHOD TO DELEGATE ITS POSITION
void Grass::stageOdom_callback(nav_msgs::Odometry msg){
   this->px = this->px+msg.pose.pose.position.x;
   this->py = this->py+msg.pose.pose.position.y;
}

// CHECKS RAINFALL AND INCREMENTS/DECREMENTS MOISTURE LEVEL
void Grass::rainfall_callback(const std_msgs::String::ConstPtr& rainfall) {

  //ROS_INFO("I heard: [%s]", rainfall->data.c_str());

  if (rainfall->data.compare("Sunny")==0) {
    moistCont = moistCont + 1;
  } else if (rainfall->data.compare("Raining")==0) {
    moistCont = moistCont - 1;
  }

  //grow(moistCont);
}

// INCREASES AND DECREASES HEIGHT DEPENDING ON MOISTURE
void Grass::grow(double moisture) {

  if (moisture > 0) {
    height = height+moisture/100;
  } else if (moisture < 5 && height != 0) {
    height = height-moisture/10;
  }
}

void Grass::spinCallback(se306_example::Custom msg) {
  if ((this->px-msg.px) <= 1) {
    if ((this->py-msg.py) <= 1) {
      this->angular_z = 0.5;
    }
  }
}

ros::NodeHandle Grass::run(){

  ros::NodeHandle n = Robot::run();

  // LISTEN
  ros::Subscriber receive_rainfall = n.subscribe<std_msgs::String>("weather/status",1000, &Grass::rainfall_callback, this);
  ros::Subscriber sheepPos = n.subscribe<se306_example::Custom>("sheep",1000, &Grass::spinCallback, this);

  // ADD SUBSCRIBERS TO LIST
  std::list<ros::Subscriber>::iterator it;
  it = subsList.end();
  subsList.insert(it,receive_rainfall);

  // TO CHANGE ANGULAR VELOCITY SET A PUBLISHER TO LISTEN ON CMD_VEL
  ros::Publisher spin = n.advertise<geometry_msgs::Twist>(robot_name+robot_number+"/cmd_vel",1000);


  // CREATE MOISTURE AND HEIGHT TOPICS TO PUBLISH TOWARDS
  ros::Publisher grassPos = n.advertise<se306_example::Custom>("grass",1000);
  ros::Publisher grassHeight = n.advertise<std_msgs::String>("grass/height", 1000);



  // ADD PUBLISHERS TO LIST
  std::list<ros::Publisher>::iterator iter;
  iter = pubsList.end();
  pubsList.insert(iter, spin);


  // SENDING AT 10 MESSAGES A SECOND
  ros::Rate loop_rate(10);


  // INITIALIZE VARIABLES TO PUBLISH
  std_msgs::String heightOfGrass;
  std_msgs::String moisture;
  geometry_msgs::Twist angular;
  se306_example::Custom grass;

//  // SET ANGULAR VELOV
//  this->angular_z = 0.2;

  grass.px = this->px;
  grass.py = this->py;
  while (ros::ok())
  {
    grow(this->moistCont);
    angular.angular.z = angular_z;
    ROS_INFO("Value is [%lf]", angular.angular.z);

    // PUBLISH
    grassPos.publish(grass);
    spin.publish(angular);


    ROS_INFO("Current value of Moisture is %f",this->moistCont);
    ROS_INFO("Current value of Height is %f",this->height);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return n;
}

int main(int argc, char **argv)
{
  Grass robot = Grass("Grass",argc,argv,10,20,"One");
  robot.run();
  return 0;
}
