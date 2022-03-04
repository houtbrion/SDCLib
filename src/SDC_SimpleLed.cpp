#include "SDC_SimpleLed.h"

SDC_SimpleLed::SDC_SimpleLed(uint8_t _led_pin, int32_t deviceID):
  led_pin(_led_pin)
{}

// 負 : 機能がない
// 0  : 全部のLEDに同じ値しかセットできない
// 1  : 個別の設定が可能
// 2  : apiで全体にまとめて設定ができる
int SDC_SimpleLed::getDeviceInfo(device_info_t * info, int32_t num) {
  if (info==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  info->type = SDC_DEVICE_TYPE_SINGLE_MONO_LED;
  info->version = SDC_SIMPLE_LED_VERSION;
  info->device_num = 1;
  info->category = SDC_DEVICE_CATEGORY_LED;
  info->ledType.set = 0;  //
  info->ledType.apply = SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION; // setで適用してしまう
  info->ledType.brightnessDeps = 8; // 255段階 (8bit値)
  info->ledType.color =0; //モノクロ
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

bool SDC_SimpleLed::begin(int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return false;
  pinMode(this->led_pin, OUTPUT);
  return true;
}

bool SDC_SimpleLed::config(uint8_t _type) {
  switch(_type) {
    case PIN_TYPE_ANALOG:
    case PIN_TYPE_PMW   :
    case PIN_TYPE_NO_PMW:
      break;
    default: return false;
  }
  pinType=_type;
  return true;
}

int SDC_SimpleLed::SetState(ledState_t *state, int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  if ((this->pinType==PIN_TYPE_ANALOG) || (this->pinType==PIN_TYPE_PMW)) {
    analogWrite(this->led_pin, state->brightness);
  } else {
    if (state->brightness!=0) {
      digitalWrite(this->led_pin, HIGH);
    } else {
      digitalWrite(this->led_pin, LOW);
    }
  }
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

int SDC_SimpleLed::GetState(ledState_t *state, int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}