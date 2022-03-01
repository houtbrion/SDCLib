

#include "SDC_Grove_LED_Bar.h"

#define INTERVAL 100

SDC_GroveLedBar led=SDC_GroveLedBar(7, 6, true,LED_BAR_10 );

void setup()
{
  Serial.begin(9600);
  delay(1000);
  if (!led.begin()) {
    Serial.println("init led fail");
    while(true){}
  } else {
    Serial.println("init led success");
  }
}

void printState(ledState_t state) {
  Serial.print(" Brightness = ");
  Serial.println(state.brightness);
}

void loop()
{
  ledState_t state;
  for (int i=0;i<(SDC_GROVE_LED_BAR_LED_MAX+1);i++){
    state.brightness=0;
    led.SetState(&state, i);
  }
  for (int i=0;i<(SDC_GROVE_LED_BAR_LED_MAX+1);i++){
    for (int b=0;b<255;b+=32){
      state.brightness=b;
      if (SIMPLE_DEVICE_CONTROL_SUCCESS != led.SetState(&state, i)) {
        Serial.println("set state to led fail");
      }
      Serial.print("led No.=");Serial.print(i);Serial.print(" , ");
      printState(state);
      delay(INTERVAL);
    }
  }
}
