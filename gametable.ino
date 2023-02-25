// WARNING: when initializing serial connection, leds white and red are frozen on!
// WARNING: when doing fast loops, small delays have to be added! otherwise the chip will crash.

#include "gametable.h"
#include "roulette.h"
#include "pickatooth.h"
#include "crashpilot.h"
#include "party.h"

uint8_t game;

void setup() {
  tableinit();
  delay(500);
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(100);
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
}

void loop() {  
  game = menu();
  delay(2000);
  setAll(LOW);
  
  switch (game){
    // green button
    case 0: roulette();
      break;
      
    // white button
    case 1: roulette2();
      break;
      
    // blue button
    case 2: pickatooth();
      break;

    // red button
    case 3: crashpilot();
      break;

    // yellow button
    case 4: party();
      break;
  }
}
