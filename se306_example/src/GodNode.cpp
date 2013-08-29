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


//Publishers for PoopOne
ros::Publisher PoopOne_StageOdom_pub;//To Sheep
ros::Publisher PoopOne_StageLaser_pub; //To Sheep
ros::Publisher PoopOne_cmd_vel_pub; //To stage


//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for SheepOne
void SheepOne_StageOdom_callback(nav_msgs::Odometry msg){ SheepOne_StageOdom_pub.publish(msg);}
void SheepOne_StageLaser_callback(sensor_msgs::LaserScan msg){SheepOne_StageLaser_pub.publish(msg);}
void SheepOne_cmd_vel_callback (geometry_msgs::Twist msg){SheepOne_cmd_vel_pub.publish(msg);}


//Callbacks for PoopOne
void PoopOne_StageOdom_callback(nav_msgs::Odometry msg){ PoopOne_StageOdom_pub.publish(msg);}
void PoopOne_StageLaser_callback(sensor_msgs::LaserScan msg){PoopOne_StageLaser_pub.publish(msg);}
void PoopOne_cmd_vel_callback (geometry_msgs::Twist msg){PoopOne_cmd_vel_pub.publish(msg);}


//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep
ros::Publisher poopAdvert; //to poop

int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....

  //Advertisments for SheepOne
  SheepOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("SheepOne/odom", 1000); //To SheepOne
  SheepOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("SheepOne/base_scan", 1000); //To SheepOne
  SheepOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage


  //Advertisments for PoopOne
  PoopOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("PoopOne/odom", 1000); //To PoopOne
  PoopOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("PoopOne/base_scan", 1000); //To PoopOne
  PoopOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage


  ros::Publisher Weather_publisherOne;
  ros::Publisher Weather_publisherTwo;
  ros::Publisher Weather_publisherThree;
  ros::Publisher Weather_publisherFour;

  //Setting up subscribers...

  //Subscriber for SheepOne
  ros::Subscriber SheepOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, SheepOne_StageOdom_callback);
  ros::Subscriber SheepOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, SheepOne_StageLaser_callback);
  ros::Subscriber SheepOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("SheepOne/cmd_vel", 1000,SheepOne_cmd_vel_callback);


  //Subscriber for PoopOne
  ros::Subscriber PoopOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, PoopOne_StageOdom_callback);
  ros::Subscriber PoopOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_2/base_scan", 1000, PoopOne_StageLaser_callback);
  ros::Subscriber PoopOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("PoopOne/cmd_vel", 1000,PoopOne_cmd_vel_callback);




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

  // initialize
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
