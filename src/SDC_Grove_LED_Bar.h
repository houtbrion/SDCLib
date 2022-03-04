#ifndef __SDC_GROVE_LED_BAR_H__
#define __SDC_GROVE_LED_BAR_H__


#define SDC_GROVE_LED_BAR_VERSION 1
#define SDC_GROVE_LED_BAR_LED_MAX 9 // 0～9の10個
#define SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID   0x0

#include "SDC_Led.h"
#include "Grove_LED_Bar.h"

class SDC_GroveLedBar : public SDC_Led {
public:
  SDC_GroveLedBar(uint8_t clk_pin, uint8_t data_pin, bool reverse=false, int32_t type = LED_BAR_10);
  bool  begin(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   GetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   ApplyState(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
private:
  Grove_LED_Bar grove;
  uint8_t clk_pin;
  uint8_t data_pin;
  int32_t max_led;
  bool reverse;
  int32_t type;
};
#endif /* __SDC_GROVE_LED_BAR_H__ */
