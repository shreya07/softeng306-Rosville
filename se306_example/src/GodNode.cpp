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

    
<<<<<<< HEAD
    //Publishers for GateTwo
ros::Publisher GateTwo_StageOdom_pub;//To Sheep
ros::Publisher GateTwo_StageLaser_pub; //To Sheep
ros::Publisher GateTwo_cmd_vel_pub; //To stage

    
    //Publishers for GateThree
ros::Publisher GateThree_StageOdom_pub;//To Sheep
ros::Publisher GateThree_StageLaser_pub; //To Sheep
ros::Publisher GateThree_cmd_vel_pub; //To stage
=======
    //Publishers for GhostSheepOne
ros::Publisher GhostSheepOne_StageOdom_pub;//To Sheep
ros::Publisher GhostSheepOne_StageLaser_pub; //To Sheep
ros::Publisher GhostSheepOne_cmd_vel_pub; //To stage

    
    //Publishers for SheepTwo
ros::Publisher SheepTwo_StageOdom_pub;//To Sheep
ros::Publisher SheepTwo_StageLaser_pub; //To Sheep
ros::Publisher SheepTwo_cmd_vel_pub; //To stage

    
    //Publishers for GrassOne
ros::Publisher GrassOne_StageOdom_pub;//To Sheep
ros::Publisher GrassOne_StageLaser_pub; //To Sheep
ros::Publisher GrassOne_cmd_vel_pub; //To stage
>>>>>>> e0a748ba689def699a0cd80594002048310cb824

    
    //Publishers for FarmerOne
ros::Publisher FarmerOne_StageOdom_pub;//To Sheep
ros::Publisher FarmerOne_StageLaser_pub; //To Sheep
ros::Publisher FarmerOne_cmd_vel_pub; //To stage

    
//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for GateOne
void GateOne_StageOdom_callback(nav_msgs::Odometry msg){ GateOne_StageOdom_pub.publish(msg);}
void GateOne_StageLaser_callback(sensor_msgs::LaserScan msg){GateOne_StageLaser_pub.publish(msg);}
void GateOne_cmd_vel_callback (geometry_msgs::Twist msg){GateOne_cmd_vel_pub.publish(msg);}

    
<<<<<<< HEAD
//Callbacks for GateTwo
void GateTwo_StageOdom_callback(nav_msgs::Odometry msg){ GateTwo_StageOdom_pub.publish(msg);}
void GateTwo_StageLaser_callback(sensor_msgs::LaserScan msg){GateTwo_StageLaser_pub.publish(msg);}
void GateTwo_cmd_vel_callback (geometry_msgs::Twist msg){GateTwo_cmd_vel_pub.publish(msg);}

    
//Callbacks for GateThree
void GateThree_StageOdom_callback(nav_msgs::Odometry msg){ GateThree_StageOdom_pub.publish(msg);}
void GateThree_StageLaser_callback(sensor_msgs::LaserScan msg){GateThree_StageLaser_pub.publish(msg);}
void GateThree_cmd_vel_callback (geometry_msgs::Twist msg){GateThree_cmd_vel_pub.publish(msg);}
=======
//Callbacks for GhostSheepOne
void GhostSheepOne_StageOdom_callback(nav_msgs::Odometry msg){ GhostSheepOne_StageOdom_pub.publish(msg);}
void GhostSheepOne_StageLaser_callback(sensor_msgs::LaserScan msg){GhostSheepOne_StageLaser_pub.publish(msg);}
void GhostSheepOne_cmd_vel_callback (geometry_msgs::Twist msg){GhostSheepOne_cmd_vel_pub.publish(msg);}

    
//Callbacks for SheepTwo
void SheepTwo_StageOdom_callback(nav_msgs::Odometry msg){ SheepTwo_StageOdom_pub.publish(msg);}
void SheepTwo_StageLaser_callback(sensor_msgs::LaserScan msg){SheepTwo_StageLaser_pub.publish(msg);}
void SheepTwo_cmd_vel_callback (geometry_msgs::Twist msg){SheepTwo_cmd_vel_pub.publish(msg);}

    
//Callbacks for GrassOne
void GrassOne_StageOdom_callback(nav_msgs::Odometry msg){ GrassOne_StageOdom_pub.publish(msg);}
void GrassOne_StageLaser_callback(sensor_msgs::LaserScan msg){GrassOne_StageLaser_pub.publish(msg);}
void GrassOne_cmd_vel_callback (geometry_msgs::Twist msg){GrassOne_cmd_vel_pub.publish(msg);}
>>>>>>> e0a748ba689def699a0cd80594002048310cb824

    
//Callbacks for FarmerOne
void FarmerOne_StageOdom_callback(nav_msgs::Odometry msg){ FarmerOne_StageOdom_pub.publish(msg);}
void FarmerOne_StageLaser_callback(sensor_msgs::LaserScan msg){FarmerOne_StageLaser_pub.publish(msg);}
void FarmerOne_cmd_vel_callback (geometry_msgs::Twist msg){FarmerOne_cmd_vel_pub.publish(msg);}

    
//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep

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
    
<<<<<<< HEAD
    
    //Advertisments for GateThree
    GateThree_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GateThree/odom", 1000); //To GateThree
    GateThree_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GateThree/base_scan", 1000); //To GateThree
    GateThree_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_3/cmd_vel", 1000); //To stage
=======
    //Advertisments for GhostSheepOne
    GhostSheepOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GhostSheepOne/odom", 1000); //To GhostSheepOne
    GhostSheepOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GhostSheepOne/base_scan", 1000); //To GhostSheepOne
    GhostSheepOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage
    
    
    //Advertisments for SheepTwo
    SheepTwo_StageOdom_pub = n.advertise<nav_msgs::Odometry>("SheepTwo/odom", 1000); //To SheepTwo
    SheepTwo_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("SheepTwo/base_scan", 1000); //To SheepTwo
    SheepTwo_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_3/cmd_vel", 1000); //To stage
    
    
    //Advertisments for GrassOne
    GrassOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GrassOne/odom", 1000); //To GrassOne
    GrassOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GrassOne/base_scan", 1000); //To GrassOne
    GrassOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage
>>>>>>> e0a748ba689def699a0cd80594002048310cb824
    
    
    //Advertisments for FarmerOne
    FarmerOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("FarmerOne/odom", 1000); //To FarmerOne
    FarmerOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("FarmerOne/base_scan", 1000); //To FarmerOne
    FarmerOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_3/cmd_vel", 1000); //To stage
    
    


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
  }

  return 0;

}
