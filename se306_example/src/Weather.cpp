/*
 * Weather.cpp
 *
 *  Created on: 14/08/2013
 *      Author: wasiq
 */

#include "Weather.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/String.h>

#include <sstream>
#include "math.h"

Weather::Weather()
{
  // TODO Auto-generated constructor stub

}

Weather::~Weather()
{
  // TODO Auto-generated destructor stub
}

int main (int argc, char**  argv){
  ros::init(argc, argv, "RobotNode3");
  ros::NodeHandle n;
  std_msgs::String msg;
    ros::Publisher RobotNode_stage_pub = n.advertise<std_msgs::String>("weather/status",1000);
    int i=0;
    std_msgs::String status;
    status.data= "Sunny";
    ros::Rate loop_rate(10);
    int num = 10;
    while (ros::ok())
    {
      i=30;
      status.data="what";
      //      if (i>10000)
//      {
//        i=0;
//      }
      //i++;
//      if (i%num==0){
//        if(status.data.compare("Sunny")==0){
//          num=30;
//          status.data="Raining";
//        }else{
//          num=40;
//          status.data="Ha";
//        }
//      }
      RobotNode_stage_pub.publish(status);
      ros::spinOnce();
      loop_rate.sleep();
    }
}
