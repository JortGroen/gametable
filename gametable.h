// WARNING: when initializing serial connection, leds white and red are frozen on!

#ifndef GAMETABLE
#define GAMETABLE

// INCLUDES
#include <Arduino.h>

// PINOUT
#define LED_GREEN 5 //D1
#define BUTTON_GREEN 4 //D2
#define LED_WHITE 1 // TX
#define BUTTON_WHITE 14 //D5
#define LED_BLUE 15 //D8
#define BUTTON_BLUE 13 //D7
#define LED_RED 3 //RX
#define BUTTON_RED 12 //D6
#define LED_YELLOW 0 //D3
#define BUTTON_YELLOW 16 //D0

// CONSTANTS
#define NOleds 5
#define NObuttons 5

// GLOBALS
extern bool buttonG;
extern bool buttonY;
extern bool buttonR;
extern bool buttonB;
extern bool buttonW;

// SETUP
void tableinit();

// HELPER FUNCTIONS
void setLeds(bool states[5]);
void setAll(bool state);
void updateButtons();
uint16_t updatingDelay(uint16_t t, uint8_t buttons[], uint8_t buttons_length);

// TEST FUNCTIONS
void test();
void test2();

#endif
