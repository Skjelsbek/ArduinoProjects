// Including LCD library
#include <LiquidCrystal_I2C.h>

// Instantiate LiquidCrystal_I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Including Time and DS1302RTC libraries
#include <TimeLib.h>
#include <DS1302RTC.h>

// Instantiate DS1302RTC
// Set pins:  CE, IO, CLK
DS1302RTC rtc(2, 3, 4);

// Optional connection for RTC module
// Using digital pins 33 and 35 as GND and VCC
#define DS1302_GND_PIN 33
#define DS1302_VCC_PIN 35

// Including and defining and instantiate DHT11(Temperature and Humidity sensor)
#include <DHT.h>
const int dhtPin = A0;
DHT dht(dhtPin, DHT11);

// Defining Joystick
#define vrx A2
#define vry A1
#define sw 2

byte menu_RIGHT[8] = {
   B10000,
   B11000,
   B11100,
   B11110,
   B11100,
   B11000,
   B10000,
   B00000};

byte menu_LEFT[8] = {
   B00001,
   B00011,
   B00111,
   B01111,
   B00111,
   B00011,
   B00001,
   B00000};

byte thermometer_symbol[8] = {
   B00100,
   B01010,
   B01010,
   B01110,
   B01110,
   B11111,
   B11111,
   B01110};

byte bell_symbol[8] = {
   B00100,
   B01110,
   B01110,
   B01110,
   B01110,
   B11111,
   B00000,
   B00100};
   
void setup() {
  Serial.begin(9600); // Init Serial
  
  // Activate RTC module
  digitalWrite(DS1302_GND_PIN, LOW);
  pinMode(DS1302_GND_PIN, OUTPUT);
  digitalWrite(DS1302_VCC_PIN, HIGH);
  pinMode(DS1302_VCC_PIN, OUTPUT);

  // Init LCD
  lcd.begin();
  lcd.setBacklight(HIGH);

  // Init DHT
  dht.begin();
  
  setSyncProvider(rtc.get); // Get time from RTC
  //setTime(23, 44, 5, 21, 6, 2018);
  //rtc.set(now());

  pinMode(vrx, INPUT);
  pinMode(vry, INPUT);
  pinMode(sw, INPUT_PULLUP);

  lcd.createChar(0, thermometer_symbol);
  lcd.createChar(1, bell_symbol);
  lcd.createChar(5, menu_RIGHT);
  lcd.createChar(6, menu_LEFT);
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

  // Display humidity and temperature  
  lcd.setCursor(8, 1);
  lcd.write(0);
  lcd.print((int)dht.readTemperature()); 
  lcd.print("C ");
  lcd.print((int)dht.readHumidity());
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
