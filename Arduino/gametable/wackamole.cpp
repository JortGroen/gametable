#include "wackamole.h"

uint8_t findmealoser(){
  for (uint8_t button=0; button<NObuttons; button++){
    if (digitalRead(BUTTONS[button])){
      return button;
    }
  }
  return 99; // couldn't find loser
}

uint16_t updateDelaytime_WM(float delaytime){ 
  if (delaytime<=100){
    return 100;
  }
  
  //delaytime = delaytime-25;
  delaytime = delaytime - (delaytime/18000)*delaytime + 1; // update in inverse exponentioal way
  
  return delaytime;
}

void wackamole_game(uint8_t players[], uint8_t NOplayers){  
  //Serial.begin(115200)
  setAll(LOW);
  uint8_t allbuttons[5] = {BUTTONS[0], BUTTONS[1], BUTTONS[2], BUTTONS[3], BUTTONS[4]};

  uint32_t seed = millis();
  randomSeed(seed);
  uint8_t hole = 0;
  uint8_t prev_hole = 0;
  float delaytime = 1000.0;
  uint16_t restdelay = 0;
  uint8_t loser = 99;
  while(loser == 99){ // continue until we have an actual loser
    prev_hole = hole;
    while(hole == prev_hole){
      hole = random(0, NOleds); 
      delay(50);
    }

    Serial.println(delaytime);

    // do the timing led
    digitalWrite(LEDS[hole], HIGH);
    restdelay = updatingDelay((uint16_t)delaytime, allbuttons, NObuttons); // delay while checking buttons (delaytime is casted from float to unsigned int 16 bit)

    // if a button was pressed within time (either the correct person or a wrong person)
    if (restdelay>0){
      if (digitalRead(BUTTONS[hole]) == LOW){ // if it was not the person that was supposed to press
        loser = findmealoser();
        break;
      }
      else{ // it was pressed in time, continue the delay
        digitalWrite(BUZZER, HIGH);
        delay(restdelay);
        digitalWrite(BUZZER, LOW);
      }
    }
    // else the button was not pressed in time
    else{
      if (players[hole] == true){ // if the button was being played
        loser = hole;
        break;
      }
    }

    // update the delay and move to next player
    digitalWrite(LEDS[hole], LOW);
    delaytime = updateDelaytime_WM(delaytime);

  }

  // we have a loser
  setAll(LOW);
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LEDS[loser], HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LEDS[loser], LOW);
  delay(500);
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LEDS[loser], HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LEDS[loser], LOW);
  delay(500);
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LEDS[loser], HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LEDS[loser], LOW);
  delay(500);
  //blinkLed(LEDS[loser], 5, 500); // blink loser
}

void wackamole(){
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
  wackamole_game(players, 5);
}
