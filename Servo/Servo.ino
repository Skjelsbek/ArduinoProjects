#include <Servo.h>;
Servo myServo;

int pos = 60;

void setup() {
  Serial.begin(9600);
  myServo.attach(8);
  myServo.write(50);

}

void loop() {   
    for (pos = 50; pos < 110; pos++) {
      myServo.write(pos);
      delay(20);
    } 

    for (pos = 110; pos >= 50; pos--) {
      myServo.write(pos);
      delay(20);
    }
}

void resetPos(int currentPos) {
  if (currentPos < 60) {
    for (int i = currentPos; i <= 60; i++) {
      myServo.write(i);
      delay(20);
    }
  } else if (currentPos > 60) {
    for (int i = currentPos; i >= 60; i--) {
      myServo.write(i);
      delay(20);
    }
  }
}

