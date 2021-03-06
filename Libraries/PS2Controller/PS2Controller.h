
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>

	/* Pin indeces
	0 x button
	1 O button
	2 square button
	3 Tri button
	4 Start button
	5 R1 button
	6 L1 button
	7 R3
	8 L3
	9 Joystick SDI (Reserved for SPI)
	10 Joystick CLK (Reserved for SPI)
	11 Chip Select
	*/
	
	/* Data indeces
	0 x
	1 o
	2 square
 	3 Tri
	4 Start
	5 R1
	6 L1
	7 R3
	8 L3
	9 R Joy x
	10 R Joy y
	11 L Joy x
	12 L Joy y
	*/


class PS2Controller{
	private:
	uint8_t pins[12];
	//uint8_t pinsin[12];
	uint8_t data[13];
	public:	
	void writeTriangle(uint8_t val); //using normal int here for ease of use for other programmers.
	void writeCircle(uint8_t val);
	void writeX(uint8_t val);
	void writeSquare(uint8_t val);
	void writeStart(uint8_t val);
	void writeR1(uint8_t val);
	void writeL1(uint8_t val);
	void writeRJoy(uint8_t val, uint8_t val2);
	void writeLJoy(uint8_t val, uint8_t val2);
	void writeSHDN(uint8_t val); //Must write here twice in order to set new latch values
	PS2Controller(); //Constructor 1: sets pins to a sequential standard according to arduino uno. Will use analog pins as digital
	//PS2Controller(controller_pins); //Constructor 2: uses custom pin settings
	void setPins(uint8_t pinvals[10]);
	void sendData(uint8_t data[11]); //used to communicate current frame of data to PCB
	void sendData2(uint8_t data[11]);
	void writeDigiPot(uint8_t addr, uint8_t data);
	void writeR3(uint8_t val);
	void writeL3(uint8_t val);
	uint8_t scaleMouseData(uint8_t m_data);
};
