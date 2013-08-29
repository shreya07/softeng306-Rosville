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

    
    //Publishers for grassOne
ros::Publisher grassOne_StageOdom_pub;//To Sheep
ros::Publisher grassOne_StageLaser_pub; //To Sheep
ros::Publisher grassOne_cmd_vel_pub; //To stage

    
//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for newSheepOne
void newSheepOne_StageOdom_callback(nav_msgs::Odometry msg){ newSheepOne_StageOdom_pub.publish(msg);}
void newSheepOne_StageLaser_callback(sensor_msgs::LaserScan msg){newSheepOne_StageLaser_pub.publish(msg);}
void newSheepOne_cmd_vel_callback (geometry_msgs::Twist msg){newSheepOne_cmd_vel_pub.publish(msg);}

    
//Callbacks for grassOne
void grassOne_StageOdom_callback(nav_msgs::Odometry msg){ grassOne_StageOdom_pub.publish(msg);}
void grassOne_StageLaser_callback(sensor_msgs::LaserScan msg){grassOne_StageLaser_pub.publish(msg);}
void grassOne_cmd_vel_callback (geometry_msgs::Twist msg){grassOne_cmd_vel_pub.publish(msg);}

    
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
    
    
    //Advertisments for grassOne
    grassOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("grassOne/odom", 1000); //To grassOne
    grassOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("grassOne/base_scan", 1000); //To grassOne
    grassOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage
    
    


  //Setting up subscribers...
  
    //Subscriber for newSheepOne
    ros::Subscriber newSheepOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, newSheepOne_StageOdom_callback);
    ros::Subscriber newSheepOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, newSheepOne_StageLaser_callback);
    ros::Subscriber newSheepOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("newSheepOne/cmd_vel", 1000,newSheepOne_cmd_vel_callback);
    
    
    //Subscriber for grassOne
    ros::Subscriber grassOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, grassOne_StageOdom_callback);
    ros::Subscriber grassOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_2/base_scan", 1000, grassOne_StageLaser_callback);
    ros::Subscriber grassOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("grassOne/cmd_vel", 1000,grassOne_cmd_vel_callback);
    
    

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
