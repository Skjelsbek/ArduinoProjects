// Defining synchronous counter pins
#define CLK 8 // Clock pulse from arduino digital pin 8 to synchronous counter clk input
#define Qa 9  // Synchronous counter output Qa to digital pin 9 on arduino
#define Qb 10 // Synchronous counter output Qb to digital pin 10 on arduino
#define Qc 11 // Synchronous counter output Qc to digital pin 11 on arduino

// Init LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Init clock(pulse from arduino to synchronous counter) and inputs(synchronous counter outputs)
  pinMode(CLK, OUTPUT);
  pinMode(Qa, INPUT);
  pinMode(Qb, INPUT);
  pinMode(Qc, INPUT);
  digitalWrite(CLK, HIGH);

  // Firing up the LCD
  lcd.init();
  lcd.setBacklight(HIGH); // Setting the backlight high turns it on
}

void loop() {
  digitalWrite(CLK, LOW); // Sending clock pulse
  delay(500); // Wait 0.5 sec
  digitalWrite(CLK, HIGH); // Stopping clock pulse
  printToDisplay(digitalRead(Qa), digitalRead(Qb), digitalRead(Qc)); // Printing number from inputs Qa, Qb and Qc   
  delay(500); // Wait 0.5 sec
}

// Returns the binary number as a String so that it can be printed to the LCD
String binaryNum (int qa, int qb, int qc) {
  String digit1 = String(qc); // Casting qc to a String
  String digit2 = String(qb); // Casting qb to a String
  String digit3 = String(qa); // Casting qa to a String
  return String(digit1 + digit2 + digit3); // Returning a String with the most significant bit first and least last
}

// Returns the number in decimal as a String so that it can be printed to the LCD
String decimalNum(int qa, int qb, int qc) {
  int num = qa * pow(2, 0) + qb * pow(2, 1) + qc * pow(2, 2); // Convert from binary to decimal
  return String(num); // Return decimal value as a String
}

// Prints both binary and decimal value to the LCD
void printToDisplay(int qa, int qb, int qc) {
  lcd.clear();  // Clears the screen
  lcd.home(); // Set cursor at the top left corner
  lcd.print("In binary: ");
  lcd.print(binaryNum(qa, qb, qc)); // Prints the String value from binaryNum function

  lcd.setCursor(0, 1);  // Sets the cursor at second row, first column 
  lcd.print("In decimal: ");
  lcd.print(decimalNum(qa, qb, qc));  // Prints the String value from decimalNum function
}

