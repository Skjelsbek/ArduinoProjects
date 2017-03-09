#include "Stepper.h"
int stepsPerRev = 32;
Stepper myStepper(stepsPerRev, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(700);
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
}

void loop() {
 while (digitalRead(12) == 0) {
  delay(3);
  myStepper.step(2048);   
 }
 while (digitalRead(13) == 0) {
  delay(3);
  myStepper.step(-2048);  
 }  
}
