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


int main(int argc, char **argv)
{

  ros::init(argc, argv, "GodNode");

  //NodeHandle is the main access point to communicate with ros.
  ros::NodeHandle n;

  // Advertisements.....
  //RegisterPublisher


  //Setting up subscribers...
  //SetupSubscribers


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
