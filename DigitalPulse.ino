#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "wifi.h"
#include "sensors.h"
#include "mqtt.h"

// Global definitions
#define WIRELESS_SSID "juli"
#define WIRELESS_PASSWORD "00000000"

// Pin definitions
#define DS18B20_PIN 4 // Pin for DS18B20 sensor

// the setup function runs once when you press reset or power the board
// ESP8266WebServer server(80); //Server on port 80

OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600); 
  
  // Pin configurations

  initializeSensors(&sensors); 
  connectToWiFi(WIRELESS_SSID, WIRELESS_PASSWORD);
  initializeMQTT();
  // server.on("/", handleRoot);
  // server.begin();

}

void loop() {
  // server.handleClient();
  handleMQTT();
  Serial.println(readTemperature(&sensors));
  char payload[50];
  dtostrf(readTemperature(&sensors), 1, 2, payload);
  publishMQTT("digitalpulse/temperature", payload);
}

// void handleRoot() {
//   server.send(200, "text/plain", "<!DOCTYPE html><html lang=\\\"ru\\\"><head><meta charset=\\\"UTF-8\\\"><title>Параметры с затворами</title><style>.container{display:flex;justify-content:space-between;margin:20px;gap:20px;}.section{flex:1;border:1px solid #888;padding:20px;display:flex;flex-direction:column;justify-content:space-between;min-height:350px;box-sizing:border-box;}.section h2{text-align:center;}.parameters{font-size:18px;line-height:1.6;margin:20px 0;}.parameters p{margin:8px 0;}.action-button{width:150px;padding:10px;font-size:16px;color:#fff;background-color:#007BFF;border:none;border-radius:5px;cursor:pointer;align-self:center;}</style></head><body><div class=\\\"container\\\"><div class=\\\"section\\\"><h2>Затвор 1</h2><div class=\\\"parameters\\\"><p><strong>Уровень воды:</strong> --</p><p><strong>Температура:</strong> --</p><p><strong>Давление:</strong> --</p></div><button class=\\\"action-button\\\" id=\\\"leftButton\\\">Открыть</button></div><div class=\\\"section\\\"><h2>Затвор 2</h2><div class=\\\"parameters\\\"><p><strong>Уровень воды:</strong> --</p><p><strong>Температура:</strong> --</p><p><strong>Давление:</strong> --</p></div><button class=\\\"action-button\\\" id=\\\"rightButton\\\">Открыть</button></div></div></body></html>");
// }
