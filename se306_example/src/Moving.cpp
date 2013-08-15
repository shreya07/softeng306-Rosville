/*
 * Moving.cpp
 * Super class for moving entities
 *  Created on: 12/08/2013
 *      Author: raouldc
 */

#include "Moving.h"

class Moving
{
public:
  double linear;
  double angular();
  void move();
private:
  //nothing as of now

};

Moving::Moving()
{
  // Constructor

}

Moving::~Moving()
{
  // Destructor
}

