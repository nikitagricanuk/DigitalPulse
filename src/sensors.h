#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>

void initializeSensors(DallasTemperature *sensors);
float readTemperature(DallasTemperature *sensors);