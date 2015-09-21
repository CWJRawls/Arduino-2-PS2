#include <OptiMouse.h>
#include <PAN3101.h>
#include "PS2Common.h"
#include "dataForController_t.h"

/*
September 20 2015
Connor Rawls; Chris Zlaket; Megan Patzem

Code to intake and send data to a ps2 controller for the
game Simpsons Hit and Run.

Requires the use of x, square, circle, and triangle buttons
along with the left joystick.
*/

dataForController_t data = getBlankData();

void setup()
{
  //Digital pins
  pinMode(2, INPUT); //x
  pinMode(3, INPUT); //Square
  pinMode(4, INPUT); //Circle
  pinMode(5, INPUT); //Triangle
  
  //analog pins do not need to have a mode set
  
}

void loop()
{
  
}
}



