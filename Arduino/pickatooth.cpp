#include "pickatooth.h"

void pickatooth(){
  setAll(LOW);
  bool leds_status[5] = {false, false, false, false, false};
  
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

    if (leds_status[button] == true){ // you pressed an already pressed button
      turn--; // this turn doesn't count
    }
    leds_status[button] = true;
  }

  // FINISH IT!
  while (button!=loser){
    button = waitforpress();
  }
  digitalWrite(LEDS[loser], HIGH);

  // YOU FINISHED THE GAME
  celebrate();
}
