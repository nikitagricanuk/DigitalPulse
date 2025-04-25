#include <arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "wifi.h"

// Global definitions
#define WIRELESS_SSID "juli"
#define WIRELESS_PASSWORD "00000000"

// the setup function runs once when you press reset or power the board
ESP8266WebServer server(80); //Server on port 80
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  connectToWiFi(WIRELESS_SSID, WIRELESS_PASSWORD);
  server.on("/", handleRoot);
  server.begin();
  pinMode(16, OUTPUT);
}

void loop() {
  server.handleClient();
  digitalWrite(16, HIGH); 
  delay(1000);    
  digitalWrite(16, LOW);
  delay(1000);
}

void handleRoot() {
  server.send(200, "text/plain", "<!DOCTYPE html><html lang=\\\"ru\\\"><head><meta charset=\\\"UTF-8\\\"><title>Параметры с затворами</title><style>.container{display:flex;justify-content:space-between;margin:20px;gap:20px;}.section{flex:1;border:1px solid #888;padding:20px;display:flex;flex-direction:column;justify-content:space-between;min-height:350px;box-sizing:border-box;}.section h2{text-align:center;}.parameters{font-size:18px;line-height:1.6;margin:20px 0;}.parameters p{margin:8px 0;}.action-button{width:150px;padding:10px;font-size:16px;color:#fff;background-color:#007BFF;border:none;border-radius:5px;cursor:pointer;align-self:center;}</style></head><body><div class=\\\"container\\\"><div class=\\\"section\\\"><h2>Затвор 1</h2><div class=\\\"parameters\\\"><p><strong>Уровень воды:</strong> --</p><p><strong>Температура:</strong> --</p><p><strong>Давление:</strong> --</p></div><button class=\\\"action-button\\\" id=\\\"leftButton\\\">Открыть</button></div><div class=\\\"section\\\"><h2>Затвор 2</h2><div class=\\\"parameters\\\"><p><strong>Уровень воды:</strong> --</p><p><strong>Температура:</strong> --</p><p><strong>Давление:</strong> --</p></div><button class=\\\"action-button\\\" id=\\\"rightButton\\\">Открыть</button></div></div></body></html>");
}
