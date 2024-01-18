// SBcalc.ino : soroban calculator
// 2023.07.07  JA1AOQ/K.Ohe
//
//#include <Key.h>
#include <Keypad.h>
#include "SBlib.hpp"

// for Custom Key Matrix
const byte ROWS = 4; //4行のキーパッドを使用
const byte COLS = 4; //4列のキーパッドを使用
  
char tenKeys[COLS][ROWS] = {
  {'C','*','/','-'},
  {'9','6','3','+'},
  {'8','5','2','='},
  {'7','4','1','0'},
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
// make keypad instance
Keypad customKeypad = Keypad( makeKeymap(tenKeys), rowPins, colPins, ROWS, COLS);

enum  STATE_SB {
  OP1 = 0,
  OP2,
  CALC,
};

static char     oprator;
static char     op1[9];
static int16_t  op1_num = 0;
static char     op2[9];
static int16_t  op2_num = 0;
static char     result[sizeof(long)*8+1];;
static int16_t  result_num = 0;
static int16_t  state = OP1;

void initParam()
{
  oprator    = 0;
  op1[0]     = 0x00;
  op1_num    = 0;
  op2[0]     = 0x00;
  op2_num    = 0;
  result[0]  = 0x00;
  result_num = 0;
  state =     OP1;
}

void setup(){
  // init the displa
  Serial.begin(9600);
  while(!Serial);
    
  lmd.setEnabled(true);
  lmd.setIntensity(2);   // 0 = low, 10 = high
  initParam();
  SBclear();
  drawString("CALC", 4, 0, 0);
  delay(2000);
  SBclearAnimation();
  delay(1000);
  SBclear();
}

void calc(char oprator)
{
  int  digit = 0;
  long ans = 0;

  switch(oprator) {
    case '*' :
      ans = atol(op1) * atol(op2);
      break;
    case '/' :
      ans = atol(op1) / atol(op2);
      break;
    case '+' :
      ans = atol(op1) + atol(op2);
      break;
    case '-' :
      ans = atol(op1) - atol(op2);
      break;
  }
  Serial.print("ans = "); Serial.println(ans);
  ltoa(ans, result, 10);
  //Serial.print("result = "); Serial.println(result);
  if (strlen(result) <= 8) {
    for (int x = 0; x < 8; x++) {
      digit =  result[x] - 0x30;
      if (digit < 0) {
        break;
      } else {
        //Serial.print("digit = "); Serial.println(digit);
        dispSoroban(digit, 24 + x);
      }
    }
  } else {
    drawSprite( font['E' - 32], 24, 0, 8, 8 );
    lmd.display();
  }
}

void loop()
{
  char customKey;

  customKey = customKeypad.getKey();//押されたキーを検出
  if (customKey){
    //Serial.print("key : "); Serial.println(customKey);
    switch(customKey) {
      case '/' :
      case '+' :
      case '-' :
      case '*' :
        if (state == OP1) {
          oprator = customKey;
          drawSprite( font[customKey - 32], 8, 0, 8, 8 );
          lmd.display();
          state = OP2;
        }
        break;
      case '=' :
        // calculation
        if (state == OP2) {
          calc(oprator);
          state = CALC;
        }
        break;
      case 'C' :
        // clear calc result
        initParam();
        SBclear();
        break;
      default :
        // pressed num kwy
        if (customKey >= '0' || customKey <= '9') {
          int16_t digit = customKey - 0x30;
          if (state == OP1 && op1_num < 8) {
            op1[op1_num] = customKey;
            dispSoroban(digit, op1_num);
            op1[++op1_num] = '\0';
          } else if (state == OP2 && op2_num < 8) {
            op2[op2_num] = customKey;
            dispSoroban(digit, 16 + op2_num);
            op2[++op2_num] = '\0';
          }
        } else {
          ;
        }
    }
  }
  delay(1); 
}
