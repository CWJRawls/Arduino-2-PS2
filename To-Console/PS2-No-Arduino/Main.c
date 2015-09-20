#include <stdio.h>
#include <avr/io.h>
#include "PS2interface.h"
#include "dataForController_t.h"

dataForController_t getBlankData(void)
{
	dataForController_t blank;
	
	blank.triangleOn = 1;
	blank.circleOn = 1;
	blank.squareOn = 1;
	blank.crossOn = 1;
	blank.l1On = 1;
	blank.l2On = 1;
	blank.l3On = 1;
	blank.r1On = 1;
	blank.r2On = 1;
	blank.r3On = 1;
	blank.startOn = 1;
	blank.selectOn = 1;
	blank.homeOn = 1;
	blank.dpadLeftOn = 1;
	blank.dpadRightOn = 1;
	blank.dpadUpOn = 1;
	blank.dpadDownOn = 1;
	blank.leftStickX = 127;
	blank.leftStickY = 127;
	blank.rightStickX = 127;
	blank.rightStickY = 127;
	
	return blank;
	
}

dataForController_t getData(void)
{
	dataForController_t controllerData = getBlankData();
	
	/*
	Commented out pin reading
	*/
	
	return controllerData;
}

int main(void)
{
	startPS2Communication();
	for(;;)
	{
		dataForController_t controlData = getData();
		sendPS2Data(controlData);
	}
	
	return 0;
}