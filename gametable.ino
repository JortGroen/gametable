// WARNING: when initializing serial connection, leds white and red are frozen on!

#include "gametable.h"
#include "roulette.h"
#include "pickatooth.h"

uint8_t game;

void setup() {
  tableinit();
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
    case 3: celebrate();
      break;

    // yellow button
    case 4: 
      uint8_t button = waitforpress();
      if(button == BUTTON_RED){
        digitalWrite(LED_RED, HIGH);
        delay(1000);
      }
      break;
  }
}
