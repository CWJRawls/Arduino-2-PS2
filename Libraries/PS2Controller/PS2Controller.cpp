#include "PS2Controller.h"


PS2Controller::PS2Controller(void)
{
	//set default values, has no shoudler button use
	pins.x_pin = 2;
	pins.circle_pin = 3;
	pins.square_pin = 4;
	pins.tri_pin = 5;
	pins.d_down = 6;
	pins.d_left = 7;
	pins.d_right = 8;
	pins.d_up = 9;
	pins.slct = -1;
	pins.start = 10;
	pins.r1_pin = -1;
	pins.r2_pin = -1;
	pins.r3_pin = -1;
	pins.l1_pin = -1;
	pins.l2_pin = -1;
	pins.l3_pin = -1;
}

PS2Controller::PS2Controller(controller_pins p, uses_analog a)
{
	//sets based on user code.
	pins = p;
	analog = a;
}

void writeTriangle(int val)
{
	if(pins.tri > -1) //Be careful here, some boards don't use 0 as a normal pin
	{
		
	}
}