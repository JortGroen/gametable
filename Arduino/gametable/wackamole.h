#ifndef WACKAMOLE
#define WACKAMOLE

// INCLUDES
#include <Arduino.h>
#include "gametable.h"

uint8_t findmealoser();
uint16_t updateDelaytime(uint16_t delaytime);
void wackamole_game(uint8_t players[], uint8_t NOplayers);
void wackamole();

#endif
