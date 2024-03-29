#include "Poop.h"
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
#include "std_msgs/Bool.h"

#include "../msg_gen/cpp/include/se306_example/IdentityRequest.h"
#include "../msg_gen/cpp/include/se306_example/IdentityReply.h"

Poop::Poop(std::string robot_name, int argc, char **argv):Robot(robot_name,argc,argv)
{
	distance = 15;
	linear_x = 0.0;
	angular_z = 0.0;
	theta = 120.0*M_PI/180.0;
	constLinear = -0.2;
	nodeDistance = 30;
	targetTheta = 0;
	width = 1;
	length = 2;
	doStop = false;
	initialX=-1;
	initialY=-1;

}
/*destrustor*/
Poop::~Poop()
{
	// TODO Auto-generated destructor stub
}


/*Callback method for the robots position*/
void Poop::stageOdom_callback(nav_msgs::Odometry msg){
	px = initialX + msg.pose.pose.position.x;
	py = initialY + msg.pose.pose.position.y;
}


void Poop::setPoop(geometry_msgs::Twist msg){
	if(doStop) {
		linear_x = 0;
		angular_z = 0;
		ROS_INFO("Has been set to 0");
	} else {
		linear_x = msg.linear.x;
		angular_z = msg.angular.z;
		ROS_INFO("Not being set 0");
	}

}

void Poop::stageStop_callback(std_msgs::String msg)
{
	if(msg.data.compare("stop") == 0) {
		if(!doStop) {
			doStop = true;
		}
	}

}


/* request the sheep to drop poop*/
void Poop::requestPoop(const std_msgs::String::ConstPtr& request) {
	if (request->data.compare("Request") == 0) {
		linear_x = 0;
		angular_z = 0;
		ROS_INFO("velocity1: %f, angular1: %f", linear_x, angular_z);
		ROS_INFO("Pooped appx: [%s]", request->data.c_str());
	}
}



/*The run method that we use to run the robot*/
ros::NodeHandle Poop::run(){

	ros::NodeHandle n = Robot::run();

	if(!n.getParam("owner",poopOwner)){
	  ROS_ERROR("Poop owner not set");
	 }


	  if(!n.getParam("px", this->px)){
	    ROS_ERROR("[Poop][%s] px not set",robot_name.c_str());


	  }else{
	    initialX=px;
	  }


	  if(!n.getParam("py", this->py)){
	    ROS_ERROR("[Poop][%s] py not set",robot_name.c_str());

	  }else{
	    initialY=py;
	  }


	// publish the poop message
	publishPoop = n.advertise<geometry_msgs::Twist>(robot_name+"/cmd_vel",1000);

	// initialize subscribers listen to sheep position and velocity
	sheepVel = n.subscribe<geometry_msgs::Twist>("SheepOne/cmd_vel",1000, &Poop::setPoop, this);
	poopReq = n.subscribe<std_msgs::String>("poop", 1000, &Poop::requestPoop, this);

	/* Add subscribers to subscriber list*/
	std::list<ros::Subscriber>::iterator it;
	it = subsList.end();
	subsList.insert(it,sheepPos);
	subsList.insert(it,sheepVel);

	/*set to 10 messages per second*/
	ros::Rate loop_rate(10);

	/*define the while loop here*/
	while (ros::ok()){

		ROS_INFO("velocity1: %f, angular1: %f", linear_x, angular_z);
		// set poop velocity to match sheep poop
		poopVel.linear.x = linear_x;
		poopVel.angular.z = angular_z;

		publishPoop.publish(poopVel);

		ros::spinOnce();
		loop_rate.sleep();
	}
	return n;
}


//int main(int argc, char **argv)
//{
//	Poop robot = Poop("Poop",argc,argv,5,1,"One");
//	robot.run();
//	return 0;
//}


