const int ledPin = 6;
const int potMeter = A2;

void setup() {  
  pinMode(ledPin, OUTPUT);
  pinMode(potMeter, INPUT);
  Serial.begin(9600);
}

void loop() {
  long verdi = analogRead(potMeter);
  //Serial.println(verdi);
  
  /*if (analogRead(potMeter) < 500) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }*/
  
  /*digitalWrite(ledPin, HIGH);
  delay(verdi);
  digitalWrite(ledPin, LOW);
  delay(verdi);*/

  long pwmVerdi = verdi*255/1023;
  Serial.println(pwmVerdi);
  analogWrite(ledPin, pwmVerdi);
}
