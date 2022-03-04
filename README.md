# Simple Device Control library
## ライブラリの親子関係
クラスの親子関係で各インクルードファイルを表示する以下のようになる．
```
SimpleDeviceControl.h
    SDC_SoundDevice.h
        SDC_ToneDevice.h
    SDC_n_Digit_LED.h
        SDC_TM1637.h
    SDC_Led.h
        SDC_SimpleLed.h
        SDC_Grove_LED_Bar.h
        SDC_NeoPixel.h
        SDC_Grove_Chainable_RGB_LED.h
    SDC_CharacterDisplay.h
        SDC_GroveLCD_RGB_BackLight.h
```

## 添付のサンプルプログラムをクラスの親子関係で木構造で表示すると以下の通り．
```
Sound
    SDC_Grove_Speaker
n_Digit_LED
    TM1637
LED
    Mono_LED
        SDC_SimpleLed
        SDC_Grove_LED_Bar
    RGB_LED
        SDC_NeoPixel
        SDC_Grove_Chainable_RGB_LED
Character_Display
    Grove-LCD_RGB_Backlight_Hello_world
```

# 共通
## 全クラスに存在する関数
```
bool  begin( ... );
int   getDeviceInfo( ... );
int   SetState( ... );
```

## 一部のクラスでしか意味がない関数
以下のメンバ関数は一部のクラスでしか意味がないが，全クラスに実装されており，返り値として``SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION``を返す．
```
int   ApplyState( ... );
```
次の関数は全クラスに存在するが，全クラスで引数の型が異なるため，複数のデバイスに適用可能なプログラムを作る場合は注意が必要．
```
int   GetState( ... );
```

## ごく一部のクラスにしか実装されていない関数
以下の関数はごく一部のクラスにしか実装されていないため，複数のデバイスに適用可能な1つのプログラムを作成する場合，#ifdefでの切り替えが必要になる．
```
bool  config( ... );
```

# SDC_ToneDevice
## 音データ
``SimpleDeviceControl.h``で音のデータは以下のように定義されています．
```
#define TONE_ARRAY_SIZE 32

typedef struct {
  unsigned int data_size;
  unsigned int freq[TONE_ARRAY_SIZE];
  unsigned int duration[TONE_ARRAY_SIZE];
  unsigned long rest[TONE_ARRAY_SIZE];
} toneState_t;
```
1つの音データ変数に最大32個の音データを格納することができます．なお，各メンバの意味は以下のとおりです．
- ``data_size`` : 何個の音データが格納されているかをしめす値
- ``freq[]`` : 周波数
- ``duration[]`` : 音を出す時間
- ``rest[]`` : 次の音を出すまでの休止時間

## toneデバイス作成 ``SDC_ToneDevice(uint8_t output_pin, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX)``
本ライブラリでは，スピーカー等のデバイスが数珠つなぎで接続された1つのデバイスを想定していないため，第2引数は無視しています．
また，``SIMPLE_DEVICE_CONTROL_DEV_ID_MAX``は1と定義されています．

第1引数はスピーカー等のデバイスを接続しているデジタル端子のピン番号を指定します．

### 使い方の例
```
SDC_ToneDevice tone_device(SPEAKER_PIN);
```

## 初期化 ``bool begin(int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``

