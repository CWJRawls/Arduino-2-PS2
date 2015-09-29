#include "PS2Controller.h"


PS2Controller::PS2Controller(void)
{
	pins.x_pin = 2;
	pins.circle_pin = 3;
	pins.square_pin = 4;
	pins.tri_pin = 5;
	pins.d_down = 6;
	pins.d_left = 7;
	pins.d_right = 8;
}