#include "SDC_GroveLCD_RGB_BackLight.h"

SDC_GroveLCD_RGB_BLackLight::SDC_GroveLCD_RGB_BLackLight(int32_t deviceID) {}

bool SDC_GroveLCD_RGB_BLackLight::begin(uint8_t columns, uint8_t rows, uint8_t charsize) {
  switch(charsize) {
    case LCD_5x8DOTS:
    case LCD_5x10DOTS:
      break;
    default: return false;
  }
  _grove.begin(columns, rows, charsize);
  return true;
}

int SDC_GroveLCD_RGB_BLackLight::SetState(character_display_state_t *state, int32_t num) {
  if (state==NULL) return SIMPLE_DEVICE_CONTROL_FAIL;
  switch(state->command) {
    case GROVE_CHARACTER_DISPLAY_CURSOR_HOME:_grove.home();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_CLEAR:_grove.clear();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_OFF:_grove.noDisplay();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_ON:_grove.display();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_CURSOR_NO_BLINK:_grove.noBlink();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_CURSOR_BLINK:_grove.blink();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_NO_CURSOR:_grove.noCursor();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_CURSOR:_grove.cursor();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_SCROLL_LEFT:_grove.scrollDisplayLeft();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_SCROLL_RIGHT:_grove.scrollDisplayRight();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_LEFT_TO_RIGHT:_grove.leftToRight();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_RIGHT_TO_LEFT:_grove.rightToLeft();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_AUTO_SCROLL:_grove.autoscroll();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_NO_AUTO_SCROLL:_grove.noAutoscroll();return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_RGB:_grove.setRGB(state->rgb.red, state->rgb.green, state->rgb.blue);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_SET_CURSOR:_grove.setCursor(state->position.x , state->position.y );return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_CREATE_CHARACTER:_grove.createChar(state->customChar.num, state->customChar.charMap);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_FLASH_STRING:_grove.print(state->flashString);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    //case GROVE_CHARACTER_DISPLAY_PRINT_STRING:_grove.print(state->string);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_CHAR_ARRAY:_grove.print(state->charArray);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_CHAR:_grove.print(state->character);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_UCHAR_INT_PAIR:_grove.print(state->uchar_int_pair.value, state->uchar_int_pair.format);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_INT_PAIR:_grove.print(state->int_pair.value, state->int_pair.format);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_UINT_INT_PAIR:_grove.print(state->uint_int_pair.value, state->uint_int_pair.format);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_LONG_INT_PAIR:_grove.print(state->long_int_pair.value, state->long_int_pair.format);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_ULONG_INT_PAIR:_grove.print(state->ulong_int_pair.value, state->ulong_int_pair.format);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_DOUBLE_INT_PAIR:_grove.print(state->double_int_pair.value, state->double_int_pair.format);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    //case GROVE_CHARACTER_DISPLAY_PRINT_PRINTABLE:_grove.print(state->printable);return SIMPLE_DEVICE_CONTROL_SUCCESS;
    case GROVE_CHARACTER_DISPLAY_PRINT_CUMTOM_CHAR:_grove.write(state->customCharNum);return SIMPLE_DEVICE_CONTROL_SUCCESS;
  }
  return SIMPLE_DEVICE_CONTROL_FAIL;
}

// 負 : 機能がない
// 0  : 全部のLEDに同じ値しかセットできない
// 1  : 個別の設定が可能
// 2  : apiで全体にまとめて設定ができる
void SDC_GroveLCD_RGB_BLackLight::getDeviceInfo(device_info_t * info) {
  info->type = SDC_DEVICE_TYPE_16x2_CHRACTER_DISPLAY;
  info->version = SDC_GROVE_LCD_RGB_VERSION;
  info->device_num = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX;
  info->category = SDC_DEVICE_CATEGORY_CHARACTER_DISPLAY;
  info->characterDisplayType.set =  0;  // 全部同じ値しかセットできない(というか1個しかないので意味はあまりない)
  info->characterDisplayType.apply = SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION; // setで適用してしまう
  info->characterDisplayType.columns=SDC_GROVE_LCD_RGB_COLUMNS;
  info->characterDisplayType.lines=SDC_GROVE_LCD_RGB_LINES;
  info->characterDisplayType.backLight=2; // バックライト 0: なし, 1:単色, 2:カラー
}
