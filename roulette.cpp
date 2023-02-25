#include "roulette.h"

void intro(){
  setAll(LOW);
  for (uint8_t i=0; i<NOleds; i++){
    digitalWrite(LEDS[i], HIGH);
    delay(500);
    digitalWrite(LEDS[i], LOW);
  }
  for (uint8_t i=NOleds; i>0; i--){
    digitalWrite(LEDS[i], HIGH);
    delay(500);
    digitalWrite(LEDS[i], LOW);
  }
}

void roulette(){
  //intro();
  //delay(1000);
  setAll(LOW);
  uint32_t seed = millis();
  randomSeed(seed);
  uint8_t winner = random(0, NOleds);  
  uint16_t maxdelay = 500;

  float i=50;
  uint8_t j=0;
  while(true){
    digitalWrite(LEDS[j], HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(round(i));
    if (i>= maxdelay and j==winner){
      delay(1000);
      digitalWrite(BUZZER, LOW);
      return;
    }
    digitalWrite(LEDS[j], LOW);
    digitalWrite(BUZZER, LOW);
    i = i*1.1;
    j = j+1;
    if (j == NOleds){
      j = 0;
    }
  }
}

void roulette2(){
  //intro();
  //delay(1000);
  uint32_t seed = millis();
  randomSeed(seed);
  setAll(HIGH);

  uint8_t winner;
  bool participants[5] = {true, true, true, true, true};
  for (uint8_t i=NOleds; i>1; i--){
    
    delay(random(2000, 10000)); // do random delay between 2 and 10 sec
    
    winner = random(0, i); // decide on next winner

    // check for all participants
    for (uint8_t participant=0; participant<=NOleds; participant++){

      // check if participant is still in the game
      if (!participants[participant]){
        continue;
      }

      // check if participant is the winner
      if (participant == winner){
        digitalWrite(LEDS[participant], LOW); // congrats you're out
        participants[participant] = false; // not joining next round
      }
    }
  }

  setAll(LOW);

  // find loser
  uint8_t loser = 0;
  for (uint8_t participant=0; participant<NOleds; participant++){
    if (participants[participant]){
      loser = participant;
      break;
    }
  }

  // blink loser
  for (uint8_t i; i<10; i++){
    digitalWrite(LEDS[loser], HIGH);
    delay(500);
    digitalWrite(LEDS[loser], LOW);
    delay(500);
  }
  
}
