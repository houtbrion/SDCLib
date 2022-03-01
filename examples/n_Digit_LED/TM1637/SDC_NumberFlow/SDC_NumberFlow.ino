
#include "SDC_TM1637.h"

#define LED_BRIGHTNESS BRIGHT_DARKEST
//#define LED_BRIGHTNESS BRIGHT_TYPICAL
//#define LED_BRIGHTNESS BRIGHTEST

digit_led_state_t state;

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
  state.brightness=LED_BRIGHTNESS;
  Serial.println("setup done.");
}

void loop()
{
  int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
  int8_t ListDisp[4];
  unsigned char i = 0;
  unsigned char count = 0;
  delay(150);
  while(1) {
    i = count;
    count ++;
    if(count == sizeof(NumTab)) count = 0;
    for(unsigned char BitSelect = 0;BitSelect < 4;BitSelect ++) {
      ListDisp[BitSelect] = NumTab[i];
      i ++;
      if(i == sizeof(NumTab)) i = 0;
    }
    state.digit[0]=-1;state.digit[1]=-1;state.digit[2]=-1;state.digit[3]=-1;
    state.digit[0]=ListDisp[0];state.digit[1]=-1;state.digit[2]=-1;state.digit[3]=-1;
    tm1637.SetState(&state);
    state.digit[0]=-1;state.digit[1]=ListDisp[1];state.digit[2]=-1;state.digit[3]=-1;
    tm1637.SetState(&state);
    state.digit[0]=-1;state.digit[1]=-1;state.digit[2]=ListDisp[2];state.digit[3]=-1;
    tm1637.SetState(&state);
    state.digit[0]=-1;state.digit[1]=-1;state.digit[2]=-1;state.digit[3]=ListDisp[3];
    tm1637.SetState(&state);
    delay(300);
  }
}
