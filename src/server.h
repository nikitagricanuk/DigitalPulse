#pragma once

void initializeMQTT();
void handleMQTT();
void publishMQTT(const char* topic, const char* payload);