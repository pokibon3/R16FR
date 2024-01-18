#include <Arduino.h>
#define LED_PIN PD6
//#define LED_PIN PC4
#define KEY_PIN PC1
#define SPEED   120           // default time

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
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(KEY_PIN, LOW);   
  delay(SPEED);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(KEY_PIN, HIGH);
  delay(SPEED);
}

void  long_beep()
{
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(KEY_PIN, LOW);   
  delay(SPEED * 3);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(KEY_PIN, HIGH);
  delay(SPEED);
}

void  morse_chr(char chr)
{
  static  int16_t cnt, i;

  if (chr == ' ') {
    delay(SPEED * 5);
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
      delay(SPEED * 3);
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
    pinMode(LED_PIN, OUTPUT);
//    pinMode(KEY_PIN, OUTPUT);
    pinMode(KEY_PIN, OUTPUT_OD);
    morse_str("HI");
    delay(1000);
}

void loop()
{
    morse_str("VVV DE JA9OIR");
    delay(1000);

}
