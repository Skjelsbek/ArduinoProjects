// Ultrasonic sensors
#include <Ultrasonic.h>
#define rightEcho 23
#define rightTrig 22
#define leftEcho 9
#define leftTrig 8
Ultrasonic rightSensor(rightTrig, rightEcho);
Ultrasonic frontSensor(leftTrig, leftEcho);

// Servo
#define servoPin 10
#include <Servo.h>;
Servo myServo;
int pos = 90;

// Motor driver (LN298N)
#define speedPin 2
#define in1 24
#define in2 25
int speed = 0;

void setup() {

  //Serial.begin(9600);
  
  // Servo init
  myServo.attach(servoPin);
  myServo.write(pos);

  // Motor driver init
  pinMode(speedPin, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {

  //Serial.println((double)frontSensor.distanceRead()/100);
  if ((double)frontSensor.distanceRead() / 100 > 0.5) {
    moveForward();
    delay(4);
  } else {
    stopEngine();
    turnRight();
    moveBackwards();
    delay(1000);

    if ((double)frontSensor.distanceRead() / 100 <= 0.5) {
      stopEngine();
      moveForward();
      delay(1000);
      stopEngine();
      turnLeft();
      moveBackwards();
      delay(1000);
    }
  }
}

void moveForward() {
  if (inReverse()) {
    stopEngine();
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  while (speed < 127) {
    analogWrite(speedPin, speed);
    speed++;
    delay(4);
  }
}

void moveBackwards() {
  if (!inReverse()) {
    stopEngine();
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  while (speed < 127) {
    analogWrite(speedPin, speed);
    speed++;
    delay(4);
  }
}

void turnLeft() {
  for (pos; pos >= 60; pos--) {
    myServo.write(pos);
    delay(4);
  }
}

void turnRight() {
  for (pos; pos < 130; pos++) {
    myServo.write(pos);
    delay(4);
  }
}

void centerWheels() {
  while (pos < 90) {
    myServo.write(pos);
    pos++;
    delay(4);
  }
  while (pos > 90) {
    myServo.write(pos);
    pos--;
    delay(4);
  }
}

void stopEngine() {
  while (speed > 0) {
    analogWrite(speedPin, speed);
    speed--;
    delay(4);
  }
}

boolean inReverse() {
  if (digitalRead(in1) == LOW) {
    return true;
  }
  return false;
}

