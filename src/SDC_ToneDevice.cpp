
#include "SDC_ToneDevice.h"

SDC_ToneDevice::SDC_ToneDevice(uint8_t _pin, int32_t deviceID){
  output_pin=_pin;
}

bool SDC_ToneDevice::begin(void) {
  pinMode(output_pin, OUTPUT);
  //Serial.print("output_pin = ");Serial.println(output_pin);
}



// �� : �@�\���Ȃ�
// 0  : �S����LED�ɓ����l�����Z�b�g�ł��Ȃ�
// 1  : �ʂ̐ݒ肪�\
// 2  : api�őS�̂ɂ܂Ƃ߂Đݒ肪�ł���
void SDC_ToneDevice::getDeviceInfo(device_info_t * info, int32_t num) {
  if (num !=0) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  info->type = SDC_DEVICE_TYPE_TONE_DEVICE;
  info->version = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX;
  info->category = SDC_DEVICE_CATEGORY_SOUND_DEVICE;
  info->tone_device.set = 0;  //
  info->tone_device.apply = SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION; // set�œK�p���Ă��܂�
}

int SDC_ToneDevice::SetState(toneState_t *state, int32_t num) {
  if (num !=0) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  for (int i=0; i< state->data_size;i++){
    //Serial.print("freq     = ");Serial.println(state->freq[i]);
    //Serial.print("duration = ");Serial.println(state->duration[i]);
    //Serial.print("rest     = ");Serial.println(state->rest[i]);
    tone(this->output_pin, state->freq[i], state->duration[i]);
    if (state->rest[i]!=0) delay(state->rest[i]);
    noTone(this->output_pin);
  }
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}
