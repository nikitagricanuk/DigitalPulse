#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "wifi.h"
#include "sensors.h"
#include "server.h"
#include "gates.h"

// Global definitions
#define WIRELESS_SSID "juli"
#define WIRELESS_PASSWORD "00000000"

// Pin definitions
#define DS18B20_PIN 4 // Pin for DS18B20 sensor

// the setup function runs once when you press reset or power the board
// ESP8266WebServer server(80); //Server on port 80

void setup() {
  Serial.begin(9600); 
  
  // Pin configurations

  initializeSensors(); 
  setupGates(); // Setup gates
  connectToWiFi(WIRELESS_SSID, WIRELESS_PASSWORD);
  initializeMQTT();
  // server.on("/", handleRoot);
  // server.begin();

}

void loop() {
  // server.handleClient();
  handleMQTT();
  antifreezeGate(1);
  antifreezeGate(2);
  char payload[50];
  if (dallasReadTemperatureByIndex(0) == -127.0) {
    Serial.println("No DS18B20 sensor found");
    return;
  }
  dtostrf(dallasReadTemperatureByIndex(0), 1, 2, payload);
  publishMQTT("digitalpulse/temperature", payload);
}
