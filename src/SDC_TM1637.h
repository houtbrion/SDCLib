#ifndef __SDC_TM1637_H__
#define __SDC_TM1637_H__

#define ON 1
#define OFF 0
#define MAX_DIGITS 4
#define MAX_SYMBOLS 1
#define SDC_TM1637_VERSION 1
#define TM1637_DEFAULT_BRIGHTNESS BRIGHT_TYPICAL
#define SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID   0x0

#include "SDC_n_Digit_LED.h"
#include <TimerOne.h>
#include "TM1637.h"

class SDC_TM1637 : public SDC_n_Digit_Led {
public:
  SDC_TM1637(uint8_t clk_pin, uint8_t data_pin, int32_t deviceID=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool begin(int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int SetState(digit_led_state_t *state, int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int GetState(digit_led_state_t *state, int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int  getDeviceInfo(device_info_t * info, int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
private:
  //SDC_n_Digit_Led _super;
  TM1637 _tm1637;
};


#endif /* __SDC_TM1637_H__ */
