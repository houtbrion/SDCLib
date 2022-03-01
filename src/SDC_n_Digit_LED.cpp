#include "SDC_n_Digit_LED.h"

SDC_n_Digit_Led::SDC_n_Digit_Led(int32_t deviceID) {
}

bool SDC_n_Digit_Led::begin(int32_t id) {
  if (id != SIMPLE_DEVICE_CONTROL_DEV_ID_MAX) return false;
  return true;
}

int SDC_n_Digit_Led::ApplyState(int32_t id) {
  if (id!=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}
