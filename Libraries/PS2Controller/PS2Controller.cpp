#include "PS2Controller.h"


PS2Controller::PS2Controller(void)
{
	//set default values, has no shoudler button use
	for(int i = 0; i < 9; i++)
	{
		pins[i] = i + 2;
	}

}

void setPins(uint8_t p[])
{
	//sets based on user code.
	pins = p;
}

void sendData(uint8_t data[])
{
	writeX(data[0]);
	writeCircle(data[1]);
	writeTriangle(data[2]);
	writeStart(data[3]);
	writeR1(data[4]);
	writeL1(data[5]);
	writeRJoy(data[6], data[7]);
	writeLJoy(data[8], data[9]);
}

void sendData(uint8_t[] data)
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

void writeX(uint8_t val)
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

void writeCircle(uint8_t val)
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

void writeTriangle(uint8_t val)
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

void writeStart(uint8_t val)
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

void writeR1(uint8_t val)
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

void writeL1(uint8_t val)
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

void writeRJoy(uint8_t val, uint8_t val2)
{
	digitalWrite(pins[8], LOW);
	
	for(int i = 0; i < 2; i++)
	{
		uint8_t mask = 1;
		
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
					
					mask << 1; //shuffle the bitmask to the left
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
					digitalWrite(pins[6], LOW);
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
					
					mask << 1; //shuffle the bitmask to the left
				}
				
				//delay(25); //Give the signal a moment to travel
			}
		}
		
		
		digitalWrite(pins[8], HIGH);
		delay(25); //put a defined space between bytes
	}
}

void writeLJoy(uint8_t val, uint8_t val2)
{
	digitalWrite(pins[8], LOW);
	
	for(int i = 0; i < 2; i++)
	{
		uint8_t mask = 1;
		
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
					digitalWrite(pins[6], HIGH);
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
					
					mask << 1; //shuffle the bitmask to the left
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
					
					mask << 1; //shuffle the bitmask to the left
				}
				
				//delay(25); //Give the signal a moment to travel
			}
		}
		
		
		digitalWrite(pins[8], HIGH);
		delay(25); //put a defined space between bytes of data
	}
}