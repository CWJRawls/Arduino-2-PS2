/* Holders for which pin is what */
int data_pin = 1; //output from controller (transmits controller status)
int command_pin = 2; //input from console (sends request for data) always read on leading edge of clock
int att_pin = 6; //input from console (asks for attention)
int clock_pin = 7; //input from console !CRUCIAL FOR TIMING!
int ack_pin = 9; //output from controller (Says I'm still paying attention)
/* PS2 considers a full byte as 8 bits of info */
/* These are all single bits of data */
/* All valueas are considered active low, init high to avoid false positives */
/* <Byte4> top value is lsb */
int slct = 1;
int r3 = 1;
int l3 = 1;
int strt = 1;
int up = 1;
int right = 1;
int down = 1;
int left = 1;
/* </Byte4> */
/* <Byte5> top value is lsb */
int l2 = 1;
int r2 = 1;
int l1 = 1;
int r1 = 1;
int tri = 1;
int circ = 1;
int x_but = 1;
int sqr = 1;
/* </Byte5> */
/* These are whole bytes of information 0 - 255 in decimal */
int but_byte_1 = 255; //Byte4
int but_byte_2 = 255; //Byte5
int right_joy_h = 127; //Byte6
int right_joy_v = 127; //Byte7
int left_joy_h = 127; //Byte8
int left_joy_v = 127; //Byte9
int send_command = 66; //incoming on byte 2
int controllerID = 115; //byte2
int data_out_flag = 90; //byte 3 

//Pin values <always init high>
int data_val = 1;
int ack_val = 1;
int clock_val = 1;
byte byte_mask = 00000001;
int data_send = 0;
int ack_send = 0;
unsigned long last_clock_fall = 0;
unsigned long current_micros = 0;
int bit_count = 0;
int in_bit_count = 0;
int att_val = 0;
int command_val = 2;
int last_clock = 1;
int command_byte = 0;
int clock_seq = 2; /* 0 = falling edge 1 = leading edge 2 = no change */
int byte_seq = 0; /* used for determining which byte we are at
0 - waiting for console
1 - Controller attention
2 - Controller id out
3 - Controller start dump out
4 - button set 1
5 - button set 2
6 - right stick h
7 - right stck v
8 - left stick h
9 - left stick v
*/
//Control scheme for logic control
int control_step = 0; 
/*
Step vals:
0 - waiting for psx to pull low on att
1 - Preamble step 1 (wait for start command (1) on command pin (then pull low on ack)
2 - reply with controller id
3 - reply with data flow start (then ack)
4 - byte 4 transmission (then ack)
5 - byte 5 transmission (then ack)
6 - right joystick horizontal then ack
7 - right joystick vertical then ack
8 - left joystick horizontal then ack
9 - left joystick vertical no ack
*/



void setup()
{
  pinMode(data_pin, OUTPUT);
  pinMode(ack_pin, OUTPUT);
  pinMode(clock_pin, INPUT);
  pinMode(att_pin, INPUT);
  pinMode(command_pin, INPUT);
}

void loop()
{
  //First step check current input from controller interface
  getClock();
  checkConsolePins();
  determineClockChange();
  //Next check current position in control sequence
  
  //Compute logic for control sequence
  checkAck();
  
  //send data out on pins
  sendData();
}

void sendData()
{
  if(data_send == 1)
  {
    if(data_val == 1)
    {
      digitalWrite(data_pin, HIGH);
    }
    else
    {
      digitalWrite(data_pin, LOW);
    }
    data_send = 0;
  }
  
  if(ack_send == 1)
  {
    if(ack_val == 1)
    {  
      digitalWrite(ack_pin, HIGH);
    }
    else
    {
      digitalWrite(ack_pin, LOW);
    }
    ack_send = 0;
  }
}

void getClock()
{
  last_clock = clock_val;
  clock_val = digitalRead(clock_pin);
}

void setNextDataOut(byte data)
{
  //reset the bit count at the start of the next byte
  if(bit_count == 8)
  {
    bit_count = 0;
  }
  
  //If we are in the middle of a byte
  if(byte_mask > 0)
  {
    if(byte_mask & data)
    {
      data_val = 1;
    }
    else
    {
      data_val = 0;
    }
    
    byte_mask <<= 1;
    bit_count++;
  }
  else //if we are at the beginning of a byte
  {
    byte_mask = 00000001;
    
    if(byte_mask & data)
    {
      data_val = 1;
    }
    else
    {
      data_val = 0;
    }
    byte_mask <<= 1;
    bit_count++;
  }
}

