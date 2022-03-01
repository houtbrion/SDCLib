#include "SDC_TM1637.h"

#define LED_BRIGHTNESS BRIGHT_DARKEST
//#define LED_BRIGHTNESS BRIGHT_TYPICAL
//#define LED_BRIGHTNESS BRIGHTEST

digit_led_state_t state;

unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 0;
unsigned char hour = 8;

#define CLK 4//pins definitions for TM1637 and can be changed to other ports
#define DIO 5

SDC_TM1637 tm1637(CLK,DIO);

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
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
  state.brightness=LED_BRIGHTNESS;
  Serial.println("setup done.");
}
void loop()
{
  if(Update == ON)
  {
    Serial.println("update time.");
    TimeUpdate();
    tm1637.SetState(&state);
  }
}
void TimingISR()
{
  halfsecond ++;
  Update = ON;
  if(halfsecond == 2){
    second ++;
    if(second == 60)
    {
      minute ++;
      if(minute == 60)
      {
        hour ++;
        if(hour == 24)hour = 0;
        minute = 0;
      }
      second = 0;
    }
    halfsecond = 0;
  }
  if (state.colon) {
    state.colon=false;
  } else {
    state.colon=true;
  }
}
void TimeUpdate(void)
{
  state.digit[0]= hour / 10;
  state.digit[1]= hour % 10;
  state.digit[2]= minute / 10;
  state.digit[3]= minute % 10;
  Update = OFF;
}
