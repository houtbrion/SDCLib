#ifndef __SDC_SOUND_DEVICE_H__
#define __SDC_SOUND_DEVICE_H__
#include <Arduino.h>
#include "SimpleDeviceControl.h"

#define SDC_SOUND_DEVICE_VERSION 1

#ifndef SIMPLE_DEVICE_CONTROL_DEV_ID_MAX
#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x1
#endif /* SIMPLE_DEVICE_CONTROL_DEV_ID_MAX */

#ifndef SIMPLE_DEVICE_CONTROL_DEV_ID_ALL
#define SIMPLE_DEVICE_CONTROL_DEV_ID_ALL       0xFF
#endif /* SIMPLE_DEVICE_CONTROL_DEV_ID_ALL */

class SDC_SoundDevice : public SimpuleDeviceControl {
public:
  SDC_SoundDevice(int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool begin(void);
  int ApplyState(int32_t id = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
private:
  int32_t numOfLED;
};
#endif /* __SDC_SOUND_DEVICE_H__ */
