// WARNING: when initializing serial connection, leds white and red are frozen on!

#include "gametable.h"
#include "roulette.h"


void setup() {
  tableinit();
}

void loop() {
  roulette();
  //test();
  setAll(LOW);
  delay(2000);
}
