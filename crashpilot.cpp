#include "crashpilot.h"

uint8_t findloser(){
  for (uint8_t button=0; button<NObuttons; button++){
    if (digitalRead(BUTTONS[button])){
      return button;
    }
  }
  return 99; // couldn't find loser
}

uint16_t updateDelaytime(float delaytime){ 
  if (delaytime<=100){
    return 100;
  }
  
  //delaytime = delaytime-25;
  delaytime = delaytime - (delaytime/9000)*delaytime + 1; // update in inverse exponentioal way
  
  return delaytime;
}

void crashpilot_game(uint8_t players[], uint8_t NOplayers){  
  //Serial.begin(115200)
  setAll(LOW);
  uint8_t allbuttons[5] = {BUTTONS[0], BUTTONS[1], BUTTONS[2], BUTTONS[3], BUTTONS[4]};

  float delaytime = 1000.0;
  uint16_t restdelay = 0;
  uint8_t loser = 99;
  while(loser == 99){ // continue until we have an actual loser
    for(uint8_t player=0; player<NObuttons; player++){ // we loop over all buttons, eventhough a button can be unplayed
      Serial.println(delaytime);

      // do the timing led
      digitalWrite(LEDS[player], HIGH);
      restdelay = updatingDelay((uint16_t)delaytime, allbuttons, NObuttons); // delay while checking buttons (delaytime is casted from float to unsigned int 16 bit)

      // if a button was pressed within time (either the correct person or a wrong person)
      if (restdelay>0){
        if (digitalRead(BUTTONS[player]) == LOW){ // if it was not the person that was supposed to press
          loser = findloser();
          break;
        }
        else{ // it was pressed in time, continue the delay
          delay(restdelay);
        }
      }
      // else the button was not pressed in time
      else{
        if (players[player] == true){ // if the button was being played
          loser = player;
          break;
        }
      }

      // update the delay and move to next player
      digitalWrite(LEDS[player], LOW);
      delaytime = updateDelaytime(delaytime);
    }
    // loser = 99; // never stop
  }

  // we have a loser
  setAll(LOW);
  blinkLed(LEDS[loser], 5, 500); // blink loser
}

void crashpilot(){
  setAll(LOW);
  digitalWrite(LED_GREEN, HIGH); // mr. green always joins

  uint8_t players[5] = {true, false, false, false, false}; // first, only mr. green is in
  uint8_t NOplayers = 1;
  while(digitalRead(BUTTON_GREEN) == LOW){ // wait for start signal
    
    delay(10); // anti crash
    
    for (uint8_t button=1; button<NObuttons; button++){
      if (digitalRead(BUTTONS[button]) == HIGH){ // if a player is joining
        digitalWrite(LEDS[button], HIGH);
        players[button] = true;
        NOplayers++;
      }
    }
  }
  while(digitalRead(BUTTON_GREEN) == HIGH){ // wait untill start button is let go off
    delay(10); // anti crash
  }
  //celebrate();
  
  // start the game
  crashpilot_game(players, 5);
}
