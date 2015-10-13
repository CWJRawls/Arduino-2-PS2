#include "PS2Controller.h"

uint8_t pinsin[9];

PS2Controller::PS2Controller(void)
{
	//set default values, has no shoudler button use
	for(int i = 0; i < 9; i++)
	{
		pins[i] = i + 2;
	}
	
	SPI.begin();

}

void PS2Controller::setPins(uint8_t pinvals[])
{
	//sets based on user code.
	for(int i = 0; i < 12; i++)
	{
		pins[i] = pinvals[i];
	}
}

void PS2Controller::sendData(uint8_t data[])
{
	writeX(data[0]);
	writeCircle(data[1]);
	writeSquare(data[2]);
	writeTriangle(data[3]);
	writeStart(data[4]);
	writeR1(data[5]);
	writeL1(data[6]);
	writeR3(data[7]);
	writeL3(data[8]);
	//writeSHDN(0);
	writeRJoy(data[9], data[10]);
	writeRJoy(data[11], data[12]);
	//writeSHDN(1);
}

void PS2Controller::sendData2(uint8_t data[])
{
	writeX(data[0]);
	writeCircle(data[1]);
	writeSquare(data[2]);
	writeTriangle(data[3]);
	writeStart(data[4]);
	writeR1(data[5]);
	writeL1(data[6]);
	writeSHDN(0);
	writeRJoy(data[7], data[8]);
	writeRJoy(data[9], data[10]);
	writeSHDN(1);
}

void PS2Controller::writeX(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[0], HIGH);
	}
	else
	{
		digitalWrite(pins[0], LOW);
	}
}

void PS2Controller::writeCircle(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[1], HIGH);
	}
	else
	{
		digitalWrite(pins[1], LOW);
	}
}

void PS2Controller::writeTriangle(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[3], HIGH);
	}
	else
	{
		digitalWrite(pins[3], LOW);
	}
}

void PS2Controller::writeStart(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[4], HIGH);
	}
	else
	{
		digitalWrite(pins[4], LOW);
	}
}

void PS2Controller::writeR1(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[5], HIGH);
	}
	else
	{
		digitalWrite(pins[5], LOW);
	}
}

void PS2Controller::writeL1(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[6], HIGH);
	}
	else
	{
		digitalWrite(pins[6], LOW);
	}
}

void PS2Controller::writeSquare(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[2], HIGH);
	}
	else
	{
		digitalWrite(pins[2], LOW);
	}
}

void PS2Controller::writeRJoy(uint8_t val, uint8_t val2)
{	
	writeDigiPot(0, val); //write the x values
	writeDigiPot(1, val2); //write the y values
}

void PS2Controller::writeLJoy(uint8_t val, uint8_t val2)
{	
	writeDigiPot(2, val); //write the x values
	writeDigiPot(3, val); //write the y values
}

void PS2Controller::writeDigiPot(uint8_t addr, uint8_t data)
{
	//write the chip select low
	digitalWrite(pins[11], LOW);
	
	SPI.transfer(addr);
	SPI.transfer(data);
	
	//write chip select high
	digitalWrite(pins[11], HIGH);
}
	
void PS2Controller::writeSHDN(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[11], HIGH);	
	}
	else
	{
		digitalWrite(pins[11], LOW);
	}
}

void PS2Controller::writeR3(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[7], HIGH);
	}
	else
	{
		digitalWrite(pins[7], LOW);
	}
}

void PS2Controller::writeL3(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[8], HIGH);
	}
	else
	{
		digitalWrite(pins[8], LOW);
	}
}
