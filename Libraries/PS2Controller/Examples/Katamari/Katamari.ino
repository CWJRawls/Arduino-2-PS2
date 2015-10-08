#include <PS2Controller.h> //library import
#include <inttypes.h>
/* Pin numbers

2 - x
3 - o
4 - square
5 - triangle
6 - start
7 - r1
8 - l1
9 - SDI
10 - Clk
11 - CS
*/

/* Data index
x - 0
o - 1
square - 2
triangle - 3
start - 4
r1 - 5
l1 - 6
r joy x - 7
r joy y - 8
l joy x - 9
l joy y - 10
*/

PS2Controller control = PS2Controller();

uint8_t data[] = {0,0,0,0,0,0,0,0,0,0,0};

uint8_t i = 0;
int k = 0;

void setup()
{
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
  
  uint8_t pins[] = {2,3,4,5,6,7,8,11,10,9}; //create an array for the pin numbers
  
  control.setPins(pins); //pass the pin numbers to the object
  
} 

void loop()
{
  
  if(i > 250)
  {
    i = 0;
  }
  
  if(k < 255)
  {
    data[7] = i;
    data[9] = i;
  }
  else if(k < 500)
  {
    data[8] = i;
    data[10] = i;
  }
  
  i++;
  k++;
  
  control.sendData(data);
  
  delay(100);
}
