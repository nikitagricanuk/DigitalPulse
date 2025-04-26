#include <OneWire.h>
#include <DallasTemperature.h>


void initializeSensors(DallasTemperature *sensors) {
    // Start the sensor library
    sensors->begin();
}

float readTemperature(DallasTemperature *sensors) {
    // Request temperature readings
    sensors->requestTemperatures();
    delay(750); // <-- Wait for conversion
    // Get the temperature in Celsius
    return sensors->getTempCByIndex(0);
}