#ifndef __SIMPLE_DEVICE_CONTROL_H__
#define __SIMPLE_DEVICE_CONTROL_H__
#include <Arduino.h>


#define SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION -2 /* 存在しない機能(state)を指定 */
#define SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID   -1 /* デバイスIDが不正 */
#define SIMPLE_DEVICE_CONTROL_FAIL                  0
#define SIMPLE_DEVICE_CONTROL_SUCCESS               1

#define SDC_DEFAULT_DEVICE_NUMBER 1

#define TONE_ARRAY_SIZE 32

#ifndef MAX_DIGITS
#define MAX_DIGITS 8
#endif /* MAX_DIGITS for n-digit led*/

typedef enum {
  SDC_DEVICE_CATEGORY_LED               = (0),
  SDC_DEVICE_CATEGORY_N_DIGIT_LED       = (1),
  SDC_DEVICE_CATEGORY_CHARACTER_DISPLAY = (2),
  SDC_DEVICE_CATEGORY_SOUND_DEVICE      = (3)
} device_category_t;

typedef enum {
  SDC_DEVICE_TYPE_SINGLE_MONO_LED            = (0),
  SDC_DEVICE_TYPE_WS281X                     = (1),
  SDC_DEVICE_TYPE_GROVE_LED_BAR              = (2),
  SDC_DEVICE_TYPE_GROVE_CIRCULAR_LED         = (3),
  SDC_DEVICE_TYPE_TM1637                     = (4),
  SDC_DEVICE_TYPE_16x2_CHRACTER_DISPLAY      = (5),
  SDC_DEVICE_TYPE_GROVE_CHAINABLE_RGB_LED    = (6),
  SDC_DEVICE_TYPE_TONE_DEVICE                = (7)
} device_type_t;

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} rgb_t;

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
} rgba_t;

typedef union {
  rgb_t   rgb;
  rgba_t  rgba;
} color_t;

typedef struct {
  uint8_t x;
  uint8_t y;
} position_t;


typedef struct {
  uint8_t num;
  uint8_t *charMap;
} custom_char_t;

typedef struct {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} backlight_rgb_t;

typedef struct {
  int value;
  int format;
} integer_pair_t;

typedef struct {
  unsigned char value;
  int format;
} uchar_int_pair_t;

typedef struct {
  unsigned int value;
  int format;
} uint_int_pair_t;

typedef struct {
  long value;
  int format;
} long_int_pair_t;

typedef struct {
  unsigned long value;
  int format;
} ulong_int_pair_t;

typedef struct {
  double value;
  int format;
} double_int_pair_t;

typedef struct {
  //bool      OnOff;
  color_t   color;
  uint8_t  brightness;
} ledState_t;

typedef struct {
  uint8_t brightness;
  bool colon;
  int8_t digit[MAX_DIGITS];
} digit_led_state_t;

typedef struct {
  uint8_t command;
  union {
    backlight_rgb_t rgb;
    position_t position;
    custom_char_t customChar;
    integer_pair_t int_pair;
    __FlashStringHelper *flashString;
    char *charArray;
    char character;
    uchar_int_pair_t uchar_int_pair;
    uint_int_pair_t uint_int_pair;
    long_int_pair_t long_int_pair;
    ulong_int_pair_t ulong_int_pair;
    double_int_pair_t double_int_pair;
    uint8_t customCharNum;
  };
} character_display_state_t;

typedef struct {
  unsigned int data_size;
  unsigned int freq[TONE_ARRAY_SIZE];
  unsigned int duration[TONE_ARRAY_SIZE];
  unsigned long rest[TONE_ARRAY_SIZE];
} toneState_t;


typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t z;
} device_subid_t;


typedef struct {
  // 負 : 機能がない
  // 0  : 全部のLEDに同じ値しかセットできない
  // 1  : 個別の設定が可能
  // 2  : apiで全体にまとめて設定ができる
  //int8_t Off;         // LEDのOFFのサポート状況
  int8_t set;         // 個別にSetできるか，一括Setのみか
  int8_t apply;       // ApplyがSetと独立しているか否か
  int8_t brightnessDeps; // brightnessの最大値(2進数のなんビットか?)
  uint8_t color;          // 0 : モノ, 1 : RGB , 2 : RGBA  (その他はいまのところ未定義)
} led_type_t;

typedef struct {
  // 負 : 機能がない
  // 0  : 全部のLEDに同じ値しかセットできない
  // 1  : 個別の設定が可能
  // 2  : apiで全体にまとめて設定ができる
  int8_t set;         // 個別にSetできるか，一括Setのみか
  int8_t apply;       // ApplyがSetと独立しているか否か
  int8_t digits;      // 文字の桁数
  int8_t symbols;     // 小数点などのLEDの数
} n_digit_led_type_t;

typedef struct {
  // 負 : 機能がない
  // 0  : 全部のLEDに同じ値しかセットできない
  // 1  : 個別の設定が可能
  // 2  : apiで全体にまとめて設定ができる
  int8_t set;         // 個別にSetできるか，一括Setのみか
  int8_t apply;       // ApplyがSetと独立しているか否か
  uint8_t columns;     // 文字の桁数
  uint8_t lines;       // 文字の行数
  uint8_t backLight;   // バックライト 0: なし, 1:単色, 2:カラー
} character_display_type_t;

typedef struct {
  // 負 : 機能がない
  // 0  : 全部のLEDに同じ値しかセットできない
  // 1  : 個別の設定が可能
  // 2  : apiで全体にまとめて設定ができる
  int8_t set;         // 個別にSetできるか，一括Setのみか
  int8_t apply;       // ApplyがSetと独立しているか否か
} tone_device_type_t;

typedef struct {
  int32_t type;
  int32_t version;
  int32_t device_num;
  int32_t category;
  union{
    led_type_t ledType;
    n_digit_led_type_t digitLedType;
    character_display_type_t characterDisplayType;
    tone_device_type_t tone_device;
  };
} device_info_t;

class SimpuleDeviceControl {
public:
  SimpuleDeviceControl() {}
  virtual ~SimpuleDeviceControl() {}
};

#endif /* __SIMPLE_DEVICE_CONTROL_H__ */
