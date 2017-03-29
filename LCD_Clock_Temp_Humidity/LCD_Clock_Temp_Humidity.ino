// Including LCD library
#include <LiquidCrystal_I2C.h>

// Instantiate LiquidCrystal_I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Including Time and DS1302RTC libraries
#include <Time.h>
#include <TimeLib.h>
#include <DS1302RTC.h>

// Instantiate DS1302RTC
// Set pins:  CE, IO, CLK
DS1302RTC RTC(27, 29, 31);

// Optional connection for RTC module
// Using digital pins 33 and 35 as GND and VCC
#define DS1302_GND_PIN 33
#define DS1302_VCC_PIN 35

// Including and defining and instantiate DHT11(Temperature and Humidity sensor)
#include "dht.h"
const int dhtPin = A0;
dht DHT;

// Defining Joystick
#define vrx A2
#define vry A1
#define sw 2

void setup() {
  // Activate RTC module
  digitalWrite(DS1302_GND_PIN, LOW);
  pinMode(DS1302_GND_PIN, OUTPUT);
  digitalWrite(DS1302_VCC_PIN, HIGH);
  pinMode(DS1302_VCC_PIN, OUTPUT);

  Serial.begin(9600); // Init Serial

  // Init LCD
  lcd.init();
  lcd.setBacklight(HIGH);

  setSyncProvider(RTC.get); // Get time from RTC
  //setTime(22, 5, 5, 26, 3, 2017);
  //RTC.set(now());

  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);
  pinMode(sw, INPUT_PULLUP);
}

void loop() {  
  Serial.print("VRX: ");
  Serial.println(analogRead(vrx));
  Serial.print("VRY: ");
  Serial.println(analogRead(vry));
  Serial.print("SW:");
  Serial.println(digitalRead(sw));
  
  // Display abbreviated Day-of-Week
  lcd.home();
  lcd.print(dayShortStr(weekday()));
  
  // Display date
  lcd.setCursor(5, 0);
  lcd.print(" ");
  print2digits(day());
  lcd.print("/");
  print2digits(month());
  lcd.print("/");
  lcd.print(year());
  
  // Display time
  lcd.setCursor(0, 1);
  print2digits(hour());
  lcd.print(":");
  print2digits(minute());
  lcd.print(":");
  print2digits(second());  

  // Display humidity and temperature
  DHT.read11(dhtPin);
  lcd.setCursor(9, 1);  
  lcd.print((int)DHT.temperature); 
  lcd.print("C ");
  lcd.print((int)DHT.humidity);
  lcd.print("%"); 
    
  delay(1000);

}

void print2digits(int number) {
  // Output leading zero
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);
}

void setAlarm() {
  // Setting hour, minutes and seconds to 0  
  lcd.clear();
  lcd.setCursor(4, 0);
  print2digits(0);
  lcd.print(":");
  print2digits(0);
  lcd.print(":");
  print2digits(0); 
  
  byte newDigit = 0; // Digit to be placed at the selected place
  
  while (digitalRead(sw) == 1) {
    lcd.setCursor(4, 0);
    print2digits(hour());
    lcd.print(":");
    print2digits(minute());
    lcd.print(":");
    print2digits(second()); 
  }
}