/* Determine if we need to pull low on ack and do so */
void checkAck()
{
  if(control_step > 0 && control_step < 9 && (bit_count == 8 || in_bit_count == 8))
  {
    current_micros = micros();
    unsigned long distance = current_micros - last_clock_fall;
    if(distance > 10 && distance < 50)
    {
      ack_send = 1;
      ack_val = 0;
    }
    
    if(distance > 75)
    {
      ack_send = 1;
      ack_val = 1;
    }
  }
}



void checkConsolePins()
{
  att_val = digitalRead(att_pin); //we don't check the clock pin here since this is not beholden to being synced.
  
  if(clock_val == 1 && last_clock == 0)
  {
    command_val = digitalRead(command_pin);
  }
}

void determineClockChange()
{
  if(clock_val == last_clock)
  {
    clock_seq = 2;
  }
  else if(clock_val < last_clock)
  {
    clock_seq = 0;
  }
  else
  {
    clock_seq = 1;
  }
}

/* Logic for advancing through the control sequence for console communication */
void checkControlStep()
{
  /* Logic for advancing through steps */
  if(control_step == 0 && att_val == 0)
  {
    control_step = 1;
    command_byte = 0;
    in_bit_count == 0;
  }
  else if(control_step == 1 && ack_val == 1 && ack_send == 1)
  {
    control_step = 2;
    command_byte = 0;
    in_bit_count == 0;
  }
  else if(control_step == 2 && ack_val == 1 && ack_send == 1)
  {
    control_step = 3;
  }
  else if(control_step == 3 && ack_val == 1 && ack_send == 1)
  {
    control_step = 4;
    assembleButtonByte1();
  }
  else if(control_step == 4 && ack_val == 1 && ack_send == 1)
  {
    control_step = 5;
    assembleButtonByte2();
  }
  else if(control_step == 5 && ack_val == 1 && ack_send == 1)
  {
    control_step = 6;
  }
  else if(control_step == 6 && ack_val == 1 && ack_send == 1)
  {
    control_step = 7;
  }
  else if(control_step == 7 && ack_val == 1 && ack_send == 1)
  {
    control_step = 8;
  }
  else if(control_step == 8 && ack_val == 1 && ack_send == 1)
  {
    control_step = 9;
  }
  else if(control_step == 9 && bit_count == 8)
  {
    control_step = 0;
  }
  
  /* Logic by point in the step */
  
  //Step 0 - Reserve this step to take in data
  
  //Step 1 - read from the console for the attention command followed by 0x01 on command line
 if(control_step == 1)
 {
  if(att_val == 0)//if the console has pulled low
  {
    if(clock_seq == 1)//if we are at the leading edge of the clock
    {
      command_byte += command_val * pow(2, in_bit_count); //So far reading data for funzies
      in_bit_count++;
      //no need to woory about pulling on the ack pin here, another function takes care of that
    }
  }
 }
 
 if(control_step == 2)
 {
   if(clock_seq == 0) //if we are on the falling edge of the clock
   {
     setNextDataOut(controllerID); //only output a bit on the falling edge.
     data_send = 1; //make sure to flag data for release over the pins.
     //again, no need to pull ack here, that is already taken care of
   }
 }
 
if(control_step == 3)
{
  if(clock_seq == 0)
  {
     setNextDataOut(data_out_flag);
     data_send = 1;
  }
}

if(control_step == 4)
{
  if(clock_seq == 0)
  {
    setNextDataOut(but_byte_1);
    data_send = 1;
  }
}

if(control_step == 5)
{
  if(clock_seq == 0)
  {
    setNextDataOut(but_byte_2);
    data_send = 1;
  }
}

if(control_step == 6)
{
  if(clock_seq == 0)
  {
    setNextDataOut(right_joy_h);
    data_send = 1;
  }
}

if(control_step == 7)
{
  if(clock_seq == 0)
  {
    setNextDataOut(right_joy_v);
    data_send = 1;
  }
}

if(control_step == 8)
{
  if(clock_seq == 0)
  {
    setNextDataOut(left_joy_h);
    data_send = 1;
  }
}

if(control_step == 9)
{
  if(clock_seq == 0)
  {
    setNextDataOut(left_joy_v);
    data_send = 1;
  }
}  
}

void assembleButtonByte1()
{
  but_byte_1 = (1 * slct) + (2 * r3) + (4 * l3) + (8 * strt) + (16 * up) + (32 * right) + (64 * down) + (128 * left);
}

void assembleButtonByte2()
{
  but_byte_2 = (1 * l2) + (2 * r2) + (4 * l1) + (8 * r1) + (16 * tri) + (32 * circ) + (64 * x_but) + (128 * sqr);
}
