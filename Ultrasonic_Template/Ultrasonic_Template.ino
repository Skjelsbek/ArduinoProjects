#include <Ultrasonic.h>
#define trig1 8
#define echo1 9
#define trig2 10
#define echo2 11
Ultrasonic ultrasonic1(trig1, echo1);
Ultrasonic ultrasonic2(trig2, echo2);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.setBacklight(HIGH);
}

void loop() {
  lcd.clear();
  lcd.home();
  lcd.print("Distance1: ");
  lcd.print((double)ultrasonic1.distanceRead() / 100);
  lcd.print("m");
  lcd.setCursor(0, 1);
  lcd.print("Distance2: ");
  lcd.print((double)ultrasonic2.distanceRead() / 100);
  lcd.println("m");   
  delay(1000);
}
