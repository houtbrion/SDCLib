
#include "SDC_SoundDevice.h"

SDC_SoundDevice::SDC_SoundDevice(int32_t devNum) {
  numOfLED=devNum;
}

bool SDC_SoundDevice::begin(void) {
  if ( numOfLED > SIMPLE_DEVICE_CONTROL_DEV_ID_MAX) return false;
  return true;
}

int SDC_SoundDevice::ApplyState(int32_t id) {
  if (id!=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}

