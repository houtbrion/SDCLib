#ifndef __SDC_SIMPLE_LED_H__
#define __SDC_SIMPLE_LED_H__



#define SDC_SIMPLE_LED_VERSION 1

#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x01
//#define SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID   0x0



#define PIN_TYPE_ANALOG 0
#define PIN_TYPE_PMW 1
#define PIN_TYPE_NO_PMW 2

#include "SDC_Led.h"

class SDC_SimpleLed : public SDC_Led {
public:
  SDC_SimpleLed(uint8_t led_pin, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool  begin(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  bool  config(uint8_t type=PIN_TYPE_PMW);
  int   SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   GetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
private:
  uint8_t led_pin;
  uint8_t pinType; // 0=analog, 1=pmw , 2= no pmw
};

#endif /* __SDC_SIMPLE_LED_H__ */
