#include "SDC_Grove_LED_Bar.h"


SDC_GroveLedBar::SDC_GroveLedBar(uint8_t _clk_pin, uint8_t _data_pin, bool _reverse, int32_t _type) :
  clk_pin(_clk_pin),
  data_pin(_data_pin),
  reverse(_reverse),
  type(_type),
  grove(_clk_pin, _data_pin, _reverse, _type)
{}

bool SDC_GroveLedBar::begin(int32_t num){
  if (num>SDC_GROVE_LED_BAR_LED_MAX) return false;
  switch(type) {
    case LED_BAR_10:max_led=10;break;
    case LED_CIRCULAR_24:max_led=24;break;
    default: return false;
  }
  return true;
}

// 負 : 機能がない
// 0  : 全部のLEDに同じ値しかセットできない
// 1  : 個別の設定が可能
// 2  : apiで全体にまとめて設定ができる
int SDC_GroveLedBar::getDeviceInfo(device_info_t * info, int32_t num) {
  if (num>SDC_GROVE_LED_BAR_LED_MAX) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (info==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  info->type = SDC_DEVICE_TYPE_GROVE_LED_BAR;
  info->version = SDC_GROVE_LED_BAR_VERSION;
  info->category = SDC_DEVICE_CATEGORY_LED;
  info->device_num = max_led;
  info->ledType.set = 1;  // 個別の設定が可能
  info->ledType.apply = SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION; // setで適用してしまう
  info->ledType.brightnessDeps = 8; // 255段階 (8bit値)
  info->ledType.color =0; // 0 : モノ, 1 : RGB , 2 : RGBA  (その他はいまのところ未定義)
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

int SDC_GroveLedBar::SetState(ledState_t *state, int32_t num) {
  if (num>SDC_GROVE_LED_BAR_LED_MAX) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
  float bri=(float) state->brightness;
  bri=bri/255;
  if ((num>SDC_GROVE_LED_BAR_LED_MAX) ||(num <0)) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  grove.setLed((num+1), bri);
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

int SDC_GroveLedBar::ApplyState(int32_t num) {
  if (num>SDC_GROVE_LED_BAR_LED_MAX) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}

int SDC_GroveLedBar::GetState(ledState_t *state, int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}