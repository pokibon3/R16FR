// SBlib.hpp : library fo soroban
// 2023.07.07  JA1AOQ/K.Ohe
//
#include <LEDMatrixDriver.hpp>

extern byte font[95][8];
extern void SBclear(void);
extern void SBclearAnimation(void);
extern void dispSoroban(uint8_t , int16_t);
extern void led_test(void);
extern void drawString(const char* , int, int, int);
extern void drawSprite( byte* , int, int, int, int);

extern LEDMatrixDriver lmd;
