/*
 * Keypad_TVRemote.pde: 自製紅外線電視遙控器(使用 Keypad)
 */
#include <Keypad.h>                      // 引用 Keypad 函式庫
#include <IRremote.h>                    // 引用 IRRemote 函式庫

const byte ROWS = 4;                     // 3x4 Keypad
const byte COLS = 3;

char keys[ROWS][COLS] = {                // 定義 Keypad 的按鍵
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// 定義 Keypad 連到 Arduino 的接腳
// Keypad 腳位佈局:
//      Rows: 2, 7, 6, 4
//      Cols: 3, 1, 5
byte rowPins[ROWS] = {11, 6, 7, 9};       // 連到 Keypad 的 4 個 Rows: Row0, Row1, Row2, Row3
byte colPins[COLS] = {10, 12, 8};         // 連到 Keypad 的 3 個 Columns: Column0, Column1, Column2

/*
// Keypad 腳位佈局:
//      Rows: 4, 5, 6, 7
//      Cols: 1, 2, 3
byte rowPins[ROWS] = {9, 8, 7, 6};       // 連到 Keypad 的 4 個 Rows: Row0, Row1, Row2, Row3
byte colPins[COLS] = {12, 11, 10};       // 連到 Keypad 的 3 個 Columns: Column0, Column1, Column2
*/

// 建立 Keypad 物件
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// 紅外線編碼對應表
// 這是我電視遙控器的紅外線編碼，記得換成你的紅外線編碼
long irKeyCodes[12] = {
  0x4FB42BD, 0x4FBC23D, 0x4FBF00F,       // 對應 Keypad 的 '1', '2', '3'
  0x4FB7887, 0x4FBB847, 0x4FB38C7,       // 對應 Keypad 的 '4', '5', '6'
  0x4FB18E7, 0x4FBA25D, 0x4FB32CD,       // 對應 Keypad 的 '7', '8', '9'
  0x4FB30CF, 0x4FB6A95, 0x4FBA05F        // 對應 Keypad 的 '*', '*', '#'
};

IRsend irsend;                           // 定義 IRsend 物件來發射紅外線訊號

void setup()
{
  Serial.begin(9600);                    // 開啟 Serial port, 通訊速率為 9600 bps
}

void loop() 
{
  char key = keypad.getKey();
  byte irKeyIndex;
  
  // 檢查 Keypad 是否有被按下
  // 有的話，key 會是非 NO_KEY 的值
  if (key != NO_KEY){    
    Serial.println(key);                // 把按鍵印到 Serial Port
    
    // 計算 irKeyCodes 的索引
    switch (key) {
      case '*':
        irKeyIndex = 9;                 // 降低音量 (volume-)
        break;
      case '0':
        irKeyIndex = 10;                // 按鍵 '0'
        break;
      case '#':                         // 提高音量 (volume+)
        irKeyIndex = 11;
        break;
      default:
        irKeyIndex = key - '1';         // 按鍵 1 ~  9
    }
    
    irsend.sendNEC(irKeyCodes[irKeyIndex], 32);        // 發射紅外線訊號
  }  
}

