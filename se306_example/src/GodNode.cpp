#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//-----Publisher variables

    //Publishers for GateOne
ros::Publisher GateOne_StageOdom_pub;//To Sheep
ros::Publisher GateOne_StageLaser_pub; //To Sheep
ros::Publisher GateOne_cmd_vel_pub; //To stage

    
    //Publishers for GateTwo
ros::Publisher GateTwo_StageOdom_pub;//To Sheep
ros::Publisher GateTwo_StageLaser_pub; //To Sheep
ros::Publisher GateTwo_cmd_vel_pub; //To stage

    
    //Publishers for GateThree
ros::Publisher GateThree_StageOdom_pub;//To Sheep
ros::Publisher GateThree_StageLaser_pub; //To Sheep
ros::Publisher GateThree_cmd_vel_pub; //To stage

    
//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for GateOne
void GateOne_StageOdom_callback(nav_msgs::Odometry msg){ GateOne_StageOdom_pub.publish(msg);}
void GateOne_StageLaser_callback(sensor_msgs::LaserScan msg){GateOne_StageLaser_pub.publish(msg);}
void GateOne_cmd_vel_callback (geometry_msgs::Twist msg){GateOne_cmd_vel_pub.publish(msg);}

    
//Callbacks for GateTwo
void GateTwo_StageOdom_callback(nav_msgs::Odometry msg){ GateTwo_StageOdom_pub.publish(msg);}
void GateTwo_StageLaser_callback(sensor_msgs::LaserScan msg){GateTwo_StageLaser_pub.publish(msg);}
void GateTwo_cmd_vel_callback (geometry_msgs::Twist msg){GateTwo_cmd_vel_pub.publish(msg);}

    
//Callbacks for GateThree
void GateThree_StageOdom_callback(nav_msgs::Odometry msg){ GateThree_StageOdom_pub.publish(msg);}
void GateThree_StageLaser_callback(sensor_msgs::LaserScan msg){GateThree_StageLaser_pub.publish(msg);}
void GateThree_cmd_vel_callback (geometry_msgs::Twist msg){GateThree_cmd_vel_pub.publish(msg);}

    
//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep
ros::Publisher poopAdvert; //to poop

int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....
  
    //Advertisments for GateOne
    GateOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GateOne/odom", 1000); //To GateOne
    GateOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GateOne/base_scan", 1000); //To GateOne
    GateOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage
    
    
    //Advertisments for GateTwo
    GateTwo_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GateTwo/odom", 1000); //To GateTwo
    GateTwo_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GateTwo/base_scan", 1000); //To GateTwo
    GateTwo_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage
    
    
    //Advertisments for GateThree
    GateThree_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GateThree/odom", 1000); //To GateThree
    GateThree_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GateThree/base_scan", 1000); //To GateThree
    GateThree_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_3/cmd_vel", 1000); //To stage
    
    
  ros::Publisher Weather_publisherOne;
  ros::Publisher Weather_publisherTwo;
  ros::Publisher Weather_publisherThree;
  ros::Publisher Weather_publisherFour;

  //Setting up subscribers...
  
    //Subscriber for GateOne
    ros::Subscriber GateOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, GateOne_StageOdom_callback);
    ros::Subscriber GateOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, GateOne_StageLaser_callback);
    ros::Subscriber GateOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("GateOne/cmd_vel", 1000,GateOne_cmd_vel_callback);
    
    
    //Subscriber for GateTwo
    ros::Subscriber GateTwo_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, GateTwo_StageOdom_callback);
    ros::Subscriber GateTwo_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_2/base_scan", 1000, GateTwo_StageLaser_callback);
    ros::Subscriber GateTwo_cmd_vel = n.subscribe<geometry_msgs::Twist>("GateTwo/cmd_vel", 1000,GateTwo_cmd_vel_callback);
    
    
    //Subscriber for GateThree
    ros::Subscriber GateThree_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_3/odom", 1000, GateThree_StageOdom_callback);
    ros::Subscriber GateThree_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_3/base_scan", 1000, GateThree_StageLaser_callback);
    ros::Subscriber GateThree_cmd_vel = n.subscribe<geometry_msgs::Twist>("GateThree/cmd_vel", 1000,GateThree_cmd_vel_callback);
    
    


  // set up publishers
  Weather_publisherOne = n.advertise<std_msgs::String>("weather/statusOne", 1000); //To fieldOne
  Weather_publisherTwo = n.advertise<std_msgs::String>("weather/statusTwo", 1000); //To fieldTwo
  Weather_publisherThree = n.advertise<std_msgs::String>("weather/statusThree", 1000); //To fieldThree
  Weather_publisherFour = n.advertise<std_msgs::String>("weather/statusFour", 1000); //To fieldFour
  poopAdvert = n.advertise<std_msgs::String>("poop", 1000);

  // set count
  int count = 0;
  int poopCount = 0;

  // set loop rate
  ros::Rate loop_rate(10);

  //a count of how many messages we have sent
  double randomNum;

  //messages
  std_msgs::String statusOne;
  std_msgs::String statusTwo;
  std_msgs::String statusThree;
  std_msgs::String statusFour;
  std_msgs::String poopInfo;

  srand(time(NULL));

  // initialize
  statusOne.data="Sunny";
  statusTwo.data="Sunny";
  statusThree.data="Sunny";
  statusFour.data="Sunny";

  while (ros::ok())
  {
    randomNum = ((rand()%10));
    ROS_INFO("random num %f", randomNum);

    if (randomNum < 4) {
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

    if (count % 100) {
      if (poopCount < 5) {
        poopInfo.data = "Request";
        poopAdvert.publish(poopInfo);
      }
    }


    ros::spinOnce();

    loop_rate.sleep();

  }

  return 0;
}
