#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//-----Publisher variables

//Publishers for GrassOne
ros::Publisher GrassOne_StageOdom_pub;//To Sheep
ros::Publisher GrassOne_StageLaser_pub; //To Sheep
ros::Publisher GrassOne_cmd_vel_pub; //To stage


//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for GrassOne
void GrassOne_StageOdom_callback(nav_msgs::Odometry msg){ GrassOne_StageOdom_pub.publish(msg);}
void GrassOne_StageLaser_callback(sensor_msgs::LaserScan msg){GrassOne_StageLaser_pub.publish(msg);}
void GrassOne_cmd_vel_callback (geometry_msgs::Twist msg){GrassOne_cmd_vel_pub.publish(msg);}


//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep

int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....

  //Advertisments for GrassOne
  GrassOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GrassOne/odom", 1000); //To GrassOne
  GrassOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GrassOne/base_scan", 1000); //To GrassOne
  GrassOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage


  ros::Publisher Weather_publisherOne;
  ros::Publisher Weather_publisherTwo;
  ros::Publisher Weather_publisherThree;
  ros::Publisher Weather_publisherFour;

  //Setting up subscribers...

  //Subscriber for GrassOne
  ros::Subscriber GrassOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, GrassOne_StageOdom_callback);
  ros::Subscriber GrassOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, GrassOne_StageLaser_callback);
  ros::Subscriber GrassOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("GrassOne/cmd_vel", 1000,GrassOne_cmd_vel_callback);


  // set up publishers
  Weather_publisherOne = n.advertise<std_msgs::String>("weather/statusOne", 1000); //To fieldOne
  Weather_publisherTwo = n.advertise<std_msgs::String>("weather/statusTwo", 1000); //To fieldTwo
  Weather_publisherThree = n.advertise<std_msgs::String>("weather/statusThree", 1000); //To fieldThree
  Weather_publisherFour = n.advertise<std_msgs::String>("weather/statusFour", 1000); //To fieldFour

  ros::Rate loop_rate(1);

  //a count of how many messages we have sent
  int randomNum;

  //messages
  std_msgs::String statusOne;
  std_msgs::String statusTwo;
  std_msgs::String statusThree;
  std_msgs::String statusFour;

  srand(time(NULL));

  // initialise
  statusOne.data="Sunny";
  statusTwo.data="Sunny";
  statusThree.data="Sunny";
  statusFour.data="Sunny";

  while (ros::ok())
  {
    randomNum = rand();

    if (randomNum < 0.4) {
      statusOne.data = "Raining";
      statusTwo.data = "Sunny";
      ROS_INFO("rainy");
    } else {
      statusOne.data = "Sunny";
      statusTwo.data = "Raining";
      ROS_INFO("sunny");
    }

    if (randomNum > 0.5) {
      statusThree.data = "Raining";
      statusFour.data = "Sunny";
    } else {
      statusThree.data = "Sunny";
      statusFour.data = "Raining";
    }
    Weather_publisherOne.publish(statusOne);
    Weather_publisherTwo.publish(statusTwo);
    Weather_publisherThree.publish(statusThree);
    Weather_publisherFour.publish(statusFour);


    ros::spinOnce();

    loop_rate.sleep();

  }

  return 0;

}
