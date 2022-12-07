#ifndef CRASHPILOT
#define CRASHPILOT

// INCLUDES
#include <Arduino.h>
#include "gametable.h"

uint8_t findloser();
uint16_t updateDelaytime(uint16_t delaytime);
void crashpilot_game(uint8_t players[], uint8_t NOplayers);
void crashpilot();

#endif
