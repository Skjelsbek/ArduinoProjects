void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  int i;
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  
  for(i = 0; i < 256; i++) {
    analogWrite(8, i);
    delay(4);
  }

  for(i = 255; i >= 0; i--) {
    analogWrite(8, i);
    delay(4);
  }
  
  delay(1000);
  
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);

  for(i = 0; i < 256; i++) {
    analogWrite(8, i);
    delay(4);
  }

  for(i = 255; i >= 0; i--) {
    analogWrite(8, i);
    delay(4);
  }
  
  delay(1000);
}
