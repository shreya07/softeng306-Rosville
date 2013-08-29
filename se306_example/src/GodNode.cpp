#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//-----Publisher variables

    //Publishers for newSheepOne
ros::Publisher newSheepOne_StageOdom_pub;//To Sheep
ros::Publisher newSheepOne_StageLaser_pub; //To Sheep
ros::Publisher newSheepOne_cmd_vel_pub; //To stage

    
    //Publishers for GrassOne
ros::Publisher GrassOne_StageOdom_pub;//To Sheep
ros::Publisher GrassOne_StageLaser_pub; //To Sheep
ros::Publisher GrassOne_cmd_vel_pub; //To stage

    
    //Publishers for BlockOne
ros::Publisher BlockOne_StageOdom_pub;//To Sheep
ros::Publisher BlockOne_StageLaser_pub; //To Sheep
ros::Publisher BlockOne_cmd_vel_pub; //To stage

    
    //Publishers for newSheepTwo
ros::Publisher newSheepTwo_StageOdom_pub;//To Sheep
ros::Publisher newSheepTwo_StageLaser_pub; //To Sheep
ros::Publisher newSheepTwo_cmd_vel_pub; //To stage

    
//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for newSheepOne
void newSheepOne_StageOdom_callback(nav_msgs::Odometry msg){ newSheepOne_StageOdom_pub.publish(msg);}
void newSheepOne_StageLaser_callback(sensor_msgs::LaserScan msg){newSheepOne_StageLaser_pub.publish(msg);}
void newSheepOne_cmd_vel_callback (geometry_msgs::Twist msg){newSheepOne_cmd_vel_pub.publish(msg);}

    
//Callbacks for GrassOne
void GrassOne_StageOdom_callback(nav_msgs::Odometry msg){ GrassOne_StageOdom_pub.publish(msg);}
void GrassOne_StageLaser_callback(sensor_msgs::LaserScan msg){GrassOne_StageLaser_pub.publish(msg);}
void GrassOne_cmd_vel_callback (geometry_msgs::Twist msg){GrassOne_cmd_vel_pub.publish(msg);}

    
//Callbacks for BlockOne
void BlockOne_StageOdom_callback(nav_msgs::Odometry msg){ BlockOne_StageOdom_pub.publish(msg);}
void BlockOne_StageLaser_callback(sensor_msgs::LaserScan msg){BlockOne_StageLaser_pub.publish(msg);}
void BlockOne_cmd_vel_callback (geometry_msgs::Twist msg){BlockOne_cmd_vel_pub.publish(msg);}

    
//Callbacks for newSheepTwo
void newSheepTwo_StageOdom_callback(nav_msgs::Odometry msg){ newSheepTwo_StageOdom_pub.publish(msg);}
void newSheepTwo_StageLaser_callback(sensor_msgs::LaserScan msg){newSheepTwo_StageLaser_pub.publish(msg);}
void newSheepTwo_cmd_vel_callback (geometry_msgs::Twist msg){newSheepTwo_cmd_vel_pub.publish(msg);}

    
//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep

int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....
  
    //Advertisments for newSheepOne
    newSheepOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("newSheepOne/odom", 1000); //To newSheepOne
    newSheepOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("newSheepOne/base_scan", 1000); //To newSheepOne
    newSheepOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage
    
    
    //Advertisments for GrassOne
    GrassOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GrassOne/odom", 1000); //To GrassOne
    GrassOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GrassOne/base_scan", 1000); //To GrassOne
    GrassOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage
    
    
    //Advertisments for BlockOne
    BlockOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("BlockOne/odom", 1000); //To BlockOne
    BlockOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("BlockOne/base_scan", 1000); //To BlockOne
    BlockOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_3/cmd_vel", 1000); //To stage
    
    
    //Advertisments for newSheepTwo
    newSheepTwo_StageOdom_pub = n.advertise<nav_msgs::Odometry>("newSheepTwo/odom", 1000); //To newSheepTwo
    newSheepTwo_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("newSheepTwo/base_scan", 1000); //To newSheepTwo
    newSheepTwo_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_4/cmd_vel", 1000); //To stage
    
    


  //Setting up subscribers...
  
    //Subscriber for newSheepOne
    ros::Subscriber newSheepOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, newSheepOne_StageOdom_callback);
    ros::Subscriber newSheepOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, newSheepOne_StageLaser_callback);
    ros::Subscriber newSheepOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("newSheepOne/cmd_vel", 1000,newSheepOne_cmd_vel_callback);
    
    
    //Subscriber for GrassOne
    ros::Subscriber GrassOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, GrassOne_StageOdom_callback);
    ros::Subscriber GrassOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_2/base_scan", 1000, GrassOne_StageLaser_callback);
    ros::Subscriber GrassOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("GrassOne/cmd_vel", 1000,GrassOne_cmd_vel_callback);
    
    
    //Subscriber for BlockOne
    ros::Subscriber BlockOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_3/odom", 1000, BlockOne_StageOdom_callback);
    ros::Subscriber BlockOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_3/base_scan", 1000, BlockOne_StageLaser_callback);
    ros::Subscriber BlockOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("BlockOne/cmd_vel", 1000,BlockOne_cmd_vel_callback);
    
    
    //Subscriber for newSheepTwo
    ros::Subscriber newSheepTwo_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_4/odom", 1000, newSheepTwo_StageOdom_callback);
    ros::Subscriber newSheepTwo_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_4/base_scan", 1000, newSheepTwo_StageLaser_callback);
    ros::Subscriber newSheepTwo_cmd_vel = n.subscribe<geometry_msgs::Twist>("newSheepTwo/cmd_vel", 1000,newSheepTwo_cmd_vel_callback);
    
    

  Weather_publisher = n.advertise<std_msgs::String>("weather/status", 1000); //To SheepOne

  ros::Rate loop_rate(10);

  //a count of howmany messages we have sent
  int count = 0;

  ////messages
  //velocity of this RobotNode
  std_msgs::String status;
  status.data="Sunny";
  while (ros::ok())
  {
    if (count%5 == 0) {
      if (status.data.compare("Sunny") == 0) {
        status.data = "Raining";
        ROS_INFO("rainy");
      } else {
        status.data = "Sunny";
        ROS_INFO("sunny");
      }
    }

    ros::spinOnce();

    loop_rate.sleep();
    count=count+1;
  }

  return 0;

}
