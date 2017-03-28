#include<IRremote.h>

int IRemitter = 8;
int IRreceiver = 9;
int LED = 10;

IRrecv irrecv(IRreceiver);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(IRemitter, OUTPUT);
  pinMode(IRreceiver, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(IRemitter, 1);

}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX); 
    irrecv.resume();  
  }
  if (results.value == 0xFFA857) {
    digitalWrite(LED, 1);
  } else if (results.value == 0xFFE01F) {
    digitalWrite(LED, 0);
  }
}
