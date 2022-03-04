

#include "SDC_GroveLCD_RGB_BackLight.h"

character_display_state_t state;

SDC_GroveLCD_RGB_BLackLight lcd((uint8_t) 16, (uint8_t) 2, LCD_5x8DOTS);



byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};


void setup() 
{
  Serial.begin(9600);
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");

  if (!lcd.begin()) {
    Serial.println("setup n digit led failure.");
    while (true) {
      ;
    }
  }
  /*
   * custom charを登録する機能は、最初にしないとダメ
   */
  state.command=GROVE_CHARACTER_DISPLAY_CREATE_CHARACTER;
  state.customChar.charMap=heart;
  state.customChar.num=0;
  lcd.SetState(&state);
  delay(1000);
}

void loop()
{
  /* ================== page1 ================ */
  state.command=GROVE_CHARACTER_DISPLAY_CURSOR_HOME;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_CLEAR;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_RGB;
  state.rgb.red=0; state.rgb.green=0; state.rgb.blue=255;
  lcd.SetState(&state);
  /* ----------------------------------------- */
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=0;state.position.y=0;
  lcd.SetState(&state);
  //int val=(int)millis()/1000;
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_INT_PAIR;
  state.int_pair.value=123;
  state.int_pair.format=DEC;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=5;state.position.y=0;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_FLASH_STRING;
  state.flashString=F("XYZ");
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=9;state.position.y=0;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_CHAR_ARRAY;
  char tmp[4]="789";
  state.charArray=tmp;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=13;state.position.y=0;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_CHAR;
  state.character=(char) 'A';
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=0;state.position.y=1;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_UCHAR_INT_PAIR;
  state.uchar_int_pair.value=(unsigned char) 0;
  state.uchar_int_pair.format=DEC;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=2;state.position.y=1;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_UINT_INT_PAIR;
  state.uint_int_pair.value=(unsigned int) 12;
  state.uint_int_pair.format=DEC;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=5;state.position.y=1;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_LONG_INT_PAIR;
  state.long_int_pair.value=(long) 34;
  state.long_int_pair.format=DEC;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=8;state.position.y=1;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_ULONG_INT_PAIR;
  state.ulong_int_pair.value=(unsigned long) 56;
  state.ulong_int_pair.format=DEC;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=11;state.position.y=1;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_DOUBLE_INT_PAIR;
  state.double_int_pair.value=(double) 789;
  state.double_int_pair.format=DEC;
  lcd.SetState(&state);
  delay(10000);
  /* ================== page2 ================ */
  state.command=GROVE_CHARACTER_DISPLAY_CURSOR_HOME;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_CLEAR;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_RGB;
  state.rgb.red=0; state.rgb.green=255; state.rgb.blue=0;
  lcd.SetState(&state);
  /* ----------------------------------------- */
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=2;state.position.y=0;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_CUMTOM_CHAR;
  state.customCharNum=0;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;
  state.position.x=5;state.position.y=0;
  lcd.SetState(&state);
  state.command=GROVE_CHARACTER_DISPLAY_PRINT_FLASH_STRING;
  state.flashString=F("456");
  lcd.SetState(&state);
  delay(10000);
}
