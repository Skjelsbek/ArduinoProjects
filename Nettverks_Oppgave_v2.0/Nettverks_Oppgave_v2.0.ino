#include <SPI.h>
#include <UIPEthernet.h> // Identical with Ethernet.h, but works with the module
#include "dht.h"  // Temp and humidity sensor lib

// Defining temp and humidity sensor
#define sensor A0
dht DHT;

// Buffer with caracters to send to client
char *myBuffer;

// Current index in buffer (used when receiving)
int index;

// Used to determine what task to be executed
const String readTemp = "check_temp";
const String readHum = "check_hum";
const String discon = "disconnect";

/*
 *  Setting up unique MAC address for the arduino,
 *  aswell as ip, dns, gateway and subnet mask.
 */
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 2);
IPAddress myDns(192,168,1, 0);
IPAddress gateway(192, 168, 1, 0);
IPAddress subnet(255, 255, 255, 0);

// Using "random" port above 1000 to not interfare with reserved ports
EthernetServer server(27015);

// whether or not the client was connected previously
boolean alreadyConnected = false;

/* 
 * Compare two arrays where size of arr1 is less than size of arr2
 * so that we can compare a preset array to whats in the buffer.
 * This is used to decide which function to use for returning to client
 */
bool compArray(char* arr1, unsigned int size1, char* arr2){
  for (unsigned int i = 0; i < size1; i++){
    if (arr1[i] != arr2[i]){
      return false;
    }
  }
  return true;
}

// Clears the input buffer and resets index variable
void clearBuffer() {
  for (int i = 0; i < 1024; i++) {
    myBuffer[i] = 0;
  }
  index = 0;
}

void setup() {
  // initialize the ethernet device
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  
  // start listening for clients
  server.begin();
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Prints the ip address to Serial monitor
  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());

  // Instantiate buffer
  myBuffer = new char[1024];  
  index = 0; 
}

void loop() {
  // Wait for a new client
  EthernetClient client = server.available();

  // When the client sends the first byte, say hello
  if (client) {
    if (!alreadyConnected) {      
      client.flush(); // Clear the input buffer
      Serial.println("We have a new client");
      client.println("Hello, client!");
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      // read the bytes incoming from the client to the buffer
      myBuffer[index++] = client.read();
      Serial.print(myBuffer[index - 1]); 
    }
        
    if (index > 0 && myBuffer[index - 1] == '\0') {
      Serial.println();
      if (compArray(readTemp.c_str(), readTemp.length(), myBuffer) == true) {
        // Sends temperature to client
        DHT.read11(sensor);
        int temp = (int)DHT.temperature;
        server.println(temp);
      } else if (compArray(readHum.c_str(), readHum.length(), myBuffer) == true) {
        // Sends humidity to client
        DHT.read11(sensor);
        int hum = (int)DHT.humidity;
        server.println(hum);
      } else if (compArray(discon.c_str(), discon.length(), myBuffer) == true) {
        // If client sends dsiconnect, stop the communication
        alreadyConnected = false;
        client.stop();
      } else {     
        // If the user didn't type any of the above commands, send error message 
        server.println("Type check_temp to get temperature, or check_hum to get humidity!");
      }

      // Clear input buffers
      client.flush();
      clearBuffer();
    }
  }
}
