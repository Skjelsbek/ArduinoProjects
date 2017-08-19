// Ultrasonic sensors
#include <Ultrasonic.h>
#define rightEcho 23
#define rightTrig 22
#define leftEcho 9
#define leftTrig 8
Ultrasonic rightSensor(rightTrig, rightEcho);
Ultrasonic leftSensor(leftTrig, leftEcho);

// Servo
#define servoPin 10
#include <Servo.h>;
Servo myServo;
int pos = 50;

// Motor driver (LN298N)
#define speedPin 2
#define in1 24
#define in2 25
int speed = 0;

void setup() {


  // Servo init
  myServo.attach(servoPin);
  myServo.write(pos);

  // Motor driver init
  pinMode(speedPin, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);  
}

void loop() {  
  if (((double)(rightSensor.distanceRead() / 100) < 0.3) && ((double)(leftSensor.distanceRead() / 100) < 0.3)) {
    if ((double)(rightSensor.distanceRead() / 100) < (double)(leftSensor.distanceRead() / 100)) {
      turnLeft();
    } else {
      turnRight();
    }
    moveBackwards();
  } else {
    moveForward();
  }
  
  if ((double)(rightSensor.distanceRead() / 100) < 0.3) {
      turnLeft();
  } else if ((double)(leftSensor.distanceRead() / 100) < 0.3) {
      turnRight();
  } else {
      centerWheels();
  }  
}

void moveForward() { 
  if (inReverse()) {
    for(speed; speed >= 0; speed--) {
      analogWrite(speedPin, speed);
      delay(4);
    }
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  for(speed = 0; speed < 256; speed++) {
    analogWrite(speedPin, speed);
    delay(4);
  }
}

void moveBackwards() {
  if (!inReverse()) {
    for(speed; speed >= 0; speed--) {
      analogWrite(speedPin, speed);
      delay(4);
    }
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  
  for(speed = 0; speed < 256; speed++) {
    analogWrite(speedPin, speed);
    delay(4);
  }
}

void turnLeft() {
  for (pos; pos >= 50; pos--) {
      myServo.write(pos);
      delay(20);
    }
}

void turnRight() {
  for (pos; pos < 110; pos++) {
    myServo.write(pos);
    delay(20);
  } 
}

void centerWheels() {
  if (pos < 50) {
    for (pos; pos <= 50; pos++) {
      myServo.write(pos);
      delay(20);
    }
  } else if (pos > 50) {
    for (pos; pos >= 50; pos--) {
      myServo.write(pos);
      delay(20);
    }
  }
}

boolean inReverse() {
  if (in1 == LOW) {
    return true;
  }
  return false;
}

