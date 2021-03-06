#include "PS2interface.h"
#include "dataForController_t.h"
#include <stdio.h>

void setup(){
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(4, OUTPUT);
  startPS2Communication();
}

void loop()
{
  //Get latest data
  dataForController_t controllerData = getControllerData();
  sendPS2Data(controllerData);
}

dataForController_t getControllerData()
{
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  dataForController_t controllerData;
  controllerData.triangleOn = 1;
  controllerData.circleOn = 1;
  controllerData.squareOn = 1;
  controllerData.crossOn = 1;
  controllerData.dpadUpOn = 1;
  controllerData.dpadDownOn = 1;
  controllerData.dpadLeftOn = 1;
  controllerData.dpadRightOn = 1;
  controllerData.l1On = 1;
  controllerData.r1On = 1;
  controllerData.r2On = 1;
  controllerData.l2On = 1;
  controllerData.l3On = 1;
  controllerData.r3On = 1;
  controllerData.selectOn = 1;
  controllerData.startOn = 1;
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use  
  controllerData.leftStickX = 127;
  controllerData.leftStickY = 127;
  controllerData.rightStickX = 127;
  controllerData.rightStickY = 127;
  // And return the data!
  return controllerData;
}
