// WARNING: when initializing serial connection, leds white and red are frozen on!

#ifndef GAMETABLE
#define GAMETABLE

#define VERSION_MINI true 

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
#define BUZZER 2 //D4 

// CONSTANTS
#define NOleds 5
#define NObuttons 5

#if VERSION_MINI
  const uint8_t LEDS[5] = {LED_GREEN, LED_BLUE, LED_RED, LED_WHITE, LED_YELLOW};
  const uint8_t BUTTONS[5] = {BUTTON_GREEN, BUTTON_BLUE, BUTTON_RED, BUTTON_WHITE, BUTTON_YELLOW};
#else
  const uint8_t LEDS[5] = {LED_GREEN, LED_YELLOW, LED_RED, LED_BLUE, LED_WHITE};
  const uint8_t BUTTONS[5] = {BUTTON_GREEN, BUTTON_YELLOW, BUTTON_RED, BUTTON_BLUE, BUTTON_WHITE};
#endif

#define BEEBSHORTD 100
#define BEEBLONGD 500

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
void blinkLed(uint8_t led, uint8_t quantity, uint16_t delaytime);
void beebShort();
void updateButtons();
uint8_t waitforpress();
uint16_t updatingDelay(uint16_t t, uint8_t buttons[], uint8_t buttons_length);

// MENUS
uint8_t menu();

// CELEBRATIONS
void celebrate();
void celebrate1();

// TEST FUNCTIONS
void test();
void test2();

#endif
