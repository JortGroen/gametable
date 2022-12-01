// WARNING: when initializing serial connection, leds white and red are frozen on!

#include "gametable.h"

bool buttonG;
bool buttonY;
bool buttonR;
bool buttonB;
bool buttonW;

// SETUP FUNCTIONS
void tableinit(){
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  pinMode(BUTTON_GREEN, INPUT);
  pinMode(BUTTON_WHITE, INPUT);
  pinMode(BUTTON_BLUE, INPUT);
  pinMode(BUTTON_RED, INPUT);
  pinMode(BUTTON_YELLOW, INPUT);

  //Serial.begin(115200);
}

// HELPER FUNCS START
void setLeds(bool states[5]){
    digitalWrite(LED_GREEN, states[0]);
    digitalWrite(LED_YELLOW, states[1]);
    digitalWrite(LED_RED, states[2]);
    digitalWrite(LED_BLUE, states[3]);
    digitalWrite(LED_WHITE, states[4]);
    //Serial.print("setting white to: ");
    //Serial.println(states[4]);
}

void setAll(bool state){
  bool states[5] = {state, state, state, state, state}; 
  setLeds(states);
}

void updateButtons(){
  buttonG = digitalRead(BUTTON_GREEN);
  buttonY = digitalRead(BUTTON_YELLOW);
  buttonR = digitalRead(BUTTON_RED);
  buttonB = digitalRead(BUTTON_BLUE);
  buttonW = digitalRead(BUTTON_WHITE);
}

uint16_t updatingDelay(uint16_t t, uint8_t buttons[], uint8_t buttons_length){
  uint8_t delaytime = 50;
  updateButtons();
  bool statuses[buttons_length];
  for (uint8_t button=0; button<buttons_length; button++){
    statuses[button] = digitalRead(buttons[button]);
  }
  
  bool change = false;
  for (int i=0; i<t; i+=delaytime){
    for (uint8_t button=0; button<buttons_length; button++){
      if (digitalRead(buttons[button]) != statuses[button]){
        //if (i>t){
          //Serial.println("problem 2");
        //}
        return t-i;
      }
    }
    delay(delaytime);
  }
  return 0;
}
// HELPER FUNCS STOP

// TEST FUNCS

void test(){
  uint8_t buttons[5] = {BUTTON_GREEN, BUTTON_YELLOW, BUTTON_RED, BUTTON_BLUE, BUTTON_WHITE};
  setAll(HIGH);
  delay(1000);
  setAll(LOW);
  uint16_t restdelay = 1000;
  while(restdelay > 0){
    restdelay = updatingDelay(restdelay, buttons, 5);
    //Serial.println(restdelay);
    updateButtons();
    if(buttonG){
      digitalWrite(LED_GREEN, HIGH);
    }
    if(buttonW){
      digitalWrite(LED_WHITE, HIGH);
    }
    if(buttonB){
      digitalWrite(LED_BLUE, HIGH);
    }
    if(buttonR){
      digitalWrite(LED_RED, HIGH);
    }
    if(buttonY){
      digitalWrite(LED_YELLOW, HIGH);
    }
  }
}

void test2(){
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_WHITE, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  delay(1000);                       // wait for a second
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_WHITE, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  if(digitalRead(BUTTON_GREEN)){
    digitalWrite(LED_GREEN, HIGH);
  }
  if(digitalRead(BUTTON_WHITE)){
    digitalWrite(LED_WHITE, HIGH);
  }
  if(digitalRead(BUTTON_BLUE)){
    digitalWrite(LED_BLUE, HIGH);
  }
  if(digitalRead(BUTTON_RED)){
    digitalWrite(LED_RED, HIGH);
  }
  if(digitalRead(BUTTON_YELLOW)){
    digitalWrite(LED_YELLOW, HIGH);
  }
  delay(1000);                       // wait for a second
}
