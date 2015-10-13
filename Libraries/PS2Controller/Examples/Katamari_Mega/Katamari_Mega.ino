#include <PS2Controller.h> //library import
#include <inttypes.h> //used to gain access 8-bit unsigned integer type
#include <ADNS2051.h> //import for the mouse object
//SPI Library included in C++ library
/* PURPOSE
This sketch is a demo sketch meant to test the PS2Controller library for the
PS2 game Katamari Damacy. The data streams are meant to work with the buttons
and joysticks needed for game operation. The joystick data is being supplied
by a 4-channel digipot chip (AD8403 10k ohms version). */

/* NOTE
This sketch assumes that you are using the arduino mega board. Otherwise you
will not have enough pins to accomodate all of the controls. */

/* Pin numbers
2 - x
3 - o
4 - square
5 - triangle
6 - start
7 - r1
8 - l1
9 - R3
12 - L3
10 - Chip Select
11 - MOSI
13 - CLK
*/

/* Data index
x - 0
o - 1
square - 2
triangle - 3
start - 4
r1 - 5
l1 - 6
r3 - 7
l3 - 8
r joy x - 9
r joy y - 10
l joy x - 11
l joy y - 12
*/

//OUTPUT Pin Definition


// INPUT Pin Definition
#define SCLK_R 51
#define SDIO_R 52
#define SCLK_L 53
#define SDIO_L 54
#define X 22
#define circle 23
#define square_p 24
#define triangle 25
#define start 26
#define r1 27
#define l1 28
#define r3 29
#define l3 30



PS2Controller control = PS2Controller();

uint8_t data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

uint8_t i = 0;
int k = 0;

//mouse objects
ADNS2051 right_joy = ADNS2051(SCLK_R, SDIO_R);
ADNS2051 left_joy = ADNS2051(SCLK_L, SDIO_L);

void setup()
{
  /* OUTPUT PINS */
  pinMode(2, OUTPUT); //x
  pinMode(3, OUTPUT); //circle
  pinMode(4, OUTPUT); //square
  pinMode(5, OUTPUT); //triangle
  pinMode(6, OUTPUT); //start
  pinMode(7, OUTPUT); //r1
  pinMode(8, OUTPUT); //l1
  pinMode(9, OUTPUT); //cs
  pinMode(10, OUTPUT); //clk
  pinMode(11, OUTPUT); //sdi
  pinMode(12, OUTPUT); //SHDN
  
  /* INPUT PINS */
  //buttons
  pinMode(X, INPUT); //x
  pinMode(circle, INPUT); //circle
  pinMode(square_p, INPUT); //square
  pinMode(triangle, INPUT); //triangle
  pinMode(start, INPUT); //start
  pinMode(r1, INPUT); //r1
  pinMode(l1, INPUT); //l1
  pinMode(r3, INPUT); //r3
  pinMode(l3, INPUT); //l3



  //OUTPUT to controller declaration
  uint8_t pins[] = {2,3,4,5,6,7,8,11,13,10,9}; //create an array for the pin numbers
  
  control.setPins(pins); //pass the pin numbers to the object
  
  //Start mouse objects
  right_joy.begin();
  left_joy.begin();
} 

void loop()
{
  
  //first get all of the data for the buttons and joysticks
  if(getX())
  {
    data[0] = 1;
  }
  else
  {
    data[0] = 0;
  }
  
  if(getCircle())
  {
    data[1] = 1;
  }
  else
  {
    data[1] = 0;
  }
  
  if(getSquare())
  {
    data[2] = 1;
  }
  else
  {
    data[2] = 0;
  }
  
  if(getTriangle())
  {
    data[3] = 1;
  }
  else
  {
    data[3] = 0;
  }
  
  if(getStart())
  {
    data[4] = 1;
  }
  else
  {
    data[4] = 0;
  }
  
  if(getR1())
  {
    data[5] = 1;
  }
  else
  {
    data[5] = 0;
  }
  
  if(getL1())
  {
    data[6] = 1;
  }
  else
  {
    data[6] = 0;
  }
  
  if(getR3())
  {
    data[7] = 1;
  }
  else
  {
    data[7] = 0;
  }
  
  if(getL3())
  {
    data[8] = 1;
  }
  else
  {
    data[8] = 0;
  }
  
  data[9] = getRJoyPosX();
  data[10] = getRJoyPosY();
  data[11] = getLJoyPosX();
  data[12] = getLJoyPosY();

  //send the data
  control.sendData(data);
  
  //wait a bit before starting over
  delay(10);
}

boolean getX()
{
  int t = digitalRead(X);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean getCircle()
{
  int t = digitalRead(circle);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}
  
boolean getSquare()
{
  int t = digitalRead(square_p);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean getTriangle()
{
  int t = digitalRead(triangle);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean getR1()
{
  int t = digitalRead(r1);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean getL1()
{
  int t = digitalRead(l1);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean getR3()
{
  int t = digitalRead(r3);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean getL3()
{
  int t = digitalRead(l3);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolena getStart()
{
  int t = digitalRead(start);
  if(t == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

//get the positioning for the right joystick
uint8_t getRJoyPosX()
{
  uint8_t xVal = right_joy.dx();
  
  //rescale the number to fit the joystick expectation
  if(xVal < 127)
  {
    xVal += 127;
  }
  else
  {
    xVal -= 127;
  }
  
  return xVal;
}

uint8_t getRJoyPosY()
{
  uint8_t yVal = right_joy.dy();
  
  //rescale the number to fit joystick expectation
  if(yVal < 127)
  {
    yVal += 127;
  }
  else
  {
    yVal -= 127;
  }
  
  return yVal;
}

//get the positioning for the right joystick
uint8_t getLJoyPosX()
{
  uint8_t xVal = left_joy.dx();
  
  //rescale the number to fit the joystick expectation
  if(xVal < 127)
  {
    xVal += 127;
  }
  else
  {
    xVal -= 127;
  }
  
  return xVal;
}

uint8_t getLJoyPosY()
{
  uint8_t yVal = left_joy.dy();
  
  //rescale the number to fit joystick expectation
  if(yVal < 127)
  {
    yVal += 127;
  }
  else
  {
    yVal -= 127;
  }
  
  return yVal;
}
