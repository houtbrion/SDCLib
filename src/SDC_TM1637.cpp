#include "SDC_TM1637.h"


SDC_TM1637::SDC_TM1637(uint8_t clk_pin, uint8_t data_pin, int32_t deviceID) :
  _tm1637(clk_pin, data_pin)
{}

bool SDC_TM1637::begin(int32_t id) {
  if (id != SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return false;
  _tm1637.set();
  _tm1637.init();
  return true;
}

int SDC_TM1637::SetState(digit_led_state_t *state, int32_t id) {
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
  if (id!=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  int8_t digit[MAX_DIGITS];
  _tm1637.set(state->brightness);
  bool flag=true;
  for (int i=0 ; i< MAX_DIGITS; i++) {
    digit[i]=state->digit[i];
    if ( digit[i] < 0 ) flag=false;
  }
  if (state->colon) {
    _tm1637.point(POINT_ON);
  } else {
    _tm1637.point(POINT_OFF);
  }
  if (flag) {
    _tm1637.display(digit);
  } else {
    for (int i=0 ; i< MAX_DIGITS; i++) {
      if (digit[i]>0) {
        _tm1637.display(i,digit[i]);
      }
    }
  }
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

// 負 : 機能がない
// 0  : 全部のLEDに同じ値しかセットできない
// 1  : 個別の設定が可能
// 2  : apiで全体にまとめて設定ができる
int SDC_TM1637::getDeviceInfo(device_info_t * info, int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (info==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  info->type = SDC_DEVICE_TYPE_TM1637;
  info->version = SDC_TM1637_VERSION;
  info->device_num = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX;
  info->category = SDC_DEVICE_CATEGORY_N_DIGIT_LED;
  info->digitLedType.set = 0;  // 全部のLEDに同じ値しかセットできない(というか1個しかないので意味はあまりない)
  info->digitLedType.apply = SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION; // setで設定実行
  info->digitLedType.digits = MAX_DIGITS; // 4桁
  info->digitLedType.symbols = MAX_SYMBOLS; // 1つ(コロンのみ)
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

int SDC_TM1637::GetState(digit_led_state_t *state, int32_t num) {
  if (num !=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION;
}