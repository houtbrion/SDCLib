#include <EEPROM.h>
#include <avr/pgmspace.h>
#include "SDC_TM1637.h"

#define CLK 4//pins definitions for TM1637 and can be changed to other ports
#define DIO 5

#define LED_BRIGHTNESS BRIGHT_DARKEST
//#define LED_BRIGHTNESS BRIGHT_TYPICAL
//#define LED_BRIGHTNESS BRIGHTEST

digit_led_state_t state;

SDC_TM1637 tm1637(CLK,DIO);

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char microsecond_10 = 0;
unsigned char second;
unsigned char _microsecond_10 = 0;
unsigned char _second;
unsigned int eepromaddr;
boolean Flag_ReadTime;

#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3

void setup()
{
  state.colon=false;
  Serial.begin(9600);
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");
  if (!tm1637.begin()) {
    Serial.println("setup n digit led failure.");
    while (true) {
      ;
    }
  }
  Timer1.initialize(10000);//timing for 10ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
  Serial.println("Please send command to control the stopwatch:");
  Serial.println("S - start");
  Serial.println("P - pause");
  Serial.println("L - list the time");
  Serial.println("W - write the time to EEPROM ");
  Serial.println("R - reset");
  state.brightness=LED_BRIGHTNESS;
  Serial.println("setup done.");
}
void loop()
{
  char command;
  command = Serial.read();
  switch(command)
  {
    case 'S':stopwatchStart();Serial.println("Start timing...");break;
    case 'P':stopwatchPause();Serial.println("Stopwatch was paused");break;
    case 'L':readTime();break;
    case 'W':saveTime();Serial.println("Save the time");break;
    case 'R':stopwatchReset();Serial.println("Stopwatch was reset");break;
    default:break;
  }
  if(Update == ON)
  {
    Serial.println("update time.");
    TimeUpdate();
    tm1637.SetState(&state);
  }
}
//************************************************
void TimingISR()
{
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second ++;
    if(second == 60)
    {
      second = 0;
    }
    microsecond_10 = 0;
  }
  if (state.colon) {
    state.colon=false;
  } else {
    state.colon=true;
  }
  if(Flag_ReadTime == 0)
  {
    _microsecond_10 = microsecond_10;
    _second = second;
  }
}
void TimeUpdate(void)
{
  state.digit[2] = _microsecond_10 / 10;
  state.digit[3] = _microsecond_10 % 10;
  state.digit[0] = _second / 10;
  state.digit[1] = _second % 10;
  Update = OFF;
}
void stopwatchStart()//timer1 on
{
  Flag_ReadTime = 0;
  TCCR1B |= Timer1.clockSelectBits;
}
void stopwatchPause()//timer1 off if [CS12 CS11 CS10] is [0 0 0].
{
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
}
void stopwatchReset()
{
  stopwatchPause();
  Flag_ReadTime = 0;
  _microsecond_10 = 0;
  _second = 0;
  microsecond_10 = 0;
  second = 0;
  Update = ON;
}
void saveTime()
{
  EEPROM.write(eepromaddr ++,microsecond_10);
  EEPROM.write(eepromaddr ++,second);
}
void readTime()
{
  Flag_ReadTime = 1;
  if(eepromaddr == 0)
  {
    Serial.println("The time had been read");
    _microsecond_10 = 0;
    _second = 0;
  }
  else{
  _second = EEPROM.read(-- eepromaddr);
  _microsecond_10 = EEPROM.read(-- eepromaddr);
  Serial.println("List the time");
  }
  Update = ON;
}