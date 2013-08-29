
#include "Sheep1.h"
#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include "Custom.h"

#include <sstream>
#include "math.h"
#include "Robot.h"
#include <vector>

#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"

int main (int argc, char **argv){
  Sheep1 robot = Sheep1("Sheep",argc,argv,20,20,"Two");
  robot.run();
  return 0;
}
