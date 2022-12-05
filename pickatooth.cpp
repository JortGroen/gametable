#include "pickatooth.h"

void pickatooth(){
  setAll(LOW);
  
  uint32_t seed = millis();
  randomSeed(seed);
  uint8_t loser = random(0, NOleds); 
   
  uint8_t button = 0;
  for (uint8_t turn=0; turn<NOleds-1; turn++){
    button = waitforpress();
    if (button == loser){ // ah oh, you lost
      blinkLed(LEDS[loser], 10, 500);
      return;
    }
    digitalWrite(LEDS[button], HIGH);
    
    while(digitalRead(BUTTONS[button]) == HIGH){
      delay(10);
    }
  }

  // FINISH IT!
  while (button!=loser){
    button = waitforpress();
  }
  digitalWrite(LEDS[loser], HIGH);

  // YOU FINISHED THE GAME
  celebrate();
}
