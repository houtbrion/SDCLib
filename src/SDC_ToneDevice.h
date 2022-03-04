#ifndef __SDC_TONE_DEVICE_H__
#define __SDC_TONE_DEVICE_H__

#define SDC_TONE_DEVICE_VERSION 1
#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x1
#define SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID   0x0

#include "SDC_SoundDevice.h"

class SDC_ToneDevice : public SDC_SoundDevice {
public:
  SDC_ToneDevice(uint8_t output_pin, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool  begin(int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   SetState(toneState_t *state, int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int  getDeviceInfo(device_info_t * info, int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   GetState(toneState_t *state, int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
private:
  uint8_t output_pin;
};


#endif /* __SDC_TONE_DEVICE_H__ */
