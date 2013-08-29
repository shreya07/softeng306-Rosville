/*
 * R3.cpp
 *
 *  Created on: 12/08/2013
 *      Author: Shreya
 */

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
#include <tf/transform_broadcaster.h>
#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 *  */
Sheep1::Sheep1(std::string robot_name, int argc, char **argv,double px,double py, std::string robot_number):Robot(robot_name,argc,argv,px,py,robot_number)
{
  //can do extra stuff here if you like
  //this-> x = px;
  //this-> y = py;

  distance = 15;
  linear_x = 2.0;
  angular_z = 2.0;
  theta = 0.0;
  constLinear = -0.2;
  nodeDistance = 30;
  targetTheta = 0;
  width = 1;
  length = 2;
  followGhost = false;
  abs_cmd_vel_linear_x=0;
  abs_cmd_vel_angular_z=0;
  prevpx=0;
  prevpy=0;
  //is this correct?
  PX_INIT = px;
  PY_INIT = py;
  old_ang_z = 2.0;
  once = false;


}
/*destrustor
 * I have not implemented it here but you should*/
Sheep1::~Sheep1()
{
  // TODO Auto-generated destructor stub
}

/*Callback method for the robots position*/
void Sheep1::stageOdom_callback(nav_msgs::Odometry msg){
  //int x = msg.linear.x;
  prevpx = px;
  prevpy = py;
  px = PX_INIT + msg.pose.pose.position.x;
  py = PY_INIT + msg.pose.pose.position.y;
  //ROS_INFO("w: %f", msg.pose.pose.orientation.w);
  //ROS_INFO("theta: %f", theta);
  //ROS_INFO("callback called");
  double theCorrectTheta = yawFromQuaternion(msg.pose.pose.orientation.x,msg.pose.pose.orientation.y,msg.pose.pose.orientation.z,msg.pose.pose.orientation.w);
  //ROS_INFO("the theta is %f",theCorrectTheta);
  theta = theCorrectTheta;
}


void Sheep1::StageLaser_callback(sensor_msgs::LaserScan msg)
{
  distance = msg.ranges[20];
  se306_example::IdentityRequest request;
  //ROS_INFO("distance: %s , %f", robot_name.c_str(),distance);
  //ROS_INFO("Angle is %f", theta);
  if(distance <= 10) {

    ROS_INFO("%f",distance);
    RobotNode_cmdvel.linear.x = linear_x;
    RobotNode_cmdvel.angular.z = angular_z;
    //RobotNode_stage_pub.publish(RobotNode_cmdvel);

    request.sender = robot_name;

    //ROS_INFO ("Calculated theta is %f", theta);
    std::list<double> pose = calculateTheta(theta, distance);
    double x = pose.front();
    double y = pose.back();
    //ROS_INFO ("Calculated x and y values x = %f, y=%f", x,y);

    request.px = this->px+x+(width/2.0);
    //pose.pop_front();
    request.py = py+y+(length/2.0);
    //pose.pop_front();

    //ROS_INFO("x: %f", request.px);
    //ROS_INFO("y: %f", request.py);

    Request_pub.publish(request);
    std_msgs::String status;
    status.data = "stop";
    Stop_pub.publish(status);
    //ROS_INFO("Request sent");

    //ROS_INFO("theta: %f", theta);
  }


}

void Sheep1::identityReply_callBack(se306_example::IdentityReply reply)
{
  ROS_INFO("reply received");
  ROS_INFO("%s is being returned", reply.type.c_str());
  if(reply.destination.compare(robot_name)==0) {

    if(reply.type.compare("grass")==0) {
      //ROS_INFO("Grass detected");
    }else if(reply.type.compare("sheep")==0){
      ROS_INFO("Swarm starting");
     // ROS_INFO("%f",this->abs_cmd_vel_angular_z);
      //calculate the distance between you and the sheep
      //this is the distance variable
      //make sure that this distance is more than 2
      if (distance < 2.0){
        ROS_INFO("Moving Back!");
        //move back and avoid
        //shall implement this later
      }else{
        ROS_INFO("Moving Forward");
        this->linear_x=reply.abs_cmd_vel_linear_x;
        if((theta<= reply.theta+7)||(theta>=reply.theta-7)){
          //movin the same direction
          this-> angular_z =old_ang_z;


        }else{
          //we are not moving in the same direction
          double thetadifference = theta- reply.theta;
          old_ang_z = angular_z;
          this->angular_z = reply.abs_cmd_vel_angular_z + (thetadifference/45.00);
          once = true;

        }
        //if he is travelling the same direction as you
        //ROS_INFO("%f is the abs_x of the sheep and %f is your abs angular z", reply.abs_cmd_vel_angular_z, this-> abs_cmd_vel_angular_z);
        //if (((reply.abs_cmd_vel_linear_x>0)&&(this->abs_cmd_vel_linear_x>0))||((reply.abs_cmd_vel_linear_x<0)&&(this->abs_cmd_vel_linear_x<0))){
        //pick the one thats ordered the best
//        }else{
//          //if you are not travelling the same direction as the othersheep
//          std::list<double> pose = calculateTheta(theta, distance);
//          //get the x and y values of the
//          double x = pose.front();
//          double y = pose.back();
//          ROS_INFO("reply x is %f and y is %f, theta was %f", x,y,theta);
//          ROS_INFO("px is %f py is %f",px,py);
//          //pick the one that is the graetest xvalue first
//          if((px<x)||(py<y)){
//            //set your linear_x to be the same as the otherpersomes linear x
//            //need to rotate the sheep twice
//
//            //this->angular_z = reply.abs_cmd_vel_angular_z;
//            //this->linear_x = reply.abs_cmd_vel_linear_x;
//            this -> angular_z = 0;
//            this -> linear_x = 0;
//            //need to set the command velocity again?
//            //is it overriden by anything
//          }
//        }
      }
      //swarm completed
      ROS_INFO("Swarm Completed");

    }
    else  {
      ROS_INFO("Don't know what it is");
    }
  }

}

