#include "PS2Controller.h"


PS2Controller::PS2Controller(void)
{
	//set default values, has no shoudler button use
	for(int i = 0; i < 9; i++)
	{
		pins.pins[i] = i + 2;
	}

}

void setPins(uint8_t[] p)
{
	//sets based on user code.
	pins = p;
}

void sendData(c_data data)
{
	writeX(data.data[0]);
	writeCircle(data.data[1]);
	writeTriangle(data.data[2]);
	writeStart(data.data[3]);
	writeR1(data.data[4]);
	writeL1(data.data[5]);
	writeRJoy(data.data[6], data.data[7]);
	writeLJoy(data.data[8], data.data[9]);
}

void sendData(uint8_t[] data)
{
	writeX(data[0]);
	writeCircle(data[1]);
	writeTriangle(data[2]);
	writeStart(data[3]);
	writeR1(data[4]);
	writeL1(data[5]);
	writeRJoy(data[6], data.data[7]);
	writeRJoy(data[8], data.data[9]);
}

void writeX(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins.pins[0], HIGH);
	}
	else
	{
		digitalWrite(pins.pins[0], LOW);
	}
}

void writeCircle(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins.pins[1], HIGH);
	}
	else
	{
		digitalWrite(pins.pins[1], LOW);
	}
}

void writeTriangle(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins.pins[2], HIGH);
	}
	else
	{
		digitalWrite(pins.pins[2], LOW);
	}
}

void writeStart(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins.pins[3], HIGH);
	}
	else
	{
		digitalWrite(pins.pins[3], LOW);
	}
}

void writeR1(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins.pins[4], HIGH);
	}
	else
	{
		digitalWrite(pins.pins[4], LOW);
	}
}

void writeL1(uint8_t val)
{
	if(val == 1)
	{
		digitalWrite(pins.pins[5], HIGH);
	}
	else
	{
		digitalWrite(pins.pins[5], LOW);
	}
}

void writeRJoy(uint8_t val, uint8_t val2)
{
	digitalWrite(pins.pins[8], LOW);
	
	for(int i = 0; i < 2; i++)
	{
		uint8_t mask = 1;
		
		digitalWrite(pins.pins[8], LOW);
		
		if(i == 0) //Write X axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					digitalWrite(pins.pins[7], HIGH);
				}
				
				if(j == 0)
				{
					digitalWrite(pins.pins[7], LOW);
					digitalWrite(pins.pins[6], LOW);
				}
				
				if(j == 2)
				{
					digitalWrite(pins.pins[7], LOW);
					digitalWrite(pins.pins[6], LOW);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					digitalWrite(pins.pins[7], LOW);
					if(val & mask)
					{
						digitalWrite(pins.pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins.pins[6], LOW);
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
					digitalWrite(pins.pins[7], HIGH);
				}
				
				if(j == 0)
				{
					digitalWrite(pins.pins[7], LOW);
					digitalWrite(pins.pins[6], HIGH);
				}
				
				if(j == 2)
				{
					digitalWrite(pins.pins[7], LOW);
					digitalWrite(pins.pins[6], LOW);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					digitalWrite(pins.pins[7], LOW);
					if(val2 & mask)
					{
						digitalWrite(pins.pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins.pins[6], LOW);
					}
					
					mask << 1; //shuffle the bitmask to the left
				}
				
				//delay(25); //Give the signal a moment to travel
			}
		}
		
		
		digitalWrite(pins.pins[8], HIGH);
		delay(25); //put a defined space between bytes
	}
}

void writeLJoy(uint8_t val, uint8_t val2)
{
	digitalWrite(pins.pins[8], LOW);
	
	for(int i = 0; i < 2; i++)
	{
		uint8_t mask = 1;
		
		digitalWrite(pins.pins[8], LOW);
		
		if(i == 0) //Write X axis
		{
			for(int j = 0; j < 20; j++)
			{
				if(j % 2 != 0)
				{
					digitalWrite(pins.pins[7], HIGH);
				}
				
				if(j == 0)
				{
					digitalWrite(pins.pins[7], LOW);
					digitalWrite(pins.pins[6], LOW);
				}
				
				if(j == 2)
				{
					digitalWrite(pins.pins[7], LOW);
					digitalWrite(pins.pins[6], HIGH);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					digitalWrite(pins.pins[7], LOW);
					if(val & mask)
					{
						digitalWrite(pins.pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins.pins[6], LOW);
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
					digitalWrite(pins.pins[7], HIGH);
				}
				
				if(j == 0)
				{
					digitalWrite(pins.pins[7], LOW);
					digitalWrite(pins.pins[6], HIGH);
				}
				
				if(j == 2)
				{
					digitalWrite(pins.pins[7], LOW);
					digitalWrite(pins.pins[6], HIGH);
				}
				
				if(j % 2 == 0 && i > 3)
				{
					digitalWrite(pins.pins[7], LOW);
					if(val2 & mask)
					{
						digitalWrite(pins.pins[6], HIGH);
					}
					else
					{
						digitalWrite(pins.pins[6], LOW);
					}
					
					mask << 1; //shuffle the bitmask to the left
				}
				
				//delay(25); //Give the signal a moment to travel
			}
		}
		
		
		digitalWrite(pins.pins[8], HIGH);
		delay(25); //put a defined space between bytes of data
	}
}