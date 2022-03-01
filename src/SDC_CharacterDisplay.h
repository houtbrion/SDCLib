#ifndef __SDC_CHARACTER_DISPLAY_H__
#define __SDC_CHARACTER_DISPLAY_H__

#include "SimpleDeviceControl.h"

#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x1
#define SIMPLE_DEVICE_CONTROL_DEV_ID_ALL       0xFF

class SDC_CharacterDisplay : public SimpuleDeviceControl {
public:
  SDC_CharacterDisplay(int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool begin(int32_t id = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  int ApplyState(int32_t id = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
};

#endif /* __SDC_CHARACTER_DISPLAY_H__ */
