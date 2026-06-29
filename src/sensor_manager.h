#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include "config.h"

// ============================================
// CLASS DECLARATION
// ============================================

class SensorManager {
public:
    // Constructor
    SensorManager();
    
    // Initialize sensors
    void begin();
    
    // Read LDR value (0-4095 for ESP32-C3)
    int readLDR();
    
    // Get LDR status as string (BRT/DRK/NRM)
    String getLDRStatus(int ldrValue);
    
    // Get LDR status with hysteresis
    String getLDRStatusWithHysteresis();
    
    // Update LDR reading (stores last value)
    void updateLDR();
    
    // Get last LDR reading
    int getLastLDR() const { return _lastLDR; }
    
    // Get current LDR status string
    String getLastLDRStatus() const { return _lastLDRStatus; }
    
    // Check if it's dark (LDR < threshold)
    bool isDark();
    
    // Check if it's bright (LDR > threshold)
    bool isBright();

private:
    int _lastLDR;                 // Last LDR reading
    String _lastLDRStatus;        // Last LDR status
    unsigned long _lastReadTime;  // Last read time
    int _stableLDR;              // Stable reading with hysteresis
    
    // Apply hysteresis to prevent rapid toggling
    int applyHysteresis(int newValue);
};

// ============================================
// GLOBAL INSTANCE
// ============================================

extern SensorManager sensorManager;

#endif