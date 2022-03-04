#ifndef __SDC_N_DIGIT_LED_H__
#define __SDC_N_DIGIT_LED_H__


#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x1
#define SIMPLE_DEVICE_CONTROL_DEV_ID_ALL       0xFF

#include "SimpleDeviceControl.h"

class SDC_n_Digit_Led : public SimpuleDeviceControl {
public:
  SDC_n_Digit_Led(int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool begin(int32_t id = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  int ApplyState(int32_t id = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
};

#endif /* __SDC_N_DIGIT_LED_H__ */
