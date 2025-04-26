#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "server.h"
#include "gates.h"

#define MQTT_SERVER "5.196.78.28" // test.mosquitto.org
#define MQTT_PORT 1883

// Create a WiFi client and a PubSubClient
WiFiClient espClient;
PubSubClient mqttClient(espClient);

ESP8266WebServer server(80); // 80 is the HTTP default port

// Setup MQTT server
void mqttCallback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println(message);

    String topicStr = String(topic);
    if (topicStr.startsWith("digitalpulse-gate/open/")) {
        String gateId = topicStr.substring(strlen("digitalpulse-gate/open/"));
        if (message == "1") {
            Serial.print("Opening gate with ID: ");
            Serial.println(gateId);
            openGate(gateId.toInt());
        }
    }
    else if (topicStr.startsWith("digitalpulse-gate/close/")) {
        String gateId = topicStr.substring(strlen("digitalpulse-gate/close/"));
        if (message == "1") {
            Serial.print("Closing gate with ID: ");
            Serial.println(gateId);
            closeGate(gateId.toInt());
        }
    }
}

void initializeMQTT() {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(mqttCallback);
}

// Ensure connection to MQTT broker
void reconnectMQTT() {
    while (!mqttClient.connected()) {
        Serial.print("Connecting to MQTT...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (mqttClient.connect(clientId.c_str())) {
            Serial.println("connected");
            mqttClient.subscribe("digitalpulse-gate/open/#");
            mqttClient.subscribe("digitalpulse-gate/close/#");
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