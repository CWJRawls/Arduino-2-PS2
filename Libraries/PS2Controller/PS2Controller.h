
#include <Arduino.h>
#include <inttypes.h>

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


class PS2Controller{
	private:
	uint8_t pins[9];
	uint8_t pinsins[9];
	uint8_t data[10];
	public:	
	void writeTriangle(uint8_t val); //using normal int here for ease of use for other programmers.
	void writeCircle(uint8_t val);
	void writeX(uint8_t val);
	void writeStart(uint8_t val);
	void writeR1(uint8_t val);
	void writeL1(uint8_t val);
	void writeRJoy(uint8_t val, uint8_t val2);
	void writeLJoy(uint8_t val, uint8_t val2);
	PS2Controller(); //Constructor 1: sets pins to a sequential standard according to arduino uno. Will use analog pins as digital
	//PS2Controller(controller_pins); //Constructor 2: uses custom pin settings
	void setPins(uint8_t pins[9]);
	void sendData(uint8_t data[10]); //used to communicate current frame of data to PCB

};
