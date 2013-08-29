#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//-----Publisher variables

//Publishers for GrassOne
    //Publishers for SheepOne
ros::Publisher SheepOne_StageOdom_pub;//To Sheep
ros::Publisher SheepOne_StageLaser_pub; //To Sheep
ros::Publisher SheepOne_cmd_vel_pub; //To stage

    
    //Publishers for BlockOne
ros::Publisher BlockOne_StageOdom_pub;//To Sheep
ros::Publisher BlockOne_StageLaser_pub; //To Sheep
ros::Publisher BlockOne_cmd_vel_pub; //To stage

    
    //Publishers for PoopOne
ros::Publisher PoopOne_StageOdom_pub;//To Sheep
ros::Publisher PoopOne_StageLaser_pub; //To Sheep
ros::Publisher PoopOne_cmd_vel_pub; //To stage

    
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


//-----[END]Publisher variables

//-----Subscriber callbacks

//Callbacks for SheepOne
void SheepOne_StageOdom_callback(nav_msgs::Odometry msg){ SheepOne_StageOdom_pub.publish(msg);}
void SheepOne_StageLaser_callback(sensor_msgs::LaserScan msg){SheepOne_StageLaser_pub.publish(msg);}
void SheepOne_cmd_vel_callback (geometry_msgs::Twist msg){SheepOne_cmd_vel_pub.publish(msg);}

    
//Callbacks for BlockOne
void BlockOne_StageOdom_callback(nav_msgs::Odometry msg){ BlockOne_StageOdom_pub.publish(msg);}
void BlockOne_StageLaser_callback(sensor_msgs::LaserScan msg){BlockOne_StageLaser_pub.publish(msg);}
void BlockOne_cmd_vel_callback (geometry_msgs::Twist msg){BlockOne_cmd_vel_pub.publish(msg);}

    
//Callbacks for PoopOne
void PoopOne_StageOdom_callback(nav_msgs::Odometry msg){ PoopOne_StageOdom_pub.publish(msg);}
void PoopOne_StageLaser_callback(sensor_msgs::LaserScan msg){PoopOne_StageLaser_pub.publish(msg);}
void PoopOne_cmd_vel_callback (geometry_msgs::Twist msg){PoopOne_cmd_vel_pub.publish(msg);}

    
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


//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep
ros::Publisher poopAdvert; //to poop

