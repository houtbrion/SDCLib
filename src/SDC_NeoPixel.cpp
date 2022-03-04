#include "SDC_NeoPixel.h"

SDC_NeoPixel::SDC_NeoPixel(uint8_t pin, neoPixelType type, int32_t deviceNum) :
  _ledPin(pin),
  _type(type)
{
  if (deviceNum> SIMPLE_DEVICE_CONTROL_DEV_ID_MAX) {
    _numOfLed=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX;
  } else {
    _numOfLed=(uint16_t)deviceNum;
  }
}

// 負 : 機能がない
// 0  : 全部のLEDに同じ値しかセットできない
// 1  : 個別の設定が可能
// 2  : apiで全体にまとめて設定ができる
int SDC_NeoPixel::getDeviceInfo(device_info_t * info, int32_t num){
  if (num > _numOfLed) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  if (info==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  info->type = SDC_DEVICE_TYPE_WS281X;
  info->version = SDC_NEO_PIXEL_VERSION;
  info->device_num = _numOfLed;
  info->category = SDC_DEVICE_CATEGORY_LED;
  info->ledType.set = 1;  // 現状は個別設定のみサポート
  info->ledType.apply = SIMPLE_DEVICE_CONTROL_SUCCESS; // applyが必要
  info->ledType.brightnessDeps = 8; // 255段階 (8bit値)
  info->ledType.color =RGB_LED; // RGB指定フルカラー
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

bool SDC_NeoPixel::begin(int32_t num) {
  if (num > _numOfLed) return false;
  _neoPixel.setPin(_ledPin);
  _neoPixel.updateLength(_numOfLed);
  _neoPixel.updateType(_type);
  _neoPixel.begin();
  _neoPixel.clear();
  return true;
}

int SDC_NeoPixel::GetState(ledState_t * state, int32_t num) {
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  if (_numOfLed < num) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  state->brightness=_neoPixel.getBrightness();
  uint32_t colorVal=_neoPixel.getPixelColor((uint16_t)num);
  colorVal=colorVal&0xFFFFFF;
  state->color.rgb.red=(uint8_t) (colorVal>>16);
  colorVal=colorVal&0xFFFF;
  state->color.rgb.green=(uint8_t) (colorVal>>8);
  colorVal=colorVal&0xFF;
  state->color.rgb.blue=(uint8_t) colorVal;
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

int SDC_NeoPixel::SetState(ledState_t *state, int32_t num) {
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  if (_numOfLed < num) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  _neoPixel.setBrightness(state->brightness);
  _neoPixel.setPixelColor((uint16_t)num,state->color.rgb.red,state->color.rgb.green,state->color.rgb.blue);
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}

int SDC_NeoPixel::ApplyState(int32_t num) {
  if (_numOfLed < num) return SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID;
  _neoPixel.show();
  return SIMPLE_DEVICE_CONTROL_SUCCESS;
}
