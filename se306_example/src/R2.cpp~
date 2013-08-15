#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//velocity of the robot
double linear_x;
double angular_z;

//pose of the robot
double px;
double py;
double theta;

//distance of the robot to the nearest wall, max distance set at 30
double minDistance = 30.000000;

// angle of detection
double w;
double z;

void StageOdom_callback(nav_msgs::Odometry msg)
{
  //This is the call back function to process odometry messages coming from Stage.
//  px = 5 + msg.pose.pose.position.x;
//  py = 10 + msg.pose.pose.position.y;
//  ROS_INFO("Current y position is: %f", py);
}

void StageLaser_callback(sensor_msgs::LaserScan msg)
{
  minDistance = msg.ranges[0];
//This is the callback function to process laser scan messages
//you can access the range data from msg.ranges[i]. i = sample number
// int numberOfValuesInRange = (msg.angle_max - msg.angle_min) / msg.angle_increment;
//  ROS_INFO("Number of values in range id : %d", numberOfValuesInRange);
//minDistance = msg.ranges[0];
//for (int i = 0; i < numberOfValuesInRange; i++)// {
//  minDistance = msg.ranges[i];
//     display full circular ranges and their distances to the nearest wall
//    if (msg.ranges[i] <= 8.0)
//    {
//     ROS_INFO("ranges[%d] = %f", i, msg.ranges[i]);
//     }
//      if (msg.ranges[i] < minDistance)
//    {
//     distance to the nearest wall
//    minDistance = msg.ranges[i];
//    }
// }
}

void WallDetection(nav_msgs::Odometry msg)
{
// Get the orientation of the farmer from Stage
  w = msg.pose.pose.orientation.w;
  z = msg.pose.pose.orientation.z;
//  ROS_INFO("w = %f", w);
//  ROS_INFO("z = %f", z);
}

//void Copy_callback(geometry_msgs::Twist msg)
//{
//  linear_x = msg.linear.x;
//  angular_z = msg.angular.z;
//}

int main(int argc, char **argv)
{

  //initialize robot parameters
  //Initial pose. This is same as the pose that you used in the world file to set	the robot pose.
  //theta = M_PI / 2.0;
  theta = 0.0;
  px = 10;
  py = 20;

  //Initial velocity
  linear_x = -2.0;
  angular_z = 0.0;

//You must call ros::init() first of all. ros::init() function needs to see argc and argv. The third argument is the name of the node
  ros::init(argc, argv, "RobotNode2");

//NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

//advertise() function will tell ROS that you want to publish on a given topic_
//to stage
  ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000);

//subscribe to listen to messages coming from stage
  ros::Subscriber StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, StageOdom_callback);
  ros::Subscriber StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_2/base_scan", 1000, StageLaser_callback);
  ros::Subscriber WallDetection_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, WallDetection);

  ros::Rate loop_rate(10);

//a count of howmany messages we have sent
  int count = 0;

////messages
//velocity of this RobotNode
  geometry_msgs::Twist RobotNode_cmdvel;

  while (ros::ok())
  {
    //ROS_INFO("I'm at ros::ok()");
    ROS_INFO("minDistance = %f", minDistance);

    if (minDistance <= 15.0)
    {
      RobotNode_cmdvel.linear.x = 3;
      RobotNode_cmdvel.angular.z = 20;
    } else {
      RobotNode_cmdvel.linear.x = linear_x;
      RobotNode_cmdvel.angular.z = angular_z;
    }
//
//      ROS_INFO("I'm inside the if (minDistance<=7.0)");
//      ROS_INFO("w = %f", w);
//      // when LEFT wall is detected,
//      // stop and turn away
//      //messages to stage
//
//        ROS_INFO("Left Wall!");
//        ROS_INFO("w = %f", w);
//        ROS_INFO("z = %f", z);
//        RobotNode_cmdvel.linear.x = 0.0;
//        RobotNode_cmdvel.angular.z = 0.2;
//        //publish the message
//        RobotNode_stage_pub.publish(RobotNode_cmdvel);
//
//
//    }
//    else
//    {
//      RobotNode_cmdvel.linear.x = -1.0;
//      RobotNode_cmdvel.angular.z = 0.0;
//    }
//if ()
//      //publish the message
//      RobotNode_stage_pub.publish(RobotNode_cmdvel);
//
//      // walk backwards and turn
//      while (minDistance <= 1.5)
//      {
//        ROS_INFO("I'm inside the while (minDistance <= 1.5)");
//        ROS_INFO("Linear = %f", RobotNode_cmdvel.linear.x);
//        ROS_INFO("Angular = %f", RobotNode_cmdvel.angular.z);
//        // walk backwards
//        while (minDistance <= 1.0)
//        {
//          ROS_INFO("I'm inside the while (minDistance <= 1.0)");
//          ROS_INFO("Linear = %f", RobotNode_cmdvel.linear.x);
//          ROS_INFO("Angular = %f", RobotNode_cmdvel.angular.z);
//          RobotNode_cmdvel.linear.x = -linear_x;
//          //publish the message
//          RobotNode_stage_pub.publish(RobotNode_cmdvel);
//        }
//        RobotNode_cmdvel.linear.x = -linear_x;
//        RobotNode_cmdvel.angular.z = -angular_z;
//
//        //publish the message
//        RobotNode_stage_pub.publish(RobotNode_cmdvel);
//
//      }
//    //}
//    // else
//    //  {
//      // no wall detected, continue to move
////      //messages to stage
//      ROS_INFO("I'm outside the loop");
//      ROS_INFO("Linear = %f", RobotNode_cmdvel.linear.x);
//      ROS_INFO("Angular = %f", RobotNode_cmdvel.angular.z);
//    //RobotNode_cmdvel.linear.x = 0.5;
//    // RobotNode_cmdvel.angular.z = 0.0;
//    // }
//    //}
    //publish the message
    RobotNode_stage_pub.publish(RobotNode_cmdvel);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;

}

