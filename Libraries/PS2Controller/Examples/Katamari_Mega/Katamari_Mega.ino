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
#define X_o 2
#define Circle_o 3
#define Square_o 4
#define Triangle_o 5
#define R1_o 6
#define L1_o 7
#define R3_o 8
#define L3_o 9
#define Start_o 10
#define SDI 51
#define SCK 52
#define CS 49
#define LED_R 40
#define LED_G 41
#define LED_B 42

// INPUT Pin Definition
#define SCLK_R 43 //actually output to mouse 1
#define SDIO_R 44 //input/output from mouse 1
#define SCLK_L 45 //output to mouse 2
#define SDIO_L 46 //input/output from mouse 2
#define X 22
#define circle 23
#define square_p 24
#define triangle 25
#define start 26
#define r1 27
#define l1 28
#define r3 29
#define l3 30
#define game_mode 31

// Joystick modes
#define mode_main_menu 0
#define mode_norm_menu 1
#define mode_game 2

PS2Controller control = PS2Controller();

uint8_t data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
int joy_data[] = {0,0,0,0};
int mode = 0;

uint8_t i = 0;
int k = 0;

//mouse objects
ADNS2051 right_joy = ADNS2051(SCLK_R, SDIO_R);
ADNS2051 left_joy = ADNS2051(SCLK_L, SDIO_L);

void setup()
{
  /* OUTPUT PINS */
  pinMode(X_o, OUTPUT); //x
  pinMode(Circle_o, OUTPUT); //circle
  pinMode(Square_o, OUTPUT); //square
  pinMode(Triangle_o, OUTPUT); //triangle
  pinMode(Start_o, OUTPUT); //start
  pinMode(R1_o, OUTPUT); //r1
  pinMode(L1_o, OUTPUT); //l1
  pinMode(R3_o, OUTPUT); //R3
  pinMode(L3_o, OUTPUT); //L3
  pinMode(SDI, OUTPUT); //sdi
  pinMode(SCK, OUTPUT); //clk
  pinMode(CS, OUTPUT); //cs
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
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
  pinMode(game_mode, INPUT); //switch joystick modes.



  //OUTPUT to controller declaration
  uint8_t pins[] = {X_o,Circle_o,Square_o,Triangle_o,Start_o,R1_o,L1_o,R3_o,L3_o,SDI,SCK,CS}; //create an array for the pin numbers
  
  control.setPins(pins); //pass the pin numbers to the object
  
  //Start mouse objects
  right_joy.begin();
  left_joy.begin();
} 

void loop()
{
  //first check the joystick mode
  checkGameMode();
  
  //next get all of the data for the buttons and joysticks
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
  
  //format the data and prep for sending
  getJoystickData(getRJoyPosX(), getRJoyPosY());
  
  data[9] = joy_data[0];
  data[10] = joy_data[1];
  data[11] = joy_data[2];
  data[12] = joy_data[3];

  

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
  xVal = control.scaleMouseData(xVal);
  
  return xVal;
}

uint8_t getRJoyPosY()
{
  uint8_t yVal = right_joy.dy();
  
  //rescale the number to fit joystick expectation
  yVal = control.scaleMouseData(yVal);
  
  return yVal;
}

//get the positioning for the right joystick
uint8_t getLJoyPosX()
{
  uint8_t xVal = left_joy.dx();
  
  //rescale the number to fit the joystick expectation
  xVal = control.scaleMouseData(xVal);
  
  return xVal;
}

uint8_t getLJoyPosY()
{
  uint8_t yVal = left_joy.dy();
  
  //rescale the number to fit joystick expectation
  yVal = control.scaleMouseData(yVal);
  
  return yVal;
}

void checkModeButton()
{
  int t = digitalRead(game_mode);
  if(t == HIGH)
  {
    rotateMode();
  }
}

void rotateMode()
{
  if(mode == mode_main_menu)
  {
    mode = mode_norm_menu;
    setLED(1);
  }
  else if(mode == mode_norm_menu)
  {
    mode = mode_game;
    setLED(2);
  }
  else
  {
    mode = mode_main_menu;
    setLED(0);
  }
}

void setLED(int c)
{
  /* Color Legend
  0 - Red, Main Menu (file loading screen controls)
  1 - Blue, All other menus
  2 - Green, Play mode
  */
  if(c == 0)
  {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
  }
  else if(c == 1)
  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
  } 
  else if(c == 2)
  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
  }
}

void getJoystickData(int joy_x, int joy_y)
{
  
  if(mode == 0) //Main menu
  {
    joy_data[0] = joy_x;
    joy_data[2] = joy_x;
    joy_data[1] = joy_y;
    joy_data[3] = joy_y;
  }
  else if(mode == 1)//in game menus
  {
    joy_data[0] = 127;
    joy_data[1] = 127;
    joy_data[2] = joy_x;
    joy_data[3] = joy_y;
  }
  else //in game
  {
    joy_data[0] = 127;
    joy_data[2] = 127;
    
    if(joy_x < 127)
    {
      if(joy_y > 127)
      {
        joy_data[1] = 255;
        joy_data[3] = 255 - (127 - joy_x);
      }
      else if(joy_y < 127)
      {
        joy_data[1] = 0;
        joy_data[3] = 127 - joy_x;
      }
      else
      {
        joy_data[1] = 127;
        joy_data[3] = 127 - joy_x;
      }
    }
    else if(joy_x > 127)
    {
      if(joy_y > 127)
      {
        joy_data[3] = 255;
        joy_data[1] = 255 - (joy_x - 127);
      }
      else if(joy_y < 127)
      {
        joy_data[3] = 0;
        joy_data[1] = 0 + (joy_x - 127);
      }
      else
      {
        joy_data[3] = 127;
        joy_data[1] = 127 - (joy_x - 127);
      }
    }
    else
    {
      if(joy_y > 127)
      {
        joy_data[1] = 255;
        joy_data[3] = 255;
      }
      else if(joy_y < 127)
      {
        joy_data[1] = 0;
        joy_data[3] = 0;
      }
      else
      {
        joy_data[1] = 127;
        joy_data[3] = 127;
      }
    }
  }
  
  return joy_data;
}
      
     
  
