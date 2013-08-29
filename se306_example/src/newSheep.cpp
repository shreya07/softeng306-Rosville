/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: Shreya
 */

#include "newSheep.h"
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
#include <tf/transform_broadcaster.h>
#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"
#include "../msg_gen/cpp/include/se306_example/FollowSheep.h"
#include "../msg_gen/cpp/include/se306_example/eatGrass.h"

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 *  */
newSheep::newSheep(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
  //can do extra stuff here if you like
  //this-> x = px;
  //this-> y = py;
  distance = 15;
  linear_x = 2.0;
  angular_z = 0.0;
  theta = 0.0;
  width = 1;
  length = 2;
  followGhost = false;
  PX_INIT = px;
  PY_INIT = py;
  old_ang_z = 2.0;
  once = false;
  health = 1.0;
  replyReceived = false;
  requestSent = false;
  grassDetected = false;
  grassReached = false;
  eaten = false;
  grassName = "";


}
/*destrustor
 * I have not implemented it here but you should*/
newSheep::~newSheep()
{
  // TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void newSheep::stageOdom_callback(nav_msgs::Odometry msg){
  //int x = msg.linear.x;
  px = PX_INIT + msg.pose.pose.position.x;
  py = PY_INIT + msg.pose.pose.position.y;
  double theCorrectTheta = yawFromQuaternion(msg.pose.pose.orientation.x,msg.pose.pose.orientation.y,msg.pose.pose.orientation.z,msg.pose.pose.orientation.w);
  theta = theCorrectTheta;
}


void newSheep::StageLaser_callback(sensor_msgs::LaserScan msg)
{
      distance = msg.ranges[20];
  se306_example::IdentityRequest request;
  if(distance <= 5) {

    RobotNode_cmdvel.linear.x = linear_x;
    RobotNode_cmdvel.angular.z = angular_z;
    //RobotNode_stage_pub.publish(RobotNode_cmdvel);

    request.sender = robot_name+robot_number;

    std::list<double> pose = calculateTheta(theta, distance);
    double x = pose.front();
    double y = pose.back();

    request.px = this->px+x+(width/2.0);
    //pose.pop_front();
    request.py = py+y+(length/2.0);
    //pose.pop_front();

    Request_pub.publish(request);
    replyReceived = false;
    requestSent = true;
  }


}

void newSheep::identityReply_callBack(se306_example::IdentityReply reply)
{
      ROS_INFO("reply received");
      replyReceived = true;
  ROS_INFO("%s is being returned", reply.type.c_str());
  if(reply.destination.compare(robot_name+robot_number)==0) {


    if(reply.type.compare("Grass")==0) {
      //ROS_INFO("Grass detected");
    	if(reply.height > 5) {
    		grassDetected = true;
    		grassName = reply.sender;

    	}

    }else if(reply.type.compare("sheep")==0){

    }else if(reply.type.compare("PoisonGrass")==0){
      health -=0.5;
    }
    else  {
      ROS_INFO("Don't know what it is");
    }
  }
}

void newSheep::grassThings() {
	se306_example::eatGrass msg;
	linear_x = 2.0;
	angular_z = 0.0;
	if(distance <= 0){
		grassReached = true;
	}
	if(grassReached && !eaten) {
		linear_x = 0;
		angular_z = 0;
		msg.sender = robot_name+robot_number;
		msg.destination = grassName;
		Eat_pub.publish(msg);
	} else if(grassReached && eaten) {
		if(distance<3) {
			linear_x = 0;
			angular_z = 2.0;
		} else {
			grassDetected = false;
			grassReached = false;
			eaten = false;
		}
	}
}

