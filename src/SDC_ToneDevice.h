#ifndef __SDC_TONE_DEVICE_H__
#define __SDC_TONE_DEVICE_H__

#include "SDC_SoundDevice.h"



#define SDC_TONE_DEVICE_VERSION 1
#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x1

class SDC_ToneDevice : public SDC_SoundDevice {
public:
  SDC_ToneDevice(uint8_t output_pin, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  bool  begin(void);
  int   SetState(toneState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  void  getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
private:
  uint8_t output_pin;
};


#endif /* __SDC_TONE_DEVICE_H__ */
