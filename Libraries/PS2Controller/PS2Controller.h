#ifndef PS2Controller
#define PS2Controller

#include <Arduino.h>
#include <inttypes.h>

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
	private:
	controller_pins pins;
	uses_analog analog;
	public:
	PS2Controller(void); //Constructor 1: sets pins to a sequential standard according to arduino uno. Will use analog pins as digital
	PS2Controller(controller_pins, uses_analog); //Constructor 2: uses custom pin settings
	~PS2Controller(void);
	void writeTriangle(int); //using normal int here for ease of use for other programmers.
	void writeCircle(int); //All of the methods that require an integer parameter control both the on and off state
	void writeSquare(int);
	void writeX(int);
	void writeSelect(int);
	void writeStart(int);
	void writeR1(int);
	void writeR2(int);
	void writeR3(int);
	void writeL1(int);
	void writeL2(int);
	void writeL3(int);
	void writeUp(int);
	void writeDown(int);
	void writeLeft(int);
	void writeRight(int);
}

#endif