int main(int argc, char **argv)
{

	ros::init(argc, argv, "GodNode");

	//NodeHandle is the main access point to communicate with ros.
	ros::NodeHandle n;

<<<<<<< HEAD
  // Advertisements.....
=======
	// Advertisements.....
	
    //Advertisments for SheepOne
    SheepOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("SheepOne/odom", 1000); //To SheepOne
    SheepOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("SheepOne/base_scan", 1000); //To SheepOne
    SheepOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage
    
    
    //Advertisments for BlockOne
    BlockOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("BlockOne/odom", 1000); //To BlockOne
    BlockOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("BlockOne/base_scan", 1000); //To BlockOne
    BlockOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_2/cmd_vel", 1000); //To stage
    
    
    //Advertisments for PoopOne
    PoopOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("PoopOne/odom", 1000); //To PoopOne
    PoopOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("PoopOne/base_scan", 1000); //To PoopOne
    PoopOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_3/cmd_vel", 1000); //To stage
    
    
    //Advertisments for GhostSheepOne
    GhostSheepOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GhostSheepOne/odom", 1000); //To GhostSheepOne
    GhostSheepOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GhostSheepOne/base_scan", 1000); //To GhostSheepOne
    GhostSheepOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_4/cmd_vel", 1000); //To stage
    
    
    //Advertisments for SheepTwo
    SheepTwo_StageOdom_pub = n.advertise<nav_msgs::Odometry>("SheepTwo/odom", 1000); //To SheepTwo
    SheepTwo_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("SheepTwo/base_scan", 1000); //To SheepTwo
    SheepTwo_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_5/cmd_vel", 1000); //To stage
    
    
    //Advertisments for GrassOne
    GrassOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GrassOne/odom", 1000); //To GrassOne
    GrassOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GrassOne/base_scan", 1000); //To GrassOne
    GrassOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_6/cmd_vel", 1000); //To stage
    
    
>>>>>>> def9acf77519ee64d6e22d46abc97b4fd0a9fabd

  //Advertisments for GrassOne
  GrassOne_StageOdom_pub = n.advertise<nav_msgs::Odometry>("GrassOne/odom", 1000); //To GrassOne
  GrassOne_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("GrassOne/base_scan", 1000); //To GrassOne
  GrassOne_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("robot_1/cmd_vel", 1000); //To stage


  ros::Publisher Weather_publisherOne;
  ros::Publisher Weather_publisherTwo;
  ros::Publisher Weather_publisherThree;
  ros::Publisher Weather_publisherFour;

<<<<<<< HEAD
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
=======
	//Setting up subscribers...
	
    //Subscriber for SheepOne
    ros::Subscriber SheepOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_1/odom", 1000, SheepOne_StageOdom_callback);
    ros::Subscriber SheepOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_1/base_scan", 1000, SheepOne_StageLaser_callback);
    ros::Subscriber SheepOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("SheepOne/cmd_vel", 1000,SheepOne_cmd_vel_callback);
    
    
    //Subscriber for BlockOne
    ros::Subscriber BlockOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_2/odom", 1000, BlockOne_StageOdom_callback);
    ros::Subscriber BlockOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_2/base_scan", 1000, BlockOne_StageLaser_callback);
    ros::Subscriber BlockOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("BlockOne/cmd_vel", 1000,BlockOne_cmd_vel_callback);
    
    
    //Subscriber for PoopOne
    ros::Subscriber PoopOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_3/odom", 1000, PoopOne_StageOdom_callback);
    ros::Subscriber PoopOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_3/base_scan", 1000, PoopOne_StageLaser_callback);
    ros::Subscriber PoopOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("PoopOne/cmd_vel", 1000,PoopOne_cmd_vel_callback);
    
    
    //Subscriber for GhostSheepOne
    ros::Subscriber GhostSheepOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_4/odom", 1000, GhostSheepOne_StageOdom_callback);
    ros::Subscriber GhostSheepOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_4/base_scan", 1000, GhostSheepOne_StageLaser_callback);
    ros::Subscriber GhostSheepOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("GhostSheepOne/cmd_vel", 1000,GhostSheepOne_cmd_vel_callback);
    
    
    //Subscriber for SheepTwo
    ros::Subscriber SheepTwo_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_5/odom", 1000, SheepTwo_StageOdom_callback);
    ros::Subscriber SheepTwo_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_5/base_scan", 1000, SheepTwo_StageLaser_callback);
    ros::Subscriber SheepTwo_cmd_vel = n.subscribe<geometry_msgs::Twist>("SheepTwo/cmd_vel", 1000,SheepTwo_cmd_vel_callback);
    
    
    //Subscriber for GrassOne
    ros::Subscriber GrassOne_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("robot_6/odom", 1000, GrassOne_StageOdom_callback);
    ros::Subscriber GrassOne_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("robot_6/base_scan", 1000, GrassOne_StageLaser_callback);
    ros::Subscriber GrassOne_cmd_vel = n.subscribe<geometry_msgs::Twist>("GrassOne/cmd_vel", 1000,GrassOne_cmd_vel_callback);
    
    

	Weather_publisher = n.advertise<std_msgs::String>("weather/status", 1000); //To SheepOne
	poopAdvert = n.advertise<std_msgs::String>("poop", 1000);
	ros::Rate loop_rate(10);

	//a count of howmany messages we have sent
	int count = 0;

	//send to poop class requesting poop to drop;
	std_msgs::String poopInfo;
	int poopCount = 0;

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

		if (count % 100) {
			if (poopCount < 5) {
				poopInfo.data = "Request";
				poopAdvert.publish(poopInfo);
			}
			poopCount++;
		}
		count++;
	}
>>>>>>> def9acf77519ee64d6e22d46abc97b4fd0a9fabd

}
