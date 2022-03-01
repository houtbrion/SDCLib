
#include "SDC_NeoPixel.h"

#define INTERVAL 500
#define LED_PIN 12
#define NUM_OF_LED 1
#define NEO_PIXEL_TYPE NEO_RGB + NEO_KHZ800
#define STEP 64


SDC_NeoPixel led(LED_PIN, NEO_PIXEL_TYPE, NUM_OF_LED);
ledState_t state;

void setup()
{
  Serial.begin(9600);
  led.begin();
}

void printState(ledState_t state) {
  Serial.print(" Brightness = ");
  Serial.print(state.brightness);
  Serial.print(" , Red = ");Serial.print(state.color.rgb.red);
  Serial.print(" , Green = ");Serial.print(state.color.rgb.green);
  Serial.print(" , Blue = ");Serial.println(state.color.rgb.blue);
}

void loop()
{
  for (int g=0; g< 256; g+=STEP) {
    for (int b=0; b< 256; b+=STEP) {
      for (int r=0; r< 256; r+=STEP) {
        for (int i=0; i< 256; i+=STEP) {
          state.brightness=i;
          state.color.rgb.red=r;
          state.color.rgb.green=g;
          state.color.rgb.blue=b;
          if (SIMPLE_DEVICE_CONTROL_SUCCESS != led.SetState(&state, (NUM_OF_LED-1))) {
            Serial.println("set state to led fail");
          }
          if (SIMPLE_DEVICE_CONTROL_SUCCESS != led.ApplyState((NUM_OF_LED-1))) {
            Serial.println("apply state to led fail");
          }
          led.GetState(&state, (NUM_OF_LED-1));
          printState(state);
          delay(INTERVAL);
        }
      }
    }
  }
}
