#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//-----Publisher variables

    //Publishers for SheepOne
ros::Publisher SheepOne_StageOdom_pub;//To Sheep
ros::Publisher SheepOne_StageLaser_pub; //To Sheep
ros::Publisher SheepOne_cmd_vel_pub; //To stage

    
    //Publishers for GhostSheepOne
ros::Publisher GhostSheepOne_StageOdom_pub;//To Sheep
ros::Publisher GhostSheepOne_StageLaser_pub; //To Sheep
ros::Publisher GhostSheepOne_cmd_vel_pub; //To stage

    //Publishers for GrassOne
ros::Publisher GrassOne_StageOdom_pub;//To Sheep
ros::Publisher GrassOne_StageLaser_pub; //To Sheep
ros::Publisher GrassOne_cmd_vel_pub; //To stage

    
//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for SheepOne
void SheepOne_StageOdom_callback(nav_msgs::Odometry msg){ SheepOne_StageOdom_pub.publish(msg);}
void SheepOne_StageLaser_callback(sensor_msgs::LaserScan msg){SheepOne_StageLaser_pub.publish(msg);}
void SheepOne_cmd_vel_callback (geometry_msgs::Twist msg){SheepOne_cmd_vel_pub.publish(msg);}

    
<<<<<<< HEAD
//Callbacks for GhostSheepOne
void GhostSheepOne_StageOdom_callback(nav_msgs::Odometry msg){ GhostSheepOne_StageOdom_pub.publish(msg);}
void GhostSheepOne_StageLaser_callback(sensor_msgs::LaserScan msg){GhostSheepOne_StageLaser_pub.publish(msg);}
void GhostSheepOne_cmd_vel_callback (geometry_msgs::Twist msg){GhostSheepOne_cmd_vel_pub.publish(msg);}

    
=======
>>>>>>> c49886d7eabcbcec34df8e65b8e80116cbf56564
//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep

int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....
  
<<<<<<< HEAD
    //Advertisments for SheepOne
    SheepOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("SheepOne/odom", 1000); //To SheepOne
    SheepOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("SheepOne/base_scan", 1000); //To SheepOne
    SheepOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage
    
    
    //Advertisments for GhostSheepOne
    GhostSheepOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GhostSheepOne/odom", 1000); //To GhostSheepOne
    GhostSheepOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GhostSheepOne/base_scan", 1000); //To GhostSheepOne
    GhostSheepOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage
=======
    //Advertisments for GrassOne
    GrassOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GrassOne/odom", 1000); //To GrassOne
    GrassOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GrassOne/base_scan", 1000); //To GrassOne
    GrassOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage
>>>>>>> c49886d7eabcbcec34df8e65b8e80116cbf56564
    
    


  //Setting up subscribers...
  
<<<<<<< HEAD
    //Subscriber for SheepOne
    ros::Subscriber SheepOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, SheepOne_StageOdom_callback);
    ros::Subscriber SheepOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, SheepOne_StageLaser_callback);
    ros::Subscriber SheepOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("SheepOne/cmd_vel", 1000,SheepOne_cmd_vel_callback);
    
    
    //Subscriber for GhostSheepOne
    ros::Subscriber GhostSheepOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, GhostSheepOne_StageOdom_callback);
    ros::Subscriber GhostSheepOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_2/base_scan", 1000, GhostSheepOne_StageLaser_callback);
    ros::Subscriber GhostSheepOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("GhostSheepOne/cmd_vel", 1000,GhostSheepOne_cmd_vel_callback);
=======
    //Subscriber for GrassOne
    ros::Subscriber GrassOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, GrassOne_StageOdom_callback);
    ros::Subscriber GrassOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, GrassOne_StageLaser_callback);
    ros::Subscriber GrassOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("GrassOne/cmd_vel", 1000,GrassOne_cmd_vel_callback);
>>>>>>> c49886d7eabcbcec34df8e65b8e80116cbf56564
    
    

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
<<<<<<< HEAD
    if (count%30==0)
        {
          status.data="Rainy";
          Weather_publisher.publish(status);

          //ROS_INFO("rainy");
        }else if (count%59){
          status.data="Sunny";
          //ROS_INFO("sunny");
          Weather_publisher.publish(status);

        }

        ros::spinOnce();

        loop_rate.sleep();
        count=count+1;
=======
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
>>>>>>> c49886d7eabcbcec34df8e65b8e80116cbf56564
  }

  return 0;

}
