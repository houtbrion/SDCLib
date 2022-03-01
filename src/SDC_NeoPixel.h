#ifndef __SDC_NEO_PIXEL_H__
#define __SDC_NEO_PIXEL_H__
#include "SDC_Led.h"
#include "Adafruit_NeoPixel.h"

#define SDC_NEO_PIXEL_VERSION 1
#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0xFFFE
#define SIMPLE_DEVICE_CONTROL_DEV_ID_ALL       0xFFFF
#define SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM  0x1

class SDC_NeoPixel : public SDC_Led {
public:
  SDC_NeoPixel(uint8_t pin, neoPixelType type=NEO_GRB + NEO_KHZ800, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM);
  bool  begin(void);
  int   GetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM);
  int   SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM);
  int   ApplyState(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM);
  void  getDeviceInfo(device_info_t * info);
private:
  uint8_t _ledPin;
  uint16_t _numOfLed;
  neoPixelType _type;
  Adafruit_NeoPixel _neoPixel;
};

#endif /* __SDC_NEO_PIXEL_H__ */
