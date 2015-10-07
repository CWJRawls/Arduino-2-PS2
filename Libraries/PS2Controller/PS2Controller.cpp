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
	writeTriangle(data[2]);
	writeStart(data[3]);
	writeR1(data[4]);
	writeL1(data[5]);
	writeRJoy(data[6], data[7]);
	writeRJoy(data[8], data[9]);
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
		digitalWrite(pins[2], HIGH);
	}
	else
	{
		digitalWrite(pins[2], LOW);
	}
}

void PS2Controller::writeStart(uint8_t val)
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

void PS2Controller::writeR1(uint8_t val)
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

void PS2Controller::writeL1(uint8_t val)
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

/* IMPORTANT NOTE */
/* The digital pot expects the address and data MSB -> LSB */ 
void PS2Controller::writeRJoy(uint8_t val, uint8_t val2)
{
	digitalWrite(pins[8], LOW);
	
	for(int i = 0; i < 2; i++)
	{
		uint8_t mask = 1;
		mask << 7; //shift to MSB to start
		
		digitalWrite(pins[8], LOW);
		
		if(i == 0) //Write X axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					digitalWrite(pins[7], HIGH);
				}
				
				if(j == 0)
				{
					digitalWrite(pins[7], LOW);
					digitalWrite(pins[6], LOW);
				}
				
				if(j == 2)
				{
					digitalWrite(pins[7], LOW);
					digitalWrite(pins[6], LOW);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					digitalWrite(pins[7], LOW);
					if(val & mask)
					{
						digitalWrite(pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins[6], LOW);
					}
					
					mask >> 1; //shuffle the bitmask to the right
				}
				
				//delay(25); //Give the signal a moment to travel
			}
		}
		
		if(i == 1) //Write Y axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					digitalWrite(pins[7], HIGH);
				}
				
				if(j == 0)
				{
					digitalWrite(pins[7], LOW);
					digitalWrite(pins[6], LOW);
				}
				
				if(j == 2)
				{
					digitalWrite(pins[7], LOW);
					digitalWrite(pins[6], HIGH);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					digitalWrite(pins[7], LOW);
					if(val2 & mask)
					{
						digitalWrite(pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins[6], LOW);
					}
					
					mask >> 1; //shuffle the bitmask to the right
				}
				
				//delay(25); //Give the signal a moment to travel
			}
		}
		
		
		digitalWrite(pins[8], HIGH);
		delay(1); //put a defined space between bytes
	}
}

/* IMPORTANT NOTE */
/* The digital pot expects the address and data MSB -> LSB */ 
void PS2Controller::writeLJoy(uint8_t val, uint8_t val2)
{
	digitalWrite(pins[8], LOW);
	
	for(int i = 0; i < 2; i++)
	{
		uint8_t mask = 1;
		mask << 7;
		
		digitalWrite(pins[8], LOW);
		
		if(i == 0) //Write X axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					digitalWrite(pins[7], HIGH);
				}
				
				if(j == 0)
				{
					digitalWrite(pins[7], LOW);
					digitalWrite(pins[6], HIGH);
				}
				
				if(j == 2)
				{
					digitalWrite(pins[7], LOW);
					digitalWrite(pins[6], LOW);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					digitalWrite(pins[7], LOW);
					if(val & mask)
					{
						digitalWrite(pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins[6], LOW);
					}
					
					mask >> 1; //shuffle the bitmask to the right
				}
				
				//delay(25); //Give the signal a moment to travel
			}
		}
		
		if(i == 1) //Write Y axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					digitalWrite(pins[7], HIGH);
				}
				
				if(j == 0)
				{
					digitalWrite(pins[7], LOW);
					digitalWrite(pins[6], HIGH);
				}
				
				if(j == 2)
				{
					digitalWrite(pins[7], LOW);
					digitalWrite(pins[6], HIGH);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					digitalWrite(pins[7], LOW);
					if(val2 & mask)
					{
						digitalWrite(pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins[6], LOW);
					}
					
					mask >> 1; //shuffle the bitmask to the right
				}
				
				//delay(25); //Give the signal a moment to travel
			}
		}
		
		
		digitalWrite(pins[8], HIGH);
		delay(1); //put a space between bytes of data
	}
}