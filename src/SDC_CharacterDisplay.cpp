#include "SDC_CharacterDisplay.h"


SDC_CharacterDisplay::SDC_CharacterDisplay(int32_t deviceID) {
}

bool SDC_CharacterDisplay::begin(int32_t id) {
  if ( id > SIMPLE_DEVICE_CONTROL_DEV_ID_MAX ) return false;
  return true;
}


int SDC_CharacterDisplay::ApplyState(int32_t id) {
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}