void Sheep1::identityRequest_callBack(se306_example::IdentityRequest request)
{
  //ROS_INFO("Request received by %s,%s",robot_name.c_str(),robot_number.c_str());
  //ROS_INFO("%s",request.abs_cmd_vel_angular_z);
  se306_example::IdentityReply reply;
  bool result = doesIntersect(request.px, request.py);
  //ROS_INFO ("x is %f and y is %f and angle is %f", request.px, request.py, theta);
  if(result) {
    ROS_INFO("YAY RESULT!");
    ROS_INFO ("x is %f and y is %f", request.px, request.py);
    reply.sender = robot_name;
    reply.destination = request.sender;
    reply.type = "sheep";
    /*this needs to be changed a bit to reflect actual velocity*/
    reply.abs_cmd_vel_angular_z = angular_z;
    reply.abs_cmd_vel_linear_x = linear_x;
    reply.theta = theta;
    Reply_pub.publish(reply);
    ROS_INFO("reply sent");
  }

  //ROS_INFO("does intersect? %d ", result);

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
std::list<double> Sheep1::calculateTheta(double theta, double distance)
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

void Sheep1::stageFollow_callback(std_msgs::String msg)
{
  if(msg.data.compare("follow") == 0) {
    followGhost = true;
  }
}

void Sheep1::ghostcmd(geometry_msgs::Twist msg){
  //int x = msg.linear.x;
  if(followGhost) {
    linear_x = msg.linear.x;
    angular_z = msg.angular.z;
  }

}

bool Sheep1::doesIntersect(float x, float y) {
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
ros::NodeHandle Sheep1::run(){
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

  std::stringstream ss;
  ss<<robot_name;

  ros::Subscriber stageOdo_sub = n.subscribe<nav_msgs::Odometry>(robot_name+robot_number+"/odom",1000, &Sheep1::stageOdom_callback, this);
  ros::Subscriber stageOdo_sub1 = n.subscribe<se306_example::IdentityRequest>("identityRequest",1000, &Sheep1::identityRequest_callBack, this);
  ros::Subscriber StageOdo_sub2 = n.subscribe<se306_example::IdentityReply>("identityReply",1000, &Sheep1::identityReply_callBack,this);
  ros::Subscriber StageLaser_sub3 = n.subscribe<sensor_msgs::LaserScan>(robot_name+robot_number+"/base_scan",1000, &Sheep1::StageLaser_callback, this);
  ros::Subscriber stageOdo_sub4 = n.subscribe<std_msgs::String>(robot_name+robot_number+"/follow",1000, &Sheep1::stageFollow_callback, this);
  ros::Subscriber stagecmd = n.subscribe<geometry_msgs::Twist>("GhostSheep/cmd_vel",1000, &Sheep1::ghostcmd, this);

  std::list<ros::Subscriber>::iterator it;
  it = subsList.end();
  subsList.insert(it,stageOdo_sub);

  //double th = 90*M_PI/2.0;
  ros::Rate loop_rate(10);
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

    RobotNode_cmdvel.linear.x = linear_x;
    //RobotNode_cmdvel.linear.y = 0.2;
    RobotNode_cmdvel.angular.z = angular_z;
    counter++;

    RobotNode_stage_pub.publish(RobotNode_cmdvel);
    if (once)
    {
      anglecounter++;
      if (anglecounter%30 == 0)
      {
        angular_z = old_ang_z;
        once = false;
      }
    }
    //RobotNode_stage_pub.publish(grass);
    //ROS_INFO("OK");
    //ROS_INFO("theta is %f",theta);
    ros::spinOnce();
    loop_rate.sleep();

  }
  return n;

}

double Sheep1::yawFromQuaternion(double x, double y, double z,double w){
  double a = atan2((2.0*(w*z + x*y)),(1.0-2.0*(y*y+z*z)));
  a = a *180/M_PI;
  if (a < 0){
    a = 360 + a;
  }
  //ROS_INFO("%f",a);
  return a;
}
//int main(int argc, char **argv)
//{
//	Sheep1 robot = Sheep1("Sheep",argc,argv,15,20,"One");
//	robot.run();
//	return 0;
//}


