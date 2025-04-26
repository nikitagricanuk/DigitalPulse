#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>

void initializeSensors();
float dallasReadTemperatureByIndex(int index);