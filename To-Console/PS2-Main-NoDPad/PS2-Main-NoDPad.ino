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
  controllerData.triangleOn = digitalRead(2);
  controllerData.circleOn = digitalRead(3);
  controllerData.squareOn = digitalRead(4);
  controllerData.crossOn = digitalRead(5);
  controllerData.dpadUpOn = 1;
  controllerData.dpadDownOn = 1;
  controllerData.dpadLeftOn = 1;
  controllerData.dpadRightOn = 1;
  controllerData.l1On = digitalRead(6);
  controllerData.r1On = digitalRead(7);
  controllerData.r2On = digitalRead(8);
  controllerData.l2On = digitalRead(9);
  controllerData.l3On = digitalRead(10);
  controllerData.r3On = digitalRead(11);
  controllerData.selectOn = digitalRead(12);
  controllerData.startOn = digitalRead(13);
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use  
  controllerData.leftStickX = analogRead(A0) >> 2;
  controllerData.leftStickY = analogRead(A1) >> 2;
  controllerData.rightStickX = analogRead(A2) >> 2;
  controllerData.rightStickY = analogRead(A3) >> 2;
  // And return the data!
  return controllerData;
}
