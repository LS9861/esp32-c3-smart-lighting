#include "sensor_manager.h"

// ============================================
// CONSTRUCTOR
// ============================================

SensorManager::SensorManager() {
    _lastLDR = 0;
    _lastLDRStatus = "NRM";
    _lastReadTime = 0;
    _stableLDR = 0;
}

// ============================================
// INITIALIZATION
// ============================================

void SensorManager::begin() {
    Serial.println("📡 Initializing Sensor Manager...");
    
    // Configure LDR pin (already done in main.cpp, but safe to repeat)
    pinMode(LDR_PIN, INPUT);
    
    // Read initial value
    updateLDR();
    
    Serial.printf("   ✅ LDR initialized on GPIO%d\n", LDR_PIN);
    Serial.printf("   📊 Initial LDR value: %d (%s)\n", _lastLDR, _lastLDRStatus.c_str());
    Serial.println();
}

// ============================================
// READ LDR (RAW VALUE)
// ============================================

int SensorManager::readLDR() {
    // ESP32-C3 ADC is 12-bit (0-4095)
    // But GPIO0 is ADC1_CH0
    int rawValue = analogRead(LDR_PIN);
    
    // Optional: Add filtering (simple moving average)
    // For now, return raw value
    
    return rawValue;
}

// ============================================
// GET LDR STATUS (Without Hysteresis)
// ============================================

String SensorManager::getLDRStatus(int ldrValue) {
    if (ldrValue < LIGHT_ON_THRESHOLD) {
        return "DRK";  // Dark
    } else if (ldrValue > LIGHT_OFF_THRESHOLD) {
        return "BRT";  // Bright
    } else {
        return "NRM";  // Normal
    }
}

// ============================================
// GET LDR STATUS (With Hysteresis)
// ============================================

String SensorManager::getLDRStatusWithHysteresis() {
    int currentValue = readLDR();
    int stableValue = applyHysteresis(currentValue);
    
    return getLDRStatus(stableValue);
}

// ============================================
// APPLY HYSTERESIS
// ============================================

int SensorManager::applyHysteresis(int newValue) {
    // If we don't have a stable value yet, use the new one
    if (_stableLDR == 0) {
        _stableLDR = newValue;
        return _stableLDR;
    }
    
    // Calculate difference
    int diff = newValue - _stableLDR;
    
    // Only update if difference exceeds hysteresis threshold
    if (abs(diff) > LDR_HYSTERESIS) {
        _stableLDR = newValue;
    }
    
    return _stableLDR;
}

// ============================================
// UPDATE LDR (Store Last Reading)
// ============================================

void SensorManager::updateLDR() {
    // Read current value
    int rawValue = readLDR();
    
    // Apply hysteresis
    _lastLDR = applyHysteresis(rawValue);
    
    // Update status
    _lastLDRStatus = getLDRStatus(_lastLDR);
    
    // Update timestamp
    _lastReadTime = millis();
}

// ============================================
// CHECK IF DARK
// ============================================

bool SensorManager::isDark() {
    updateLDR();
    return (_lastLDR < LIGHT_ON_THRESHOLD);
}

// ============================================
// CHECK IF BRIGHT
// ============================================

bool SensorManager::isBright() {
    updateLDR();
    return (_lastLDR > LIGHT_OFF_THRESHOLD);
}

// ============================================
// GLOBAL INSTANCE
// ============================================

SensorManager sensorManager;