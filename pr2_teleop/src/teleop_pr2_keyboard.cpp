/*
 * teleop_pr2_keyboard
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <ORGANIZATION> nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// Author: Kevin Watts
#include <termios.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "std_msgs/String.h"

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#define KEYCODE_A 0x61
#define KEYCODE_D 0x64
#define KEYCODE_S 0x73
#define KEYCODE_W 0x77 
#define KEYCODE_Q 0x71
#define KEYCODE_E 0x65
#define KEYCODE_1 0x31
#define KEYCODE_2 0x32
#define KEYCODE_3 0x33
#define KEYCODE_ENTER 0x20

#define KEYCODE_A_CAP 0x41
#define KEYCODE_D_CAP 0x44
#define KEYCODE_S_CAP 0x53
#define KEYCODE_W_CAP 0x57
#define KEYCODE_Q_CAP 0x51
#define KEYCODE_E_CAP 0x45

class TeleopPR2Keyboard
{
private:
  double walk_vel, run_vel, yaw_rate, yaw_rate_run;
  geometry_msgs::Twist cmd;

  ros::NodeHandle n_;
  ros::Publisher vel_pub_;
  ros::Publisher gate_opener1;
  ros::Publisher gate_opener2;
  ros::Publisher gate_opener3;
  ros::Publisher sheepSell;

  std_msgs::String one, two, three;

public:
  void init()
  {
    cmd.linear.x = cmd.linear.y = cmd.angular.z = 0;

    vel_pub_ = n_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    gate_opener1 = n_.advertise<std_msgs::String>("toggleGate/GateOne", 1000);
    gate_opener2 = n_.advertise<std_msgs::String>("toggleGate/GateTwo", 1000);
    gate_opener3 = n_.advertise<std_msgs::String>("toggleGate/GateThree", 1000);
    sheepSell = n_.advertise<std_msgs::String>("sellSheep", 1000);
    
    ros::NodeHandle n_private("~");
    n_private.param("walk_vel", walk_vel, 0.5);
    n_private.param("run_vel", run_vel, 1.0);
    n_private.param("yaw_rate", yaw_rate, 1.0);
    n_private.param("yaw_run_rate", yaw_rate_run, 1.5);

  }

  ~TeleopPR2Keyboard()
  {
  }
  void keyboardLoop();

};

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  exit(0);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pr2_base_keyboard");

  TeleopPR2Keyboard tpk;
  tpk.init();

  signal(SIGINT, quit);

  tpk.keyboardLoop();

  return (0);
}

void TeleopPR2Keyboard::keyboardLoop()
{
  char c;
  bool dirty = false;

  // get the console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &= ~(ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);


puts("_|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_   ");
puts(" |       |       |       |       |       |       |       |       |"    );
puts("    _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|");
puts("     |       |       |       |       |       |       |       |       |");
puts("_|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_   ");
puts(" |       |       |       |       |       |       |       |       |    ");
puts("    _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|");
puts("     |       |       |       |       |       |       |       |       |");
puts("_|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_   ");
puts(" |       |       |       |       |       |       |       |       |    ");
puts("    _|_     _Welcome to Rosville's SE 306 Project 1 _|_     _|_     _|");
puts("     |       |       |       |       |       |       |       |       |");
puts("_|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_   ");
puts(" |       |       |       |       |       |       |       |       |    ");
puts("    _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|");
puts("     |       |       |       |       |       |       |       |       |");
puts("_|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_   ");
puts(" |       |       |       |       |       |       |       |       |    ");
puts("    _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|");
puts("     |       |       |       |       |       |       |       |       |");
puts("_|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_     _|_   ");
puts(" |       |       |       |       |       |       |       |       |    ");

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Commands:\nUse 'WS' to move the Farmer");
  puts("Use 'QE' to make the Farmer run");
  puts("Press 'Shift' to run");
puts("'1', '2' and '3' to open the Gates");
  for (;;)
  {
    // get the next event from the keyboard
    if (read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

    cmd.linear.x = cmd.linear.y = cmd.angular.z = 0;
   std::stringstream ss;//create a stringstream
   ss << c;//add number to the stream
    
	puts(ss.str().c_str());
    switch (c)
    {
      // Walking
      case KEYCODE_W:
        cmd.linear.x = walk_vel;
        dirty = true;
        break;
      case KEYCODE_S:
        cmd.linear.x = -walk_vel;
        dirty = true;
        break;
      case KEYCODE_A:
        cmd.linear.y = walk_vel;
        dirty = true;
        break;
      case KEYCODE_D:
        cmd.linear.y = -walk_vel;
        dirty = true;
        break;
      case KEYCODE_Q:
        cmd.angular.z = yaw_rate;
        dirty = true;
        break;
      case KEYCODE_E:
        cmd.angular.z = -yaw_rate;
        dirty = true;
        break;

        //gate
      case KEYCODE_1:
        one.data = "open";
	gate_opener1.publish(one);
        dirty = true;
        break;
      case KEYCODE_2:
          two.data = "open";
	gate_opener2.publish(two);
        dirty = true;
        break;
      case KEYCODE_3:
          three.data = "open";
	gate_opener3.publish(three);
        dirty = true;
        break;
      case KEYCODE_ENTER:
        three.data = "sell";
	sheepSell.publish(three);
        dirty = true;
        break;

        // Running 
      case KEYCODE_W_CAP:
        cmd.linear.x = run_vel;
        dirty = true;
        break;
      case KEYCODE_S_CAP:
        cmd.linear.x = -run_vel;
        dirty = true;
        break;
      case KEYCODE_A_CAP:
        cmd.linear.y = run_vel;
        dirty = true;
        break;
      case KEYCODE_D_CAP:
        cmd.linear.y = -run_vel;
        dirty = true;
        break;
      case KEYCODE_Q_CAP:
        cmd.angular.z = yaw_rate_run;
        dirty = true;
        break;
      case KEYCODE_E_CAP:
        cmd.angular.z = -yaw_rate_run;
        dirty = true;
        break;
    }

    if (dirty == true)
    {
      vel_pub_.publish(cmd);
    }

  }
}

