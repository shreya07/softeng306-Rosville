#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//-----Publisher variables

    //Publishers for Sheep_One
ros::Publisher Sheep_One_StageOdom_pub;//To Sheep
ros::Publisher Sheep_One_StageLaser_pub; //To Sheep
ros::Publisher Sheep_One_cmd_vel_pub; //To stage

    
    //Publishers for Sheep_Two
ros::Publisher Sheep_Two_StageOdom_pub;//To Sheep
ros::Publisher Sheep_Two_StageLaser_pub; //To Sheep
ros::Publisher Sheep_Two_cmd_vel_pub; //To stage

    
//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for Sheep_One
void Sheep_One_StageOdom_callback(nav_msgs::Odometry msg){ Sheep_One_StageOdom_pub.publish(msg);}
void Sheep_One_StageLaser_callback(sensor_msgs::LaserScan msg){Sheep_One_StageLaser_pub.publish(msg);}
void Sheep_One_cmd_vel_callback (geometry_msgs::Twist msg){Sheep_One_cmd_vel_pub.publish(msg);}

    
//Callbacks for Sheep_Two
void Sheep_Two_StageOdom_callback(nav_msgs::Odometry msg){ Sheep_Two_StageOdom_pub.publish(msg);}
void Sheep_Two_StageLaser_callback(sensor_msgs::LaserScan msg){Sheep_Two_StageLaser_pub.publish(msg);}
void Sheep_Two_cmd_vel_callback (geometry_msgs::Twist msg){Sheep_Two_cmd_vel_pub.publish(msg);}

    
//-----[END] Subscriber callbacks


int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....
  
    //Advertisments for Sheep_One
    Sheep_One_StageOdom_pub = n.advertise<nav_msgs::Odometry>("Sheep_One/odom", 1000); //To Sheep_One
    Sheep_One_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("Sheep_One/base_scan", 1000); //To Sheep_One
    Sheep_One_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage
    
    
    //Advertisments for Sheep_Two
    Sheep_Two_StageOdom_pub = n.advertise<nav_msgs::Odometry>("Sheep_Two/odom", 1000); //To Sheep_Two
    Sheep_Two_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("Sheep_Two/base_scan", 1000); //To Sheep_Two
    Sheep_Two_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage
    
    


  //Setting up subscribers...
  
    //Subscriber for Sheep_One
    ros::Subscriber Sheep_One_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, Sheep_One_StageOdom_callback);
    ros::Subscriber Sheep_One_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, Sheep_One_StageLaser_callback);
    ros::Subscriber Sheep_One_cmd_vel = n.subscribe<geometry_msgs::Twist>("Sheep_One/cmd_vel", 1000,Sheep_One_cmd_vel_callback);
    
    
    //Subscriber for Sheep_Two
    ros::Subscriber Sheep_Two_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, Sheep_Two_StageOdom_callback);
    ros::Subscriber Sheep_Two_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_2/base_scan", 1000, Sheep_Two_StageLaser_callback);
    ros::Subscriber Sheep_Two_cmd_vel = n.subscribe<geometry_msgs::Twist>("Sheep_Two/cmd_vel", 1000,Sheep_Two_cmd_vel_callback);
    
    


  ros::Rate loop_rate(10);

  //a count of howmany messages we have sent
  int count = 0;

  ////messages
  //velocity of this RobotNode

  while (ros::ok())
  {
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;

}
