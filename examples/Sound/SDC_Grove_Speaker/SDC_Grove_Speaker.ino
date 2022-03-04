

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
  toneState.data_size=8;
  toneState.freq[0]=NOTE_C4;
  toneState.freq[1]=NOTE_D4;
  toneState.freq[2]=NOTE_E4;
  toneState.freq[3]=NOTE_F4;
  toneState.freq[4]=NOTE_G4;
  toneState.freq[5]=NOTE_A4;
  toneState.freq[6]=NOTE_B4;
  toneState.freq[7]=NOTE_C5;
  toneState.duration[0]=DURATION;
  toneState.duration[1]=DURATION;
  toneState.duration[2]=DURATION;
  toneState.duration[3]=DURATION;
  toneState.duration[4]=DURATION;
  toneState.duration[5]=DURATION;
  toneState.duration[6]=DURATION;
  toneState.duration[7]=DURATION;
  toneState.rest[0]=WAIT_TIME;
  toneState.rest[1]=WAIT_TIME;
  toneState.rest[2]=WAIT_TIME;
  toneState.rest[3]=WAIT_TIME;
  toneState.rest[4]=WAIT_TIME;
  toneState.rest[5]=WAIT_TIME;
  toneState.rest[6]=WAIT_TIME;
  toneState.rest[7]=WAIT_TIME;
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
  Serial.println("play start.");
  tone_device.SetState(&toneState,0);
  Serial.println("play end.");
}

void loop()
{
  //delay(LOOP_WAIT_TIME);
}
