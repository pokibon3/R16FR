// 2023-07-08 ja1aoq
#include "ch32v003fun.h"
#include "ch32v003_GPIO_branchless.h"
#include <stdio.h>
#define SPEED   60           // default time
#define DUTY	512
#define PC4		4

const  char  table[][8] = {
	"A.-",
	"B-...",
	"C-.-.",
	"D-..",
	"E.",
	"F..-.",
	"G--.",
	"H....",
	"I..",
	"J.---",
	"K-.-",
	"L.-..",
	"M--",
	"N-.",
	"O---",
	"P.--.",
	"Q--.-",
	"R.-.",
	"S...",
	"T-",
	"U..-",
	"V...-",
	"W.--",
	"X-..-",
	"Y-.--",
	"Z--..",
	"1.----",
	"2..---",
	"3...--",
	"4....-",
	"5.....",
	"6-....",
	"7--...",
	"8---..",
	"9----.",
	"0-----",
/*
	"..-.-.-",
	",--..--",
	":---...",
	"?..--..",
	"'.----.",
	"--....-",
	"(-.--.",
	")-.--.-",
	"/-..-.",
	"=-...-",
	"+.-.-.",
	"\".-..-.",
	"*-..-",
	"@.--.-."
*/
};

void  short_beep()
{
	GPIO_tim1_analogWrite(PC4, DUTY);
	Delay_Ms(SPEED);
	GPIO_tim1_analogWrite(PC4, 0);
	Delay_Ms(SPEED);
}

void  long_beep()
{
	GPIO_tim1_analogWrite(PC4, DUTY);
	Delay_Ms(SPEED * 3);
	GPIO_tim1_analogWrite(PC4, 0);
	Delay_Ms(SPEED);
}

void  morse_chr(char chr)
{
  static  int16_t cnt, i;

  if (chr == ' ') {
    Delay_Ms(SPEED * 5);
    return;
  }

  for (cnt = 0; cnt < 36; cnt++) {
    if (table[cnt][0] == chr) {
      for (i = 1; table[cnt][i] != 0x00; i++) {
        if (table[cnt][i] == '.')
          short_beep();
        else
          long_beep();
      }
      Delay_Ms(SPEED * 3);
      return;
    }
  }
}

void  morse_str(char* str)
{
  while (*str != 0x00) {
    morse_chr(*str);
    str++;
  }
}

void setup()
{
	SystemInit();

	//SetupUART( UART_BRR );
	GPIO_port_enable(GPIO_port_C);
	// GPIO C0 - C7 Push-Pull
	GPIO_port_pinMode(GPIO_port_C, GPIO_pinMode_O_pushPullMux, GPIO_Speed_10MHz);
	GPIO_tim1_map(GPIO_tim1_output_set_0__D2_A1_C3_C4__D0_A2_D1);
	GPIO_tim1_init();
	TIM1->PSC = (uint16_t)0x40;
	//GPIO_tim1_enableCH(3);
	GPIO_tim1_enableCH(4);
    morse_str("HI");
    Delay_Ms(500);
}


int main() 
{
	setup();	
	while (1) {
	    morse_str("VVV DE JA9OIR");
	    Delay_Ms(500);
	}
}
