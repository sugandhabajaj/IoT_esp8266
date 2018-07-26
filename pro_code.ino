// Code to switch the LED and Motor Fan on from the Mobile Phone

#include "ESP8266WiFi.h"

const char* ssid = "abc";            // Wi-Fi ID 
const char* password = "abc@123";      // Wi-Fi Password
const int ledPin = 8;
int motor=3;
WiFiServer server(80);               // Server Port Address

void printWiFiStatus();

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Configure GPIO2 as OUTPUT.
  pinMode(ledPin, OUTPUT);

  // Start TCP server.
  server.begin();
}

void loop(void) {
  // Check if module is still connected to WiFi.
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    // Print the new IP to Serial.
    printWiFiStatus();
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");

    while (client.connected()) {
      if (client.available()) {
        char command = client.read();              // To accept the incoming command from the client
        if (command == 'H') {
          digitalWrite(ledPin, HIGH);             // If Command is 'H' turn the LED ON
          Serial.println("LED is now on.");
        }
        else if (command == 'L') {
          digitalWrite(ledPin, LOW);              // If Command is 'L' turn the LED OFF
          Serial.println("LED is now off.");
        }
        else if(command =='C') {                   // To check if LED is ON or OFF
        Serial.println(digitalRead(8));
        if (digitalRead(8)==1)                       //Check the Pin as Input
        {client.println("LED is ON");}
        
        else {client.println("LED is OFF");}
        }
        else if (command == 'O') {                       // To switch the Motor ON
          analogWrite(motor, 50);
          Serial.println("FAN is now off.");
        }
        else if (command == 'N') {             // To switch the motor OFF
          analogWrite(motor,255);
          Serial.println("FAN is now on.");
        }
        else if(command =='S') {                 // To check the status of MOTOR FAN
        Serial.println(analogRead(3));
        if (analogRead(3)==1)
        {client.println("FAN is ON");}
        
        else {client.println("FAN is OFF");}
        }
        
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
}

void printWiFiStatus() {
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

