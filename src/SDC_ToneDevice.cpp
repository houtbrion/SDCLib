
#include "SDC_ToneDevice.h"

SDC_ToneDevice::SDC_ToneDevice(uint8_t _pin, int32_t deviceID){
  output_pin=_pin;
}

bool SDC_ToneDevice::begin(int32_t id) {
  if (id!=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  pinMode(output_pin, OUTPUT);
}

int SDC_ToneDevice::getDeviceInfo(device_info_t * info, int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (info==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  info->type = SDC_DEVICE_TYPE_TONE_DEVICE;
  info->version = SDC_TONE_DEVICE_VERSION;
  info->category = SDC_DEVICE_CATEGORY_SOUND_DEVICE;
  info->tone_device.set = 0;  //
  info->tone_device.apply = SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

int SDC_ToneDevice::SetState(toneState_t *state, int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  for (int i=0; i< state->data_size;i++){
    tone(this->output_pin, state->freq[i], state->duration[i]);
    if (state->rest[i]!=0) delay(state->rest[i]);
    noTone(this->output_pin);
  }
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

int SDC_ToneDevice::GetState(toneState_t *state, int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}