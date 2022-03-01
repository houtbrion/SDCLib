#ifndef __SDC_SIMPLE_LED_H__
#define __SDC_SIMPLE_LED_H__

#include "SDC_Led.h"

#define SDC_SIMPLE_LED_VERSION 1

#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x01

#define PIN_TYPE_ANALOG 0
#define PIN_TYPE_PMW 1
#define PIN_TYPE_NO_PMW 2

class SDC_SimpleLed : public SDC_Led {
public:
  SDC_SimpleLed(uint8_t led_pin, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool  begin(uint8_t type=PIN_TYPE_PMW);
  int   SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  void  getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
private:
  uint8_t led_pin;
  uint8_t pinType; // 0=analog, 1=pmw , 2= no pmw
};

#endif /* __SDC_SIMPLE_LED_H__ */