オブジェクトを生成する時と同じく，デバイスは1つである前提なので，第2引数は``0 (SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``を想定しています．
もし，``0``以外の値の場合は何もせずに``SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID``を返します．

### 使い方の例
```
tone_device.begin();
```

## 音の再生 ``int   SetState(toneState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``
オブジェクトを生成する時と同じく，デバイスは1つである前提なので，第2引数は``0 (SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``を想定しています．
もし，``0``以外の値の場合は何もせずに``SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID``を返します．


| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 再生成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数のstateが``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``0``以外 |


### 使い方の例
```
toneState_t toneState;
：
(略:音データをtoneStateに格納する処理)
：
tone_device.SetState(&toneState,0);
```

## デバイス情報の取得 ``int  getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``
第1引数がNULLの場合，第2引数が0以外の場合はなにもせずにエラーを返します．正常な場合は，第1引数で与えられた構造体変数にデバイスの情報を格納します．


| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数が``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``0``以外 |


| メンバ | 値 | 意味 |
|---|---|---|
| category | SDC_DEVICE_CATEGORY_SOUND_DEVICE | 音関係のデバイス |
| type | SDC_DEVICE_TYPE_TONE_DEVICE | スピーカーなど |
| version | SDC_TONE_DEVICE_VERSION | バージョン番号 |
| tone_device.apply | SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION | ``setState()``で音を再生するため，``applyState()``は不要 |

### 使い方の例
```
device_info_t info;
tone_device.getDeviceInfo(&info, 0);
```


# TM1637

## 設定用データ型
```
typedef struct {
  uint8_t brightness;
  bool colon;
  int8_t digit[MAX_DIGITS];
} digit_led_state_t;
```
- ``brightness`` : 0から255のLEDの明るさ
- ``colon`` : 記号(コロン)のON/OFF
- ``digit[]`` : 各桁の数字

## オブジェクトの作成 ``SDC_TM1637(uint8_t clk_pin, uint8_t data_pin, int32_t deviceID=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX)``
本ライブラリでは，デバイスが数珠つなぎで接続されたデバイスを想定していないため，第3引数は無視しています．
また，``SIMPLE_DEVICE_CONTROL_DEV_ID_MAX``は1と定義されています．

第1, 第2引数はデバイスを接続しているデジタル端子のピン番号を指定します．

### 使い方の例
```
#define CLK 4
#define DIO 5
SDC_TM1637 tm1637(CLK,DIO);
```


## 初期化 ``bool begin(int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``

オブジェクトを生成する時と同じく，デバイスは1つである前提なので，引数は``0 (SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``を想定しています．
もし，``0``以外の値の場合は何もせずに``SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID``を返します．

### 使い方の例
```
if (!tm1637.begin()) {
  Serial.println("setup n digit led failure.");
}
```

## 設定 ``int SetState(digit_led_state_t *state, int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``
オブジェクトを生成する時と同じく，デバイスは1つである前提なので，第2引数は``0 (SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``を想定しています．
もし，``0``以外の値の場合は何もせずに``SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID``を返します．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数のstateが``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``0``以外 |

### 使い方の例
```
digit_led_state_t state;
：
(略:データをstateに格納する処理)
：
tm1637.SetState(&state);
```


## デバイス情報取得 ``void  getDeviceInfo(device_info_t * info, int32_t id=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``
第1引数がNULLの場合，第2引数が0以外の場合はなにもせずにエラーを返します．正常な場合は，第1引数で与えられた構造体変数にデバイスの情報を格納します．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数が``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``0``以外 |

| メンバ | 値 | 意味 |
|---|---|---|
| category | SDC_DEVICE_CATEGORY_N_DIGIT_LED | N桁数字表示LED |
| type | SDC_DEVICE_TYPE_TM1637 | TM1637 |
| version | SDC_TONE_DEVICE_VERSION | バージョン番号 |
| digitLedType.apply | SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION | ``setState()``で設定するため，``applyState()``は不要 |
| digitLedType.digits | MAX_DIGITS(=4) | 4桁 |
| digitLedType.symbols | MAX_SYMBOLS(=1) | 1つ(コロンのみ) |

### 使い方の例
```
device_info_t info;
tm1637.getDeviceInfo(&info, 0);
```

# SDC_SimpleLed
## 設定用データ型
```
typedef struct {
  color_t   color;
  uint8_t  brightness;
} ledState_t;
```
単色のLEDを想定しているため，``brightness``のみが意味を持ちます．

## デバイス用オブジェクト生成 ``SDC_SimpleLed(uint8_t led_pin, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX)``
本ライブラリでは，デバイスが数珠つなぎで接続されたデバイスを想定していないため，第2引数は無視しています．
また，``SIMPLE_DEVICE_CONTROL_DEV_ID_MAX``は1と定義されています．

第1引数はデバイスを接続している端子のピン番号を指定します．

### 使い方の例
```
#define LED_PIN 2
SDC_SimpleLed led(LED_PIN );
```

## ピン端子設定 ``bool config(uint8_t type=PIN_TYPE_PMW)``

| 値 | 意味 |
|---|---|
| PIN_TYPE_ANALOG | アナログ端子 |
| PIN_TYPE_PMW | PMW対応デジタル端子 |
| PIN_TYPE_NO_PMW | PMW非対応デジタル端子 |

引数が上の表のいずれかに収まらない場合はfalseを返します．

### 使い方の例
```
led.config(PIN_TYPE_PMW);
```

## 初期化 ``bool begin(int32_t num=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX)``

オブジェクトを生成する時と同じく，デバイスは1つである前提なので，引数は``0 (SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``を想定しています．
もし，``0``以外の値の場合は何もせずに``SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID``を返します．

### 使い方の例
```
led.begin();
```

## 状態設定 ``int SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX)``

オブジェクトを生成する時と同じく，デバイスは1つである前提なので，第2引数は``0 (SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``を想定しています．
もし，``0``以外の値の場合は何もせずに``SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID``を返します．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数のstateが``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``0``以外 |

### 使い方の例
以下のコードは輝度を8単位で変えながらLEDを点滅する事例になっています．
```
ledState_t state;
for (int i=0; i< 256; i+=8) {
    Serial.print("Brightness = ");Serial.println(i);
    state.brightness=i;
    led.SetState(&state);
    delay(INTERVAL);
    Serial.println("LED Off");
    state.brightness=0;
    led.SetState(&state);
    delay(INTERVAL);
}
```

## デバイス情報取得 ``int getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEV_ID_MAX)``
第1引数がNULLの場合，第2引数が0以外の場合はなにもせずにエラーを返します．正常な場合は，第1引数で与えられた構造体変数にデバイスの情報を格納します．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数が``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``0``以外 |

| メンバ | 値 | 意味 |
|---|---|---|
| category | SDC_DEVICE_CATEGORY_LED | LED |
| type | SDC_DEVICE_TYPE_SINGLE_MONO_LED | 単色の単独LED |
| version | SDC_SIMPLE_LED_VERSION | バージョン番号 |
| ledType.apply | SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION | ``setState()``で設定するため，``applyState()``は不要 |
| ledType.brightnessDeps | 8 | 明度 255段階 (8bit値) |
| ledType.color | 0 | 単色 |

### 使い方の例
```
device_info_t info;
led.getDeviceInfo(&info, 0);
```

# SDC_Grove_LED_Bar
## 設定用データ型
```
typedef struct {
  color_t   color;
  uint8_t  brightness;
} ledState_t;
```
単色のLEDを想定しているため，``brightness``のみが意味を持ちます．

## デバイス用オブジェクト生成 ``SDC_GroveLedBar(uint8_t clk_pin, uint8_t data_pin, bool reverse=false, int32_t type = LED_BAR_10)``

Seeed Studioが提供する[公式ライブラリ](https://github.com/Seeed-Studio/Grove_LED_Bar)のラッパとして実装されているため，第4引数に[公式ライブラリ](https://github.com/Seeed-Studio/Grove_LED_Bar)で用いるデバイスの種類を識別するための情報を取ります．

| 値 | 実際のデバイス |
|---|---|
| LED_BAR_10 | [Grove LED Bar](https://wiki.seeedstudio.com/Grove-LED_Bar/) |
| LED_CIRCULAR_24 | [Grove - Circular LED](https://www.seeedstudio.com/Grove-Circular-LED.html) |

引数を省略した場合は，[Grove LED Bar](https://wiki.seeedstudio.com/Grove-LED_Bar/)が指定されたとみなして動作します．

第1,2引数はデバイスを接続している端子のピン番号を指定します．第3引数は表示の向きを逆方向にするか否かを指定するもので，``true``の場合は逆方向に表示されます．

### 使い方の例
```
SDC_GroveLedBar led=SDC_GroveLedBar(7, 6, true,LED_BAR_10 );
```

## 初期化 ``bool begin(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``

引数がデバイスのLED数より大きい場合，上のオブジェクト生成の第4引数に不正な値を指定した場合はfalseになります．

### 使い方の例
```
if (!led.begin()) {
    Serial.println("init led fail");
    while(true){}
} else {
    Serial.println("init led success");
}
```

## 状態設定 ``int SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数のstateが``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``SDC_GROVE_LED_BAR_LED_MAX``より大きい |

### 使い方の例
下の例はLED barの全てのLEDを明度を変えながら点灯する例になっています．
```
ledState_t state;
for (int i=0;i<(SDC_GROVE_LED_BAR_LED_MAX+1);i++){
    state.brightness=0;
    led.SetState(&state, i);
}
```

## 状態設定の適用 ``int ApplyState(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``
この機能は存在しないため，意味はありませんが，``ApplyState()``が存在しない他のクラスと違い，デバイス数が1ではないため，
引数をチェックする実装が異なっています．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION | サポートしていない機能 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``SDC_GROVE_LED_BAR_LED_MAX``より大きい |

### 使い方の例
```
led.ApplyState(0);
```

## デバイス情報の取得 ``int getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数が``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が``SDC_GROVE_LED_BAR_LED_MAX``より大きい |


| メンバ | 値 | 意味 |
|---|---|---|
| category | SDC_DEVICE_CATEGORY_LED | LED |
| type | SDC_DEVICE_TYPE_GROVE_LED_BAR | [Grove LED Bar](https://wiki.seeedstudio.com/Grove-LED_Bar/) |
| version | SDC_GROVE_LED_BAR_VERSION | バージョン番号 |
| ledType.apply | SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION | ``setState()``で設定するため，``applyState()``は不要 |
| ledType.brightnessDeps | 8 | 明度 255段階 (8bit値) |
| ledType.color | 0 | 単色 |
| info->device_num | 9 | 9個 |

### 使い方
```
device_info_t info;
led.getDeviceInfo(&info, 0);
```

# SDC_NeoPixel

## 設定用データ型

```
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
  color_t   color;
  uint8_t  brightness;
} ledState_t;
```

本ライブラリは，[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)のラッパの形式になっています．

フルカラーLEDの状態は上の型で定義されており，RGBもしくはRGB+alphaで色を指定する形式になっていますが，[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)はRGBAをサポートしていないので，RGBのみが利用できます．
一方，[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)はRGBWが利用できますが，本ライブラリはRGBWをサポートしていません．

## デバイス用オブジェクト生成 ``SDC_NeoPixel(uint8_t pin, neoPixelType type=NEO_GRB + NEO_KHZ800, int32_t deviceNum = SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``

[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)がサポートしているデバイス(LED)は，1つのピンに数珠つなぎで複数のLEDを接続して個別に制御することが可能になっているので，第1引数でピン番号，接続しているデバイスの数を第3引数で指定します．

第2引数は[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)に渡す，デバイスのタイプを示す値になりますが，詳細は[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)を参照してください．

### 使い方の例
```
#define LED_PIN 12
#define NUM_OF_LED 1
#define NEO_PIXEL_TYPE NEO_RGB + NEO_KHZ800
SDC_NeoPixel led(LED_PIN, NEO_PIXEL_TYPE, NUM_OF_LED);
```

## 初期化 ``bool  begin(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``
[Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)が対象にしているデバイスは，1つのピンに複数のLEDがぶら下がっている場合に，1つづつ初期化処理をすることはできないため，引数は無視しています．ただし，引数で指定した値がLED数より大きい場合はエラーとなります．

### 使い方の例
```
led.begin();
```

## 状態の取得 ``int   GetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``

引数で指定された番号のLEDの状態(色と明るさ)を取得するAPIです．デバイス番号は0から数えるため，1個しかデバイスがつながっていない場合は0を指定することになります．本クラスのオブジェクト生成の時は1以上であるため注意してください．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数のstateが``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が接続されているデバイス数より大きい |

### 使い方の例
```
#define NUM_OF_LED 1
led.GetState(&state, (NUM_OF_LED-1));
```

## 状態の指定 ``int   SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``
第1引数は色と明るさ，第2引数で色を設定するLEDの番号を指定します．ただし，本APIを実行しただけでは対象のデバイスの状態は変わりません．``ApplyState()``の実行が必要になります．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数のstateが``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が接続されているデバイス数より大きい |

### 使い方の例
```
#define NUM_OF_LED 1
ledState_t state;
state.brightness=i;
state.color.rgb.red=r;
state.color.rgb.green=g;
state.color.rgb.blue=b;
if (SIMPLE_DEVICE_CONTROL_SUCCESS != led.SetState(&state, (NUM_OF_LED-1))) {
    Serial.println("set state to led fail");
}
```

## 状態の設定 ``int   ApplyState(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``
引数で指定した番号のLEDに設定した状態を反映させます．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 引数が接続されているデバイス数より大きい |

### 使い方の例
```
#define NUM_OF_LED 1
ledState_t state;
if (SIMPLE_DEVICE_CONTROL_SUCCESS != led.ApplyState((NUM_OF_LED-1))) {
    Serial.println("apply state to led fail");
}
```

## デバイス情報の取得 ``int  getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数が``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が接続されているデバイス数より大きい |

| メンバ | 値 | 意味 |
|---|---|---|
| category | SDC_DEVICE_CATEGORY_LED | LED |
| type | SDC_DEVICE_TYPE_GROVE_LED_BAR | [Grove LED Bar](https://wiki.seeedstudio.com/Grove-LED_Bar/) |
| version | SDC_GROVE_LED_BAR_VERSION | バージョン番号 |
| ledType.apply | SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION | ``setState()``で設定するため，``applyState()``は不要 |
| ledType.brightnessDeps | 8 | 明度 255段階 (8bit値) |
| ledType.color | RGB_LED | RGBカラー |
| info->device_num | － | 接続されているデバイス数(オブジェクト生成時に指定した値) |

### 使い方の例
```
#define NUM_OF_LED 1
device_info_t info;
led.getDeviceInfo(&info, (NUM_OF_LED-1));
```


# SDC_Grove_Chainable_RGB_LED

## 設定用データ型

```
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
  color_t   color;
  uint8_t  brightness;
} ledState_t;
```

本ライブラリは，[Grove - Chainable RGB LED](https://wiki.seeedstudio.com/Grove-Chainable_RGB_LED/)用のライブラリで，[ChainableLED](https://github.com/pjpmarques/ChainableLED)のラッパの形式になっています．

フルカラーLEDの状態は上の型で定義されており，RGBもしくはRGB+alphaで色を指定する形式になっていますが，[ChainableLED](https://github.com/pjpmarques/ChainableLED)はRGBAとbrightnessをサポートしていないので，RGBのみでbrightnessも指定する必要があります．


## デバイス用オブジェクト生成 ``SDC_Grove_Chainable_RGB_Led(uint8_t clk_pin, uint8_t data_pin, int32_t num = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX)``
第1,2引数でクロックピンとデータピンを指定し，第3引数で接続しているLEDの数を指定します．

### 使い方の例
```
#define NUM_LEDS  2
SDC_Grove_Chainable_RGB_Led leds(10, 11, NUM_LEDS);
```

## 初期化 ``bool  begin(int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``
[ChainableLED](https://github.com/pjpmarques/ChainableLED)は，
1つのピンに複数のLEDがぶら下がっている場合に，1つづつ初期化処理をすることはできないため，引数は無視しています．ただし，引数で指定した値がLED数より大きい場合はエラー(``false``)となります．

### 使い方の例
```
leds.begin();
```

## 設定 ``int   SetState(ledState_t *state, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``
第1引数の変数に色と明るさを指定し，第2引数でつないだLEDのうち何番目のLEDの色(と明るさ)を設定するかを指定します．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数のstateが``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が接続されているデバイス数より大きい |

### 使い方の例
```
#define NUM_LEDS  2
#define INTERVAL 500

state.color.rgb.red=r;
state.color.rgb.green=g;
state.color.rgb.blue=b;
for (int i=0; i< NUM_LEDS; i++) {
    if (SIMPLE_DEVICE_CONTROL_SUCCESS != leds.SetState(&state, i)) {
        Serial.print("set state to led No.");Serial.print(i);Serial.println(" fail.");
    }
    delay(INTERVAL);
}
```
## デバイス情報の取得 ``int  getDeviceInfo(device_info_t * info, int32_t num=SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_NUM)``

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数が``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が接続されているデバイス数より大きい |

| メンバ | 値 | 意味 |
|---|---|---|
| category | SDC_DEVICE_CATEGORY_LED | LED |
| type | SDC_DEVICE_TYPE_GROVE_CHAINABLE_RGB_LED | [Grove - Chainable RGB LED](https://wiki.seeedstudio.com/Grove-Chainable_RGB_LED/) |
| version | SDC_GROVE_CHAINALE_RGB_LED_VERSION | バージョン番号 |
| ledType.apply | SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION | ``setState()``で設定するため，``applyState()``は不要 |
| ledType.brightnessDeps | 1 | brightnessの指定はなし |
| ledType.color | RGB_LED | RGBカラー |
| info->device_num | － | 接続されているデバイス数(オブジェクト生成時に指定した値) |

### 使い方の例
```
device_info_t info;
leds.getDeviceInfo(&info, 0)
```


# SDC_GroveLCD_RGB_BackLight
## 設定用データ型
```
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
```

| コマンド | 引数 | 処理内容 |
|---|---|---|
| GROVE_CHARACTER_DISPLAY_CLEAR                 | なし                                                        | ディスプレイをクリア                                 |
| GROVE_CHARACTER_DISPLAY_OFF                   | なし                                                        | ディスプレイをOFF                                    |
| GROVE_CHARACTER_DISPLAY_ON                    | なし                                                        | ディスプレイをON                                     |
| GROVE_CHARACTER_DISPLAY_CURSOR_HOME           | なし                                                        | カーソルをホームポジションにセット                     |
| GROVE_CHARACTER_DISPLAY_CURSOR_NO_BLINK       | なし                                                        | カーソルをブリンクさせない                             |
| GROVE_CHARACTER_DISPLAY_CURSOR_BLINK          | なし                                                        | カーソルをブリンクさせる                               |
| GROVE_CHARACTER_DISPLAY_NO_CURSOR             | なし                                                        | カーソルを消す                                        |
| GROVE_CHARACTER_DISPLAY_CURSOR                | なし                                                        | カーソルを表示する                                    |
| GROVE_CHARACTER_DISPLAY_SCROLL_LEFT           | なし                                                        | 左スクロール                                          |
| GROVE_CHARACTER_DISPLAY_SCROLL_RIGHT          | なし                                                        | 右スクロール                                          |
| GROVE_CHARACTER_DISPLAY_LEFT_TO_RIGHT         | なし                                                        | 左から右へ表示                                        |
| GROVE_CHARACTER_DISPLAY_RIGHT_TO_LEFT         | なし                                                        | 右から左へ表示                                        |
| GROVE_CHARACTER_DISPLAY_AUTO_SCROLL           | なし                                                        | 自動スクロールする                                     |
| GROVE_CHARACTER_DISPLAY_NO_AUTO_SCROLL        | なし                                                        | 自動スクロールしない                                   |
| GROVE_CHARACTER_DISPLAY_RGB                   | state->rgb.red, state->rgb.green, state->rgb.blue           | バックライトの色を設定                                 |
| GROVE_CHARACTER_DISPLAY_SET_CURSOR            | state->position.x , state->position.y                       | カーソルのポジション設定                               |
| GROVE_CHARACTER_DISPLAY_CREATE_CHARACTER      | state->customChar.num, state->customChar.charMap            | bitmapで特殊文字を作成                                |
| GROVE_CHARACTER_DISPLAY_PRINT_FLASH_STRING    | state->flashString                                          | ``F()``マクロで作成した文字列を表示                    |
| GROVE_CHARACTER_DISPLAY_PRINT_CHAR_ARRAY      | state->charArray                                            | charの配列を表示                                      |
| GROVE_CHARACTER_DISPLAY_PRINT_CHAR            | state->character                                            | 1文字表示                                             |
| GROVE_CHARACTER_DISPLAY_PRINT_UCHAR_INT_PAIR  | state->uchar_int_pair.value, state->uchar_int_pair.format   | unsigned charをformatで指定した形式(HEX,BIN,DEC)で表示 |
| GROVE_CHARACTER_DISPLAY_PRINT_INT_PAIR        | state->int_pair.value, state->int_pair.format               | intをformatで指定した形式(HEX,BIN,DEC)で表示           |
| GROVE_CHARACTER_DISPLAY_PRINT_UINT_INT_PAIR   | state->uint_int_pair.value, state->uint_int_pair.format     | unsigned intをformatで指定した形式(HEX,BIN,DEC)で表示  |
| GROVE_CHARACTER_DISPLAY_PRINT_LONG_INT_PAIR   | state->long_int_pair.value, state->long_int_pair.format     | longをformatで指定した形式(HEX,BIN,DEC)で表示          |
| GROVE_CHARACTER_DISPLAY_PRINT_ULONG_INT_PAIR  | state->ulong_int_pair.value, state->ulong_int_pair.format   | unsigned longをformatで指定した形式(HEX,BIN,DEC)で表示 |
| GROVE_CHARACTER_DISPLAY_PRINT_DOUBLE_INT_PAIR | state->double_int_pair.value, state->double_int_pair.format | doubleをformatで指定した形式(HEX,BIN,DEC)で表示        |
| GROVE_CHARACTER_DISPLAY_PRINT_CUMTOM_CHAR     | state->customCharNum                                        | 作成済みの特殊文字を表示                               |

## デバイス用オブジェクト生成 ``SDC_GroveLCD_RGB_BLackLight(uint8_t columns, uint8_t rows, uint8_t charsize = LCD_5x8DOTS, int32_t deviceID = SIMPLE_DEVICE_CONTROL_DEV_ID_MAX)``
第1,2引数で表示可能な行と列を指定，第3引数で文字サイズを指定，第4引数はデバイス数ですが，数珠つなぎにはできないので内容は無視されます．

第3引数で指定可能な文字サイズは以下の2つ
- ``LCD_5x10DOTS`` : 縦10dot
- ``LCD_5x8DOTS``  : 縦8dot

### 使い方の例
```
SDC_GroveLCD_RGB_BLackLight lcd((uint8_t) 16, (uint8_t) 2, LCD_5x8DOTS);
```

## 初期化 ``bool  begin(int32_t num = SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``
[Grove - LCD RGB Backlight](https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/)は，数珠つなぎにはできないので内容は無視されます．ただし，引数が0以外だと何もせずに，``false``を返します．


### 使い方の例
```
if (!lcd.begin()) {
    Serial.println("setup n digit led failure.");
    while (true) {
        ;
    }
}
```

## 設定(と表示) ``int   SetState(character_display_state_t *state, int32_t num = SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``
第1引数の構造体でコマンドと引数を与えてバックライトの色設定や文字の表示等を行います．

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数のstateが``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が接続されているデバイス数より大きい |

### 使い方の例

#### 画面の初期化
```
state.command=GROVE_CHARACTER_DISPLAY_CURSOR_HOME;       // カーネルをホームポジションに移動
lcd.SetState(&state);
state.command=GROVE_CHARACTER_DISPLAY_CLEAR;             // 画面をクリア
lcd.SetState(&state);
state.command=GROVE_CHARACTER_DISPLAY_RGB;               // バックライトを青色に設定
state.rgb.red=0; state.rgb.green=0; state.rgb.blue=255;
lcd.SetState(&state);
```

#### カーソルの移動と数字の表示
```
state.command=GROVE_CHARACTER_DISPLAY_SET_CURSOR;       // カーソルを0,0(左下)に移動
state.position.x=0;state.position.y=0;
lcd.SetState(&state);
state.command=GROVE_CHARACTER_DISPLAY_PRINT_INT_PAIR;   // "123"を10進で表示
state.int_pair.value=123;
state.int_pair.format=DEC;
lcd.SetState(&state);
```

#### 特殊文字(ハート型)の登録
```
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

state.command=GROVE_CHARACTER_DISPLAY_CREATE_CHARACTER;
state.customChar.charMap=heart;
state.customChar.num=0;
lcd.SetState(&state);
```
上は，ハート型を0番のバッファに登録




## デバイス情報の取得 ``int  getDeviceInfo(device_info_t * info, int32_t num = SIMPLE_DEVICE_CONTROL_DEFAULT_DEV_ID)``

| 返り値 | 意味 |
|---|---|
| SIMPLE_DEVICE_CONTROL_SUCCESS | 成功 |
| SIMPLE_DEVICE_CONTROL_FAIL | 第1引数が``NULL``など不正な場合 |
| SIMPLE_DEVICE_CONTROL_UNSUPPORTED_DEV_ID | 第2引数が接続されているデバイス数より大きい |

| メンバ | 値 | 意味 |
|---|---|---|
| category | SDC_DEVICE_CATEGORY_CHARACTER_DISPLAY | 文字表示ディスプレイ |
| type | SDC_DEVICE_TYPE_16x2_CHRACTER_DISPLAY | [Grove - LCD RGB Backlight](https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/) |
| version | SDC_GROVE_LCD_RGB_VERSION | バージョン番号 |
| characterDisplayType.apply | SIMPLE_DEVICE_CONTROL_UNSUPPORTED_FUNCTION | ``setState()``で設定するため，``applyState()``は不要 |
| characterDisplayType.columns | SDC_GROVE_LCD_RGB_COLUMNS | 横の文字数 |
| characterDisplayType.lines | SDC_GROVE_LCD_RGB_LINES | 行数 |
| characterDisplayType.backLight | 2 | バックライトがRGBカラー |


### 使い方の例
```
device_info_t info;
lcd.getDeviceInfo(&info, 0)
```

<!--- コメント

## 動作検証

|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| [Uno R3][Uno]  |[Arduino][Arduino]|  ○    |      |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] |  ○    |      |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] | ○     |      |
|       | [Uno WiFi][UnoWiFi] |[Arduino][Arduino] | ○     | |
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] |   ×   |      |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino] |○||
|ESP8266|[ESPr developer][ESPrDev]| [スイッチサイエンス][SwitchScience] |||
|ESP32 | [ESPr one 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] |×|　|




[Adafruit Unified Sensor Driver][AdafruitUSD]
[Groveシールド][shield]
[Arduino M0 Pro][M0Pro]
[Arduino Due][Due]
[Arduino Uno R3][Uno]
[Arduino Mega2560 R3][Mega]
[Arduino Leonardo Ethernet][LeonardoEth]
[Arduino Pro mini 328 - 3.3V/8MHz][ProMini]
[ESpr one][ESPrOne]
[ESPr one 32][ESPrOne32]
[Grove][Grove]
[Seed Studio][SeedStudio]
[Arduino][Arduino]
[Sparkfun][Sparkfun]
[スイッチサイエンス][SwitchScience]
--->
