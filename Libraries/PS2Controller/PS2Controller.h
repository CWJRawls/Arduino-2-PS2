#ifndef PS2Controller
#define PS2Controller

#include <Arduino.h>

//struct to declare which pin is used for which button. Covers digital pins only. See next struct for use of analog pins
struct controller_pins
{
	//Declare these first and as 8-bit integers to save space on the arduino
	uint8_t tri_pin : 8;
	uint8_t square_pin : 8;
	uint8_t circle_pin : 8;
	uint8_t x_pin : 8;
	uint8_t d_up : 8;
	uint8_t d_down : 8;
	uint8_t d_left : 8;
	uint8_t d_right : 8;
	uint8_t slct : 8;
	uint8_t strt : 8;
	uint8_t r1_pin : 8;
	uint8_t r2_pin : 8;
	uint8_t r3_pin : 8;
	uint8_t l1_pin : 8;
	uint8_t l2_pin : 8;
	uint8_t l3_pin : 8;
	
	//current struct size: 16 bytes
	//will add joysticks later when we figure them out.
}

//struct for declaring which pins are actually analog. Assumes an arduino board which will start with 'A'
struct uses_analog
{
	//if the pin used is analog set the number with the corresponding button. Otherwise set the number to -1
	uint8_t tri_pin : 8;
	uint8_t square_pin : 8;
	uint8_t circle_pin : 8;
	uint8_t x_pin : 8;
	uint8_t d_up : 8;
	uint8_t d_down : 8;
	uint8_t d_left : 8;
	uint8_t d_right : 8;
	uint8_t slct : 8;
	uint8_t strt : 8;
	uint8_t r1_pin : 8;
	uint8_t r2_pin : 8;
	uint8_t r3_pin : 8;
	uint8_t l1_pin : 8;
	uint8_t l2_pin : 8;
	uint8_t l3_pin : 8;
	
	//current struct size: 16 bytes
	//will add joysticks later when we figure them out.
}

class PS2Controller{
	public:
	PS2Controller(); //Constructor 1: sets pins to a sequential standard according to arduino uno. Will use analog pins as digital
	PS2Controller(controller_pins, uses_analog); //Constructor 2: uses custom pin settings
	~PS2Controller();
	writeTriangle(int); //using normal int here for ease of use for other programmers.
	writeCircle(int); //All of the methods that require an integer parameter control both the on and off state
	writeSquare(int);
	writeX(int);
	writeSelect(int);
	writeStart(int);
	writeR1(int);
	writeR2(int);
	writeR3(int);
	writeL1(int);
	writeL2(int);
	writeL3(int);
	writeUp(int);
	writeDown(int);
	writeLeft(int);
	writeRight(int);
}

#endif