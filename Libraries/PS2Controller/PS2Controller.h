#ifndef PS2Controller
#define PS2Controller

#include <Arduino.h>
#include <inttypes.h>

//struct to declare which pin is used for which button. Covers digital pins only. See next struct for use of analog pins
struct controller_pins
{
	//Declare these first and as 8-bit integers to save space on the arduino
	uint8_t pins[9];
	/* Pin indeces
	0 x button
	1 O button
	2 Tri button
	3 Start button
	4 R1 button
	5 L1 button
	6 Joystick SDI
	7 Joystick CLK
	8 Chip Select 
	*/
	
	//current struct size: 16 bytes
	
}

//Struct for containing controller data

struct c_data
{
	uint8_t data[10];
	/* Data indeces
	0 x
	1 o
	2 Tri
	3 Start
	4 R1
	5 L1
	6 R Joy x
	7 R Joy y
	8 L Joy x
	9 L Joy y
	*/
}

class PS2Controller{
	private:
	controller_pins pins;
	c_data current_data;	
	void writeTriangle(uint8_t); //using normal int here for ease of use for other programmers.
	void writeCircle(uint8_t);
	void writeX(uint8_t);
	void writeStart(uint8_t);
	void writeR1(uint8_t);
	void writeL1(uint8_t);
	void writeRJoy(uint8_t, uint8_t);
	void writeLJoy(uint8_t, uint8_t);
	public:
	PS2Controller(void); //Constructor 1: sets pins to a sequential standard according to arduino uno. Will use analog pins as digital
	PS2Controller(controller_pins); //Constructor 2: uses custom pin settings
	~PS2Controller(void);
	void sendData(c_data); //used to communicate current frame of data to PCB

}

#endif