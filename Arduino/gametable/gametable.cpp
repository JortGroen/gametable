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
  pinMode(BUZZER, OUTPUT);
  
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
  //digitalWrite(BUZZER, state);
}

void blinkLed(uint8_t led, uint8_t quantity, uint16_t delaytime){
  for (uint8_t i=0; i<quantity; i++){
    digitalWrite(led, HIGH);
    delay(delaytime);
    digitalWrite(led, LOW);
    delay(delaytime);
  }
}

void beebShort(){
  digitalWrite(BUZZER, HIGH);
  delay(BEEBSHORTD);
  digitalWrite(BUZZER, LOW);
}

void updateButtons(){
  buttonG = digitalRead(BUTTON_GREEN);
  buttonY = digitalRead(BUTTON_YELLOW);
  buttonR = digitalRead(BUTTON_RED);
  buttonB = digitalRead(BUTTON_BLUE);
  buttonW = digitalRead(BUTTON_WHITE);
}

uint8_t waitforpress(){
  while(true){
    for (uint8_t i=0; i<NObuttons; i++){
      if (digitalRead(BUTTONS[i]) == HIGH){
        updateButtons();
        return i;
      }
    }
    delay(10); // I have encountered before that this is needed sometimes
  }
  return -1;
}

uint16_t updatingDelay(uint16_t t, uint8_t buttons[], uint8_t buttons_length){
  uint8_t delaytime = 50;
  updateButtons();
  bool statuses[buttons_length];
  for (uint8_t button=0; button<buttons_length; button++){
    statuses[button] = digitalRead(buttons[button]);
  }
  
  bool change = false;
  bool value = false;
  for (int i=0; i<t; i+=delaytime){
    for (uint8_t button=0; button<buttons_length; button++){
      value = digitalRead(buttons[button]);
      if (value != statuses[button] && value == true){
        return t-i;
      }
    }
    delay(delaytime);
  }
  return 0;
}
// HELPER FUNCS STOP

uint8_t menu(){
  uint8_t buttons[5] = {BUTTON_GREEN, BUTTON_YELLOW, BUTTON_RED, BUTTON_BLUE, BUTTON_WHITE};
  while(true){
    setAll(HIGH);
    delay(1000);
    setAll(LOW);
    uint16_t restdelay = 1000;
    while(restdelay > 0){
      restdelay = updatingDelay(restdelay, buttons, 5);
      updateButtons();
      if(buttonG){
        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED_GREEN, HIGH);
        delay(50);
        digitalWrite(BUZZER, LOW);
        return 0;
      }
      if(buttonW){
        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED_WHITE, HIGH);
        delay(50);
        digitalWrite(BUZZER, LOW);
        return 1;
      }
      if(buttonB){
        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED_BLUE, HIGH);
        delay(50);
        digitalWrite(BUZZER, LOW);
        return 2;
      }
      if(buttonR){
        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED_RED, HIGH);
        delay(50);
        digitalWrite(BUZZER, LOW);
        return 3;
      }
      if(buttonY){
        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED_YELLOW, HIGH);
        delay(50);
        digitalWrite(BUZZER, LOW);
        return 4;
      }
    }
  }  
  return -1;
}

// CELLEBRATIONS
void celebrate(){
  celebrate1();
}
void celebrate1(){
  uint16_t delaytime = 500;
  setAll(LOW);
  delay(delaytime);
  digitalWrite(LED_GREEN, HIGH);
  delay(delaytime);
  digitalWrite(LED_GREEN, LOW);
  
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_WHITE, HIGH);
  delay(delaytime);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_WHITE, LOW);
  
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_RED, HIGH);  
  delay(delaytime);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);  
 
  delay(delaytime);

  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_RED, HIGH);
  delay(delaytime);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);

  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_WHITE, HIGH);
  delay(delaytime);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_WHITE, LOW);

  digitalWrite(LED_GREEN, HIGH);
  delay(delaytime);
  digitalWrite(LED_GREEN, LOW);

  return;
}

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
