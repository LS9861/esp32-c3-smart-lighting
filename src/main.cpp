#include <Arduino.h>
#include "config.h"
#include "sensor_manager.h"

// ============================================
// GLOBAL VARIABLES
// ============================================

unsigned long lastSerialPrint = 0;

// ============================================
// FUNCTION PROTOTYPES
// ============================================

void initHardware();
void printStatus();

// ============================================
// SETUP
// ============================================

void setup() {
    // Initialize serial
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("========================================");
    Serial.println("  ESP32-C3 Smart Lighting System");
    Serial.println("  Version: 0.2.0 (Sensor Manager)");
    Serial.println("========================================");
    Serial.println();
    
    // Initialize hardware
    initHardware();
    
    // Initialize sensor manager
    sensorManager.begin();
    
    Serial.println("✅ Setup complete!");
    Serial.println("📡 Waiting for loop...");
    Serial.println();
}

// ============================================
// LOOP
// ============================================

void loop() {
    // Update sensors
    sensorManager.updateLDR();
    
    // Print status every 5 seconds
    if (millis() - lastSerialPrint > 5000) {
        lastSerialPrint = millis();
        printStatus();
    }
    
    // Small delay
    delay(100);
}

// ============================================
// HARDWARE INITIALIZATION
// ============================================

void initHardware() {
    Serial.println("🔧 Initializing hardware...");
    
    // Configure pins
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    pinMode(LDR_PIN, INPUT);
    
    // Set initial states
    digitalWrite(RELAY_PIN, LOW);
    
    // Print pin configuration
    Serial.println("   Pin configuration:");
    Serial.printf("   - LDR:      GPIO%d (ADC)\n", LDR_PIN);
    Serial.printf("   - DS18B20:  GPIO%d (OneWire) [Coming soon]\n", DS18B20_PIN);
    Serial.printf("   - Relay:    GPIO%d (Output)\n", RELAY_PIN);
    Serial.printf("   - Switch:   GPIO%d (Input Pull-up)\n", SWITCH_PIN);
    Serial.printf("   - OLED SDA: GPIO%d (I2C) [Coming soon]\n", OLED_SDA);
    Serial.printf("   - OLED SCL: GPIO%d (I2C) [Coming soon]\n", OLED_SCL);
    Serial.println();
}

// ============================================
// STATUS PRINTING
// ============================================

void printStatus() {
    Serial.println("----------------------------------------");
    Serial.println("📊 SYSTEM STATUS");
    Serial.println("----------------------------------------");
    
    // Get LDR reading
    int ldrValue = sensorManager.getLastLDR();
    String ldrStatus = sensorManager.getLastLDRStatus();
    
    // Read switch state
    int switchState = digitalRead(SWITCH_PIN);
    int relayState = digitalRead(RELAY_PIN);
    
    // Print status
    Serial.printf("   ⏰ Uptime:   %lu seconds\n", millis() / 1000);
    Serial.printf("   💡 LDR:      %d (%s)\n", ldrValue, ldrStatus.c_str());
    Serial.printf("   🔦 Relay:    %s\n", relayState ? "ON" : "OFF");
    Serial.printf("   🔘 Switch:   %s\n", switchState ? "RELEASED" : "PRESSED");
    
    // Sensor status
    Serial.println("   📋 Sensors:");
    Serial.printf("      - LDR threshold: ON=%d, OFF=%d\n", LIGHT_ON_THRESHOLD, LIGHT_OFF_THRESHOLD);
    Serial.printf("      - Hysteresis: %d\n", LDR_HYSTERESIS);
    
    // Decision info
    Serial.println("   📋 Decision: [MANUAL → AI → LDR]");
    if (switchState == LOW) {
        Serial.println("   🟡 MANUAL OVERRIDE ACTIVE!");
    } else {
        // Show what AI would decide based on LDR
        if (ldrValue < LIGHT_ON_THRESHOLD) {
            Serial.println("   💡 AI would turn ON (Dark)");
        } else if (ldrValue > LIGHT_OFF_THRESHOLD) {
            Serial.println("   ☀️ AI would turn OFF (Bright)");
        } else {
            Serial.println("   ⚪ AI would maintain state (Normal)");
        }
    }
    Serial.println("----------------------------------------");
    Serial.println();
}