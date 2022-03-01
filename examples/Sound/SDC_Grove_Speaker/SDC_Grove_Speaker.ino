

#define SPEAKER_PIN 8
#define WAIT_TIME 1000
#define DURATION 500

#define LOOP_WAIT_TIME 3000


#include "SDC_ToneDevice.h"

#define TONE_USE_INT
#define TONE_PITCH 440
#include <TonePitch.h>



SDC_ToneDevice tone_device(SPEAKER_PIN);

toneState_t toneState;

void setToneData() {
  toneState.data_size=2;
  toneState.freq[0]=NOTE_C4;
  toneState.freq[1]=NOTE_E4;
  toneState.duration[0]=DURATION;
  toneState.duration[1]=DURATION;
  toneState.rest[0]=WAIT_TIME;
  toneState.rest[1]=WAIT_TIME;
}

void setup(){
  Serial.begin(9600);
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");
  tone_device.begin();
  setToneData();
  Serial.println("setup done.");
}

void loop()
{
  Serial.println("play start.");
  tone_device.SetState(&toneState,0);
  Serial.println("play end.");
  delay(LOOP_WAIT_TIME);
}
