#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "server.h"

#define MQTT_SERVER "5.196.78.28"
#define MQTT_PORT 1883

// Create a WiFi client and a PubSubClient
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Setup MQTT server
void initializeMQTT() {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
}

// Ensure connection to MQTT broker
void reconnectMQTT() {
    while (!mqttClient.connected()) {
        Serial.print("Connecting to MQTT...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (mqttClient.connect(clientId.c_str())) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" trying again in 5 seconds");
            delay(5000);
        }
    }
}

// Publish a message to a specific topic
void publishMQTT(const char* topic, const char* payload) {
    if (!mqttClient.connected()) {
        reconnectMQTT();
    }
    mqttClient.loop();
    mqttClient.publish(topic, payload);
}

void handleMQTT() {
    if (!mqttClient.connected()) {
        reconnectMQTT();
    }
    mqttClient.loop();
}