const int VRX = A0;
const int VRY = A1;
const int SW = 8;
const int bluePin = 9;
const int greenPin = 10;
const int redPin = 11;

void setup() {  
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT);  
  digitalWrite(SW, HIGH);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  delay(500);
  Serial.print("VRX: ");
  Serial.println(analogRead(VRX));

  Serial.print("VRY: ");
  Serial.println(analogRead(VRY));
  
  Serial.print("SW: ");
  Serial.println(digitalRead(SW));

  if (analogRead(VRX) < 200) {
    setColor(255, 0, 0);
  }

  if (analogRead(VRX) > 768) {
    setColor(255, 255, 255);
  }

  if (analogRead(VRY) < 200) {
    setColor(0, 255, 0);
  }

  if (analogRead(VRY) > 768) {
    setColor(0, 0, 255);
  }

  if (digitalRead(SW) == 0) {
    setColor (0, 0, 0);
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin,  red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

