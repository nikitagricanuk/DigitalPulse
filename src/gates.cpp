#include <Arduino.h>

#define GATE1_PIN 13
#define GATE2_PIN 5

const int gatePins[] = {
    0,      // index 0 unused for convenience, since you start from gateId 1
    GATE1_PIN, // gateId = 1
    GATE2_PIN  // gateId = 2
};

// Antifreeze configuration
unsigned long lastAntifreezeTime = 0;
unsigned long antifreezeInterval = 10UL * 60UL * 1000UL; // 10 minutes in milliseconds
int antifreezePulseDuration = 500; // Duration gate moves during antifreeze in milliseconds

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

int getGateStatus(int gateId) {
    if (gateId <= 0 || gateId >= sizeof(gatePins)/sizeof(gatePins[0])) {
        return -1;
    }
    Serial.println("Getting status of gate with ID: " + String(gateId));
    int status = digitalRead(gatePins[gateId]);
    Serial.println("Gate " + String(gateId) + " status: " + String(status));
    return status;
}

void closeGate(int gateId) {
    if (gateId <= 0 || gateId >= sizeof(gatePins)/sizeof(gatePins[0])) {
        return;
    }
    Serial.println("Closing gate with ID: " + String(gateId));
    digitalWrite(gatePins[gateId], HIGH); 
}

void antifreezeGate(int gateId, bool force) {
    if (gateId <= 0 || gateId >= sizeof(gatePins)/sizeof(gatePins[0])) {
        return;
    }
    

    if (!force) {
        unsigned long currentMillis = millis();
        if (currentMillis - lastAntifreezeTime < antifreezeInterval) {
            return; // Not time yet
        }
        lastAntifreezeTime = currentMillis;
    }

    Serial.println("Performing antifreeze action for gate ID: " + String(gateId));

    int currentState = digitalRead(gatePins[gateId]);

    if (currentState == HIGH) {
        // If gate is closed, pulse it open slightly and close back
        digitalWrite(gatePins[gateId], LOW);
        delay(antifreezePulseDuration);
        digitalWrite(gatePins[gateId], HIGH);
    } else {
        // If gate is open, pulse it closed slightly and open back
        digitalWrite(gatePins[gateId], HIGH);
        delay(antifreezePulseDuration);
        digitalWrite(gatePins[gateId], LOW);
    }
}

void setAntifreezeSettings(unsigned long intervalMs, int pulseDurationMs) {
    antifreezeInterval = intervalMs;
    antifreezePulseDuration = pulseDurationMs;
    Serial.println("Antifreeze settings updated:");
    Serial.println("Interval (ms): " + String(antifreezeInterval));
    Serial.println("Pulse duration (ms): " + String(antifreezePulseDuration));
}