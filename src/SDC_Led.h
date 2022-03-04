#ifndef __SDC_LED_H__
#define __SDC_LED_H__


#ifndef SIMPLE_DEVICE_CONTROL_DEV_ID_MAX
#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x1
#endif /* SIMPLE_DEVICE_CONTROL_DEV_ID_MAX */

#ifndef SIMPLE_DEVICE_CONTROL_DEV_ID_ALL
#define SIMPLE_DEVICE_CONTROL_DEV_ID_ALL       0xFF
#endif /* SIMPLE_DEVICE_CONTROL_DEV_ID_ALL */

#include "SimpleDeviceControl.h"

class SDC_Led : public SimpuleDeviceControl {
public:
  SDC_Led(int32_t devNum=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool  begin(void);
  int ApplyState(int32_t id);
private:
  int32_t  _numOfLED;
};

#endif /* __SDC_LED_H__ */
