void setupGates();
void openGate(int gateId);
void closeGate(int gateId);
void antifreezeGate(int gateId, bool force = false);
void setAntifreezeSettings(unsigned long intervalMs, int pulseDurationMs);