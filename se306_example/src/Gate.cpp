/*
 * Gate.cpp
 *
 *  Created on: Aug 14, 2013
 *      Author: surbhi
 */

#include "Gate.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"
#include "Robot.h"
//#include <thread>

/*Constructor
 * The :RobotRobot(robot_name,argc,argv,px,py,robot_number) part at the end
 * tells the compiler to run the superclass constructor
 * It is exactly like the super(robot_name,argc,argv,px,py) call in Java
 * if you are unsure of what that means look it up in the link provided
 * http://docs.oracle.com/javase/tutorial/java/IandI/super.html
 *  */
Gate::Gate(std::string robot_name, int argc, char **argv) :
    Robot(robot_name, argc, argv)
{
  //can do extra stuff here if you like
  isHorizontal = false;
  isOpen = false;
  shouldMoveGate = false;
  ROS_INFO("constructed");

}
/*destrustor
 * I have not implemented it here but you should*/
Gate::~Gate()
{
  // TODO Auto-generated destructor stub
}

void Gate::moveGate()
{

  //send message while distance is reached.
  ROS_INFO("Gate location:(%f %f) desitnation:%f", px, py, destination);

  if (isHorizontal)
  {

    if (abs(destination - px) != 0)
    {

      ROS_INFO("Publishing message");
      RobotNode_stage_pub.publish(moveMessage);

    }
    else
    {
      shouldMoveGate = false;
    }

  }

  if (!isHorizontal)
  {

    if (abs(destination - py) != 0)
    {

      ROS_INFO("Publishing message");
      RobotNode_stage_pub.publish(moveMessage);

    }
    else
    {
      shouldMoveGate = false;
    }

  }

}

/*Callback method for the robots position*/

void Gate::stageOdom_callback(nav_msgs::Odometry msg)
{
  this->px = initialX + msg.pose.pose.position.x;
  this->py = initialY + msg.pose.pose.position.y;
  //ROS_INFO("Odom distance=%f",px);

}

void Gate::Gate_callback(std_msgs::String msg)
{
  ROS_INFO("Gate %s: received message", robot_name.c_str());

  double distanceToMove = 5;

  moveMessage = geometry_msgs::Twist();

  if (isHorizontal)
  {
    if (isOpen)
    {
      //Need to close the gate.....
      ROS_INFO("Need to close the gate");

      //Check the direction to move to close the gate.
      if (directionToOpen.compare("left"))
      {
        //Move to the left!
        destination = px - distanceToMove;
        moveMessage.linear.x = -1;
        ROS_INFO("Moving to the left");

      }
      else
      {
        //Moving to the right
        destination = px + distanceToMove;
        moveMessage.linear.x = 1;
        ROS_INFO("Moving to the right");

      }

    }
    else
    {

      //Gate is closed. Need to open
      ROS_INFO("Need to open the gate");

      //Check the direction to move to close the gate.
      if (directionToOpen.compare("left"))
      {
        //Move to the right to close!
        destination = px + distanceToMove;
        moveMessage.linear.x = 1;
        ROS_INFO("Moving to the right");

      }
      else
      {
        //Moving to the left to close
        destination = px - distanceToMove;
        moveMessage.linear.x = -1;
        ROS_INFO("Moving to the left");

      }

    }

    isOpen = !isOpen;

  } //End of Horizontal

  if (!isHorizontal)
  {
    if (isOpen)
    {
      //Need to close the gate.....
      ROS_INFO("Need to close the gate");

      //Check the direction to move to close the gate.
      if (directionToOpen.compare("down"))
      {
        //Move to the left!
        destination = py - distanceToMove;
        moveMessage.linear.y = -1;
        ROS_INFO("Moving to the down");

      }
      else
      {
        //Moving to the right
        destination = py + distanceToMove;
        moveMessage.linear.y = 1;
        ROS_INFO("Moving to the up");

      }

    }
    else
    {

      //Gate is closed. Need to open
      ROS_INFO("Need to open the gate");

      //Check the direction to move to close the gate.
      if (directionToOpen.compare("down"))
      {
        //Move to the right to close!
        destination = py + distanceToMove;
        moveMessage.linear.y = 1;
        ROS_INFO("Moving to the down");

      }
      else
      {
        //Moving to the left to close
        destination = py - distanceToMove;
        moveMessage.linear.y = -1;
        ROS_INFO("Moving to the up");

      }

    }

    isOpen = !isOpen;

  } //End of Vertical

  shouldMoveGate = true;

}

/*The run method that we use to run the robot*/
ros::NodeHandle Gate::run()
{
  /*always call this line it defines the Nodehandler
   * it also creates the callback for the postion message*/
  ros::NodeHandle n = Robot::run();
  isOpen = false;

  //Get parameter from launch file.
  this->isHorizontal = false;

  n.getParam("isHorizontal", this->isHorizontal);
  n.getParam("px", this->px);
  n.getParam("py", this->py);
  n.getParam("px", this->initialX);
  n.getParam("py", this->initialY);
  n.getParam("directionToOpen", directionToOpen);

  moveMessage = geometry_msgs::Twist();

  ROS_INFO("helloooooo");
  if (isHorizontal)
  {
    ROS_INFO("This gate is horizontal");
  }
  else
  {
    ROS_INFO("This gate is vertical");
  }

  ROS_INFO(robot_name.c_str());

  //Set position co-ordinates
  //double x= -1;
  //n.getParam("x",px);
  //n.getParam("y",py);

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
  ros::Rate loop_rate(10);
  /*define the while loop here*/
  ros::Subscriber GateListener = n.subscribe<std_msgs::String>("/toggleGate/" + robot_name, 1000, &Gate::Gate_callback,
                                                               this);
  RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  while (ros::ok())
  {
    //ROS_INFO("OK");
    if (shouldMoveGate)
    {

      moveGate();
    }

    ros::spinOnce();
    loop_rate.sleep();
  }
  //
  return n;
}

int main(int argc, char **argv)
{
  Gate robot = Gate("Gate", argc, argv);
  robot.run();
  return 0;
}

