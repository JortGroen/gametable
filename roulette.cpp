#include "roulette.h"

void celebration(uint8_t led){
  for (uint8_t k=0; k<10; k++){
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(500);
  }
}

void roulette(){
  uint32_t seed = millis();
  randomSeed(seed);
  //Serial.begin(115200);
  //Serial.println(seed);

  uint8_t winner = random(0, NOleds);  
  uint16_t maxdelay = 1000;

  uint8_t leds[5] = {LED_GREEN, LED_YELLOW, LED_RED, LED_BLUE, LED_WHITE};
  float i=50;
  uint8_t j=0;
  while(true){
    digitalWrite(leds[j], HIGH);
    delay(round(i));
    if (i>= maxdelay and j==winner){
      delay(1000);
      return;
    }
    digitalWrite(leds[j], LOW);
    i = i*1.1;
    j = j+1;
    if (j == NOleds){
      j = 0;
    }
  }
  
}
