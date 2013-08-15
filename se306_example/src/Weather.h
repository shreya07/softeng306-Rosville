/*
 * Weather.h
 *
 *  Created on: 14/08/2013
 *      Author: wasiq
 */

#ifndef WEATHER_H_
#define WEATHER_H_
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>

#include <sstream>
#include "math.h"

class Weather
{
public:
  Weather();
  virtual ~Weather();
};

#endif /* WEATHER_H_ */
