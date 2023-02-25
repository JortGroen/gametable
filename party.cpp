#include "party.h"

void party(){
  uint8_t allbuttons[5] = {BUTTONS[0], BUTTONS[1], BUTTONS[2], BUTTONS[3], BUTTONS[4]};
  uint32_t seed = millis();
  randomSeed(seed);
  //Serial.begin(115200)
  uint16_t delaytime = 500;
  bool go = true;
  while(go == true){
    for (uint8_t led=0; led<NOleds; led++){
      bool onoff = random(0, 2); // decide wether it should be on or off
      digitalWrite(LEDS[led], onoff); // set the led to what we want it
    }
    uint16_t restdelay = updatingDelay(delaytime, allbuttons, NObuttons);
    if (restdelay > 0){ // if a button is pressed
      go = false;
    }
  }
}
