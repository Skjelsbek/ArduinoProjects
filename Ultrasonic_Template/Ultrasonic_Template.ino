#include <Ultrasonic.h>
#define trig1 6
#define echo1 7
#define trig2 8
#define echo2 9
Ultrasonic ultrasonic1(trig1, echo1);
Ultrasonic ultrasonic2(trig2, echo2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Distance1: ");
  Serial.println((double)ultrasonic1.distanceRead() / 100);
  Serial.print("Distance2: ");
  Serial.println((double)ultrasonic2.distanceRead() / 100);  
  delay(1000);
}
