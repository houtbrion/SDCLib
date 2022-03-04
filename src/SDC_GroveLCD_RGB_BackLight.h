#ifndef __SDC_GROVELCD_RGB_BACKLIGHT_H__
#define __SDC_GROVELCD_RGB_BACKLIGHT_H__



#define SDC_GROVE_LCD_RGB_VERSION 1
#define SDC_GROVE_LCD_RGB_LINES 2
#define SDC_GROVE_LCD_RGB_COLUMNS 16

#define SIMPLE_DEVICE_CONTROL_DEV_ID_MAX       0x1
#define SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID   0x0

#include "SDC_CharacterDisplay.h"
#include <Wire.h>
#include "rgb_lcd.h"

typedef enum {
  GROVE_CHARACTER_DISPLAY_CURSOR_HOME      = (0),
  GROVE_CHARACTER_DISPLAY_CLEAR                 ,
  GROVE_CHARACTER_DISPLAY_OFF                   ,
  GROVE_CHARACTER_DISPLAY_ON                    ,
  GROVE_CHARACTER_DISPLAY_CURSOR_NO_BLINK       ,
  GROVE_CHARACTER_DISPLAY_CURSOR_BLINK          ,
  GROVE_CHARACTER_DISPLAY_NO_CURSOR             ,
  GROVE_CHARACTER_DISPLAY_CURSOR                ,
  GROVE_CHARACTER_DISPLAY_SCROLL_LEFT           ,
  GROVE_CHARACTER_DISPLAY_SCROLL_RIGHT          ,
  GROVE_CHARACTER_DISPLAY_LEFT_TO_RIGHT         ,
  GROVE_CHARACTER_DISPLAY_RIGHT_TO_LEFT         ,
  GROVE_CHARACTER_DISPLAY_AUTO_SCROLL           ,
  GROVE_CHARACTER_DISPLAY_NO_AUTO_SCROLL        ,
  GROVE_CHARACTER_DISPLAY_RGB                   ,
  GROVE_CHARACTER_DISPLAY_SET_CURSOR            ,
  GROVE_CHARACTER_DISPLAY_CREATE_CHARACTER      ,
  GROVE_CHARACTER_DISPLAY_PRINT_FLASH_STRING    ,
  GROVE_CHARACTER_DISPLAY_PRINT_STRING          ,
  GROVE_CHARACTER_DISPLAY_PRINT_CHAR_ARRAY      ,
  GROVE_CHARACTER_DISPLAY_PRINT_CHAR            ,
  GROVE_CHARACTER_DISPLAY_PRINT_UCHAR_INT_PAIR  ,
  GROVE_CHARACTER_DISPLAY_PRINT_INT_PAIR        ,
  GROVE_CHARACTER_DISPLAY_PRINT_UINT_INT_PAIR   ,
  GROVE_CHARACTER_DISPLAY_PRINT_LONG_INT_PAIR   ,
  GROVE_CHARACTER_DISPLAY_PRINT_ULONG_INT_PAIR  ,
  GROVE_CHARACTER_DISPLAY_PRINT_DOUBLE_INT_PAIR ,
  GROVE_CHARACTER_DISPLAY_PRINT_PRINTABLE       ,
  GROVE_CHARACTER_DISPLAY_PRINT_CUMTOM_CHAR
} displayCommands_t;


class SDC_GroveLCD_RGB_BLackLight : public SDC_CharacterDisplay {
public:
  SDC_GroveLCD_RGB_BLackLight(uint8_t columns, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX);
  //bool  begin(uint8_t columns, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
  bool  begin(int32_t num = SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int   SetState(character_display_state_t *state, int32_t num = SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int  getDeviceInfo(device_info_t * info, int32_t num = SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID);
  int  GetState(character_display_state_t *state, int32_t num);
private:
  uint8_t columns;
  uint8_t rows;
  uint8_t charsize;
  character_display_state_t displayState;
  //SDC_CharacterDisplay _super;
  rgb_lcd _grove;
  void testCreateChar(void);
};


#endif /* __SDC_GROVELCD_RGB_BACKLIGHT_H__ */