void newSheep::identityRequest_callBack(se306_example::IdentityRequest request)
{
      //ROS_INFO("Request received by %s,%s",robot_name.c_str(),robot_number.c_str());
      //ROS_INFO("%s",request.abs_cmd_vel_angular_z);
	if(request.sender.compare(robot_name+robot_number) != 0) {
      se306_example::IdentityReply reply;
  bool result = doesIntersect(request.px, request.py);
  //ROS_INFO ("x is %f and y is %f and angle is %f", request.px, request.py, theta);
  if(result) {
   // ROS_INFO("YAY RESULT!");
   // ROS_INFO ("x is %f and y is %f", request.px, request.py);
    reply.sender = robot_name+robot_number;
    reply.destination = request.sender;
    reply.type = "sheep";
    /*this needs to be changed a bit to reflect actual velocity*/
    reply.abs_cmd_vel_angular_z = angular_z;
    reply.abs_cmd_vel_linear_x = linear_x;
    reply.theta = theta;
    Reply_pub.publish(reply);
    ROS_INFO("reply sent");
  }
	}

}
/*this function returns a double array depending on the theta
 * the double array shows the distance from you to the object in the x direction
 * and the y direction
 * The first element is the x direction and the second is the y.
 * The distances calculated are the distances from you to the next robot
 * so if the x value is negative for instance, you know that the object is on your left
 * if the y value is negatice the object is below you
 * etc
 * */
std::list<double> newSheep::calculateTheta(double theta, double distance)
{
      std::list<double> result;
  //ROS_INFO("Theta is %f", theta);
  double calcualted_theta;
  /*there are 4 cases in which differing methods have to be used
   * case 1 : when theta is between 0 and 90
   * case 2 : when theta is between 90 and 180
   * case 3 : when theta is between 180 and 270
   * case 4 : when theta is between 270 and 360
   * then there are the obvious cases that sin and cos and stuff will
   * not work for when theta == 0 or 90 or 270 or 360*/

  /*easy cases*/
  result.clear();
  if (theta==0){
    result.push_back(distance);
    result.push_back(0.00);
  }else if(theta == 90.00){
    //ROS_INFO("theta is 90");
    result.push_back(0.00);
    result.push_back(distance);
  }else if (theta==180){
    result.push_back(-distance);
    result.push_back(0.00);
  }else if (theta == 270){
    result.push_back(0.00);
    result.push_back(-distance);
  }
  /*case 1 : if theta is between 0 and 90 then the theta of the triangle that
   * we made will be the same theta as what is given to us*/
  else if ((theta>0)&&(theta<90)){
    calcualted_theta = theta * (M_PI/180.0);
    //x value is dist*cos(calculated_theta)
    //y value is dist*sin(calculated_theta)d
    result.push_back(distance * cos(calcualted_theta));
    result.push_back(distance * sin(calcualted_theta));

  }
  /*case 2: if the theta is between 90 and 180, then the theta of the triangle is 180-theta*/
  else if((theta>90)&&(theta<180)){
    calcualted_theta = 180 - theta;
    result.push_back(-distance * cos(calcualted_theta));
    result.push_back(distance * sin(calcualted_theta));

  }
  /*case 3 : if the theta value is between 180 and 270*/
  else if ((theta>180)&&(theta<270)){
    /*calulated theta must be theta - 180*/
    calcualted_theta = theta - 180;
    result.push_back(-distance * cos(calcualted_theta));
    result.push_back(-distance * sin(calcualted_theta));
  }
  /*case 4 : when theta is between 270 and 360*/
  else {
    /*calculated theta must be 360-theta*/
    calcualted_theta = 360 - theta;
    result.push_back(distance * cos(calcualted_theta));
    result.push_back(distance * sin(calcualted_theta));
  }

  //return result;
  return result;
}

void newSheep::grassEaten(std_msgs::String msg) {
	if(msg.data.compare(robot_name+robot_number) == 0) {
		eaten = true;
	}
}


bool newSheep::doesIntersect(float x, float y) {
  float leftX = px-(width*2);
  float rightX = px+(width*2);
  float top = py+(length*2);
  float bottom = py-(length*2);

  if(leftX <= x && rightX >= x) {
    if(top >= y && bottom <= y) {
      ROS_INFO("Within bounds");
      return true;
    }
  }
  return false;
}

