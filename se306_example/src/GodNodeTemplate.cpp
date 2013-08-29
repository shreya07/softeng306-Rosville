#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

//-----Publisher variables
//PublisherDeclaration
//-----[END]Publisher variables

//-----Subscriber callbacks
//subscriberCallBacksMethods
//-----[END] Subscriber callbacks

ros::Publisher Weather_publisher;//To Sheep
ros::Publisher poopAdvert; //to poop

int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....
  //RegisterPublisher
  ros::Publisher Weather_publisherOne;
  ros::Publisher Weather_publisherTwo;
  ros::Publisher Weather_publisherThree;
  ros::Publisher Weather_publisherFour;

  //Setting up subscribers...
  //SetupSubscribers


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
  ros::Rate loop_rate(1);

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
