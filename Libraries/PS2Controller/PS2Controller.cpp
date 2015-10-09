#include "PS2Controller.h"

uint8_t pinsin[9];

PS2Controller::PS2Controller(void)
{
	//set default values, has no shoudler button use
	for(int i = 0; i < 9; i++)
	{
		pins[i] = i + 2;
	}

}

void PS2Controller::setPins(uint8_t pins[])
{
	//sets based on user code.
	for(int i = 0; i < 9; i++)
	{
		pinsin[i] = pins[i];
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

/* IMPORTANT NOTE */
/* The digital pot expects the address and data MSB -> LSB */ 
void PS2Controller::writeRJoy(uint8_t val, uint8_t val2)
{	
	for(int i = 0; i < 2; i++)
	{
		uint8_t mask = 1;
		mask << 7; //shift to MSB to start
		
		//set chip select low to write to serial register
		digitalWrite(pins[9], LOW);
		
		if(i == 0) //Write X axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					//write high on clock for signal to settle
					digitalWrite(pins[8], HIGH);
				}
				
				if(j == 0)
				{
					//write clock low and then MSB of RDAC address
					digitalWrite(pins[8], LOW);
					digitalWrite(pins[7], LOW);
				}
				
				if(j == 2)
				{
					//write clock low and the LSB of RDAC address
					digitalWrite(pins[8], LOW);
					digitalWrite(pins[7], LOW);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					//write clock low and current bit of data word
					digitalWrite(pins[8], LOW);
					if(val & mask) //if the data byte is on at the same point as the mask
					{
						digitalWrite(pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins[6], LOW);
					}
					
					mask >> 1; //shuffle the bitmask to the right
				}
			}
		}
		
		if(i == 1) //Write Y axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					//write clock high to let the signal settle
					digitalWrite(pins[8], HIGH);
				}
				
				if(j == 0)
				{
					//write clock low and MSB of RDAC address
					digitalWrite(pins[8], LOW);
					digitalWrite(pins[7], LOW);
				}
				
				if(j == 2)
				{
					//write clock low and LSB of RDAC address
					digitalWrite(pins[8], LOW);
					digitalWrite(pins[7], HIGH);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					//write clock low and current bit of data word
					digitalWrite(pins[8], LOW);
					if(val2 & mask) //if the byte mask and data byte are on at the same bit
					{
						digitalWrite(pins[7], HIGH);
					}
					else
					{
						digitalWrite(pins[7], LOW);
					}
					
					mask >> 1; //shuffle the bitmask to the right
				}
			}
		}
		
		//write high on chip select so that the data will be read from the register to the latch
		digitalWrite(pins[8], HIGH);
		delay(5); //put a defined space between bytes
	}
}

/* IMPORTANT NOTE */
/* The digital pot expects the address and data MSB -> LSB */ 
void PS2Controller::writeLJoy(uint8_t val, uint8_t val2)
{	
	for(int i = 0; i < 2; i++)
	{
		uint8_t mask = 1; //create bit mask
		mask << 7; //shift to MSB to start
		
		//write chip select low to enable writing to internal register
		digitalWrite(pins[8], LOW);
		
		if(i == 0) //Write X axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					//write clock high to allow signal settling
					digitalWrite(pins[8], HIGH);
				}
				
				if(j == 0)
				{
					//write clock low and MSB of RDAC address
					digitalWrite(pins[8], LOW);
					digitalWrite(pins[7], HIGH);
				}
				
				if(j == 2)
				{
					//write clock low and LSB of RDAC address
					digitalWrite(pins[8], LOW);
					digitalWrite(pins[7], LOW);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					//write clock low and the current bit of the current data word
					digitalWrite(pins[8], LOW);
					if(val & mask)
					{
						digitalWrite(pins[7], HIGH);
					}
					else
					{
						digitalWrite(pins[7], LOW);
					}
					
					mask >> 1; //shuffle the bitmask to the right
				}
			}
		}
		
		if(i == 1) //Write Y axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					//write clock high to allow for the signal to settle
					digitalWrite(pins[8], HIGH);
				}
				
				if(j == 0)
				{
					//write clock low and MSB of RDAC address
					digitalWrite(pins[8], LOW);
					digitalWrite(pins[7], HIGH);
				}
				
				if(j == 2)
				{
					//write clock low and thw LSB of RDAC address
					digitalWrite(pins[8], LOW);
					digitalWrite(pins[7], HIGH);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					//write clock low and the current bit of data word
					digitalWrite(pins[8], LOW);
					if(val2 & mask)
					{
						digitalWrite(pins[7], HIGH);
					}
					else
					{
						digitalWrite(pins[7], LOW);
					}
					
					mask >> 1; //shuffle the bitmask to the right
				}
			}
		}
		
		//write high on chip select to allow for decoding of the data
		digitalWrite(pins[9], HIGH);
		delay(1); //put a space between bytes of data
	}
}
	
void PS2Controller::writeSHDN(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins[10], HIGH);	
	}
	else
	{
		digitalWrite(pins[10], LOW);
	}
}
