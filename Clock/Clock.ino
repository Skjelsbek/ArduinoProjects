#define buzzer 7
#define redButton 8
#define greenButton 9
#define yellowButton 10
#define whiteButton 11

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(whiteButton, INPUT_PULLUP);  

}

void loop() {
  if (digitalRead(redButton == 0)) {
    tone(buzzer, 1000);
  } 
  if (digitalRead(redButton) == 1) {
    noTone(buzzer);
  }

}
