#include "SDC_Led.h"

SDC_Led::SDC_Led(int32_t devNum) {
  _numOfLED=devNum;
}

bool SDC_Led::begin(void) {
  if ( _numOfLED > SIMPLE_DEVICE_CONTROL_DEV_ID_MAX) return false;
  return true;
}

int SDC_Led::ApplyState(int32_t id) {
  if (id!=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}