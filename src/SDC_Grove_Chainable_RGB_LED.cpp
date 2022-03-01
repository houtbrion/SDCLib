#include "SDC_Grove_Chainable_RGB_LED.h"

SDC_Grove_Chainable_RGB_Led::SDC_Grove_Chainable_RGB_Led(uint8_t _clk_pin, uint8_t _data_pin, int32_t num) {
  clk_pin=(byte) _clk_pin;
  data_pin=(byte) _data_pin;
  if (num > SIMPLE_DEVICE_CONTROL_DEV_ID_MAX) {
    devNum=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX;
  } else {
    devNum=(byte) num;
  }
}

// 負 : 機能がない
// 0  : 全部のLEDに同じ値しかセットできない
// 1  : 個別の設定が可能
// 2  : apiで全体にまとめて設定ができる
void SDC_Grove_Chainable_RGB_Led::getDeviceInfo(device_info_t * info, int32_t num){
  info->type = SDC_DEVICE_TYPE_GROVE_CHAINABLE_RGB_LED;
  info->version = SDC_GROVE_CHAINALE_RGB_LED_VERSION;
  info->device_num = devNum;
  info->category = SDC_DEVICE_CATEGORY_LED;
  info->ledType.set = 0;  // 現状は個別設定のみサポート
  info->ledType.apply = SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION; // setで適用してしまう
  info->ledType.brightnessDeps = 1; // 輝度の設定機能はなし(RGBで設定)
  info->ledType.color =2; // RGB指定フルカラー
}

bool SDC_Grove_Chainable_RGB_Led::begin(void){
  led=new ChainableLED((byte) clk_pin, (byte) data_pin, (byte) devNum);
  return true;
}

int SDC_Grove_Chainable_RGB_Led::SetState(ledState_t *state, int32_t num) {
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
  if (num > devNum) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  led->setColorRGB((byte) num , (byte )state->color.rgb.red,(byte ) state->color.rgb.green, (byte ) state->color.rgb.blue);
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

