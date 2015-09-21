#include <stdio.h>
#include <stdin.h>
#include "dataForController_t.h"
#include "PS2Common.h"

dataForController_t getBlankData(void)
{
	dataForController_t controlData;
	
	controlData.crossOn = 1;
	controlData.circleOn = 1;
	controlData.squareOn = 1;
	controlData.triangleOn = 1;
	controlData.dpadUpOn = 1;
	controlData.dpanDownOn = 1;
	controlData.dpadLeftOn = 1;
	controlData.dpadRightOn = 1;
	controlData.l1On = 1;
	controlData.l2On = 1;
	controlData.l3On = 1;
	controlData.r1On = 1;
	controlData.r2On = 1;
	controlData.r3On = 1;
	controlData.rightStickX = 127;
	controlData.rightStickY = 127;
	controlData.leftStickX = 127;
	controlData.leftStickY = 127;
	controlData.homeOn = 1; //Just because it is in the struct, does not exist on ps2
	
	return controlData;
}