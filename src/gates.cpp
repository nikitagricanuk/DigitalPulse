#include <Arduino.h>

#define GATE1_PIN 13
#define GATE2_PIN 5

const int gatePins[] = {
    0,      // index 0 unused for convenience, since you start from gateId 1
    GATE1_PIN, // gateId = 1
    GATE2_PIN  // gateId = 2
};

void setupGates() {
    pinMode(GATE1_PIN, OUTPUT);
    pinMode(GATE2_PIN, OUTPUT);
}

void openGate(int gateId) {
    if (gateId <= 0 || gateId >= sizeof(gatePins)/sizeof(gatePins[0])) {
        // invalid gateId
        return;
    }
    Serial.println("Opening gate with ID: " + String(gateId) + " (GPIO" + String(gatePins[gateId]) + ")");
    digitalWrite(gatePins[gateId], LOW); // or LOW depending on your hardware
}

void closeGate(int gateId) {
    if (gateId <= 0 || gateId >= sizeof(gatePins)/sizeof(gatePins[0])) {
        return;
    }
    Serial.println("Closing gate with ID: " + String(gateId));
    digitalWrite(gatePins[gateId], HIGH); 
}