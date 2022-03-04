#ifndef __SDC_GROVE_CHAINALBLE_RGB_LED_H__
#define __SDC_GROVE_CHAINALBLE_RGB_LED_H__



#define SDC_GROVE_CHAINALE_RGB_LED_VERSION 1

#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0xFE
#define SIMPLE_DEVICE_CONTROL_DEV_ID_ALL       0xFF
#define SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM  0x0

#include "SDC_Led.h"
#include <ChainableLED.h>

class SDC_Grove_Chainable_RGB_Led : public SDC_Led {
public:
  SDC_Grove_Chainable_RGB_Led(uint8_t clk_pin, uint8_t data_pin, int32_t num = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool  begin(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM);
  int   SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM);
  int   GetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM);
  int  getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM);
private:
  byte devNum;
  byte data_pin;
  byte clk_pin;
  ChainableLED *led;
  //ChainableLED led;
};

#endif /* __SDC_GROVE_CHAINALBLE_RGB_LED_H__ */
