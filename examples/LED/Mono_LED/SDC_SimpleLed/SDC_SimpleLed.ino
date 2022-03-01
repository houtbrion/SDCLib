
#include "SDC_SimpleLed.h"

#include "arduinoHardwareHelper.h"

#define INTERVAL 1000
#define LED_PIN 2
#define STEP 16

HardwareHelper helper;

SDC_SimpleLed led(LED_PIN );
ledState_t state;
uint8_t pmw;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");
  
  if (helper.checkPMW(LED_PIN)) {
    pmw=PIN_TYPE_PMW;
    Serial.println("PMW is OK");
  } else {
    pmw=PIN_TYPE_NO_PMW;
    Serial.println("PMW is not OK");
  }
  led.begin(pmw);
}

void pmwTest(){
  for (int i=0; i< 256; i+=STEP) {
    Serial.print("Brightness = ");Serial.println(i);
    state.brightness=i;
    led.SetState(&state);
    delay(INTERVAL);
    Serial.println("LED Off");
    state.brightness=0;
    led.SetState(&state);
    delay(INTERVAL);
  }
}

void digitalTest(void) {
  Serial.println("LED On");
  led.SetState(&state);
  Serial.println("LED On");
  delay(INTERVAL);
  led.SetState(&state);
  Serial.println("LED Off");
  delay(INTERVAL);
}

void loop()
{
  if (pmw==PIN_TYPE_PMW) {
    pmwTest();
  } else {
    digitalTest();
  }
}
