/* 
 * Example of using the ChainableRGB library for controlling a Grove RGB.
 * This code cycles through all the colors in an uniform way. This is accomplished using a HSB color space. 
 */
 
 
#include "SDC_Grove_Chainable_RGB_LED.h"
 
#define NUM_LEDS  2
#define STEP 64
#define INTERVAL 500

SDC_Grove_Chainable_RGB_Led leds(10, 11, NUM_LEDS);

ledState_t state;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");
  leds.begin();
  Serial.println("setup done.");
}

 
void loop()
{
  for (int g=0; g< 256; g+=STEP) {
    for (int b=0; b< 256; b+=STEP) {
      for (int r=0; r< 256; r+=STEP) {
        state.color.rgb.red=r;
        state.color.rgb.green=g;
        state.color.rgb.blue=b;
        for (int i=0; i< NUM_LEDS; i++) {
          if (SIMPLE_DEVICE_CONTROL_SUCCESS != leds.SetState(&state, i)) {
            Serial.print("set state to led No.");Serial.print(i);Serial.println(" fail.");
          }
          delay(INTERVAL);
        }
        state.color.rgb.red=0;
        state.color.rgb.green=0;
        state.color.rgb.blue=0;
        for (int i=0; i< NUM_LEDS; i++) {
          if (SIMPLE_DEVICE_CONTROL_SUCCESS != leds.SetState(&state, i)) {
            Serial.print("set state to led No.");Serial.print(i);Serial.println(" fail.");
          }
          delay(INTERVAL);
        }
        delay(INTERVAL);
      }
    }
  }
}