/*The run method that we use to run the robot*/
ros::NodeHandle newSheep::run(){
      /*always call this line it defines the Nodehandler
       * it also creates the callback for the postion message*/
      ros::NodeHandle n = Robot::run();
  /*To define a new message
   * std::stringstream ss;
   * ss<<robot_name;
   * ros::Subscriber name_of_message = n.subscribe<nav_msgs::Odometry>("robot_"+ss.str()+"/message_name",1000, &Robot::callback_function,this);
   *
   * Then add to the list of subscribers
   *   std::list<ros::Subscriber>::iterator it;
   *   it = subsList.end();
   *   subsList.insert(it,StageOdo_sub);
   *
   * Publishers are defined in exactly the same way as they are in the given examoles
   * But you must add them to the publisherList*/
  //advertise() function will tell ROS that you want to publish on a given topic_
  //to stage
  RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>(robot_name+robot_number+"/cmd_vel",1000);
  //ros::Publisher RobotNode_stage_pub1 = n.advertise<geometry_msgs::Twist>("grass",1000);
  Request_pub = n.advertise<se306_example::IdentityRequest>("identityRequest", 1000);
  Reply_pub = n.advertise<se306_example::IdentityReply>("identityReply", 1000);
  Stop_pub = n.advertise<std_msgs::String>("SheepOne/stop",1000);
  Eat_pub = n.advertise<se306_example::eatGrass>("eat", 1000);

  std::stringstream ss;
  ss<<robot_name;

  ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>(robot_name+robot_number+"/odom",1000, &newSheep::stageOdom_callback, this);
  ros::Subscriber stageOdo_sub1 = n.subscribe<se306_example::IdentityRequest>("identityRequest",1000, &newSheep::identityRequest_callBack, this);
  ros::Subscriber StageOdo_sub2 = n.subscribe<se306_example::IdentityReply>("identityReply",1000, &newSheep::identityReply_callBack,this);
  ros::Subscriber StageLaser_sub3 = n.subscribe<sensor_msgs::LaserScan>(robot_name+robot_number+"/base_scan",1000, &newSheep::StageLaser_callback, this);
  ros::Subscriber stageOdo_sub4 = n.subscribe<std_msgs::String>("eaten",1000, &newSheep::grassEaten, this);
  //ros::Subscriber stagecmd = n.subscribe<geometry_msgs::Twist>("GhostSheepOne/cmd_vel",1000, &newSheep::ghostcmd, this);

  std::list<ros::Subscriber>::iterator it;
  it = subsList.end();
  subsList.insert(it,stageOdo_sub);

  //double th = 90*M_PI/2.0;
  ros::Rate loop_rate(5);
  nav_msgs::Odometry odom;
  geometry_msgs::Quaternion odom_quat;
  int counter = 0;

  int anglecounter = 0;
  //se306_example::Grass grass;

  /*define the while loop here*/
  while (ros::ok())
  {

    // RobotNode_cmdvel.angular.x = 0.2;
    //RobotNode_cmdvel.angular.y = 0.5;
	  if(grassDetected) {
		  grassThings();
	  } else if(!replyReceived && requestSent && distance <= 4) {
		  linear_x = 0.5;
		  angular_z = 2.0;
	  } else {
		  linear_x = 2.0;
		  angular_z = 0.0;
	  }

    RobotNode_cmdvel.linear.x = linear_x;
    //RobotNode_cmdvel.linear.y = 0.2;
    RobotNode_cmdvel.angular.z = angular_z;

    RobotNode_stage_pub.publish(RobotNode_cmdvel);
    //RobotNode_stage_pub.publish(grass);
    //ROS_INFO("OK");
    //ROS_INFO("theta is %f",theta);

    /*increase the health of the sheep
     * because the looprate is 10 per second*/
    ros::spinOnce();
    loop_rate.sleep();

  }
  return n;

}

double newSheep::yawFromQuaternion(double x, double y, double z,double w){
  double a = atan2((2.0*(w*z + x*y)),(1.0-2.0*(y*y+z*z)));
  a = a *180/M_PI;
  if (a < 0){
    a = 360 + a;
  }
  //ROS_INFO("%f",a);
  return a;
}

int main(int argc, char **argv)
{
	newSheep robot = newSheep("newSheep",argc,argv,12,10,"One");
	robot.run();
	return 0;
}
