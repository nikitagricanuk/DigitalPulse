#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <vector>
#include "sensors.h"

const int availablePins[] = {4, 5, 12, 13, 14};
const int availablePinsCount = sizeof(availablePins) / sizeof(availablePins[0]);

const int maxDallasSensors = 10; // Safe upper limit for dynamic sensors

OneWire* oneWires[maxDallasSensors];
DallasTemperature* sensors[maxDallasSensors];

float dallasReadTemperatureByIndex(int index) {
    if (sensors[index] != nullptr) {
        sensors[index]->requestTemperatures();
        delay(750); // Wait for conversion
        return sensors[index]->getTempCByIndex(0);
    } else {
        return -127.0; // Sensor not available
    }
}

void scanI2CDevices() {
    byte error, address;
    int devices = 0;

    Serial.println("Scanning for I2C devices...");
    Wire.begin();
    
    for (address = 1; address < 127; address++ ) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println(" !");
            devices++;
        }
    }

    if (devices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("Done.\n");
}

void scanDallasSensors() {
    int sensorIndex = 0;
    for (int i = 0; i < availablePinsCount && sensorIndex < maxDallasSensors; ++i) {
        int pin = availablePins[i];
        oneWires[sensorIndex] = new OneWire(pin);
        sensors[sensorIndex] = new DallasTemperature(oneWires[sensorIndex]);
        sensors[sensorIndex]->begin();

        if (sensors[sensorIndex]->getDeviceCount() > 0) {
            Serial.print("Sensor found on GPIO ");
            Serial.println(pin);
            ++sensorIndex;
        } else {
            delete sensors[sensorIndex];
            sensors[sensorIndex] = nullptr;
            delete oneWires[sensorIndex];
            oneWires[sensorIndex] = nullptr;
        }
    }
}

void initializeSensors() {
    scanI2CDevices();
    scanDallasSensors();
}