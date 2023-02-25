#define BUTTON 16

uint32_t t0 = 0;
uint32_t t1 = 0;
uint32_t t2 = 0;
uint32_t timeout = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
}

void loop() {
  while(digitalRead(BUTTON) == LOW){
    delay(5);
    //timeout += 10;
    //if(timeout > 1000){
    //  t0 = 0;
    //}
  }
  t1 = millis();
   while(digitalRead(BUTTON) == HIGH){
    delay(5);
  } 
  t2 = millis();
  Serial.print("delay(");
  Serial.print(t1-t0);
  Serial.println(");");
  Serial.println("digitalWrite(BUZZER, HIGH);");
  Serial.print("delay(");
  Serial.print(t2-t1);
  Serial.println(");");
  Serial.println("digitalWrite(BUZZER, LOW);");
  t0 = t2;
  //timeout = 0;
}
