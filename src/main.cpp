#include <Arduino.h>
#include "config.h"

// We'll add these later
// #include "secrets.h"
// #include "display_manager.h"
// #include "sensor_manager.h"
// #include "ai_decision.h"
// #include "wifi_manager.h"
// #include "relay_manager.h"

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
    // Initialize serial for debugging
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("========================================");
    Serial.println("  ESP32-C3 Smart Lighting System");
    Serial.println("  Version: 0.1.0 (Foundation)");
    Serial.println("========================================");
    Serial.println();
    
    // Initialize hardware
    initHardware();
    
    Serial.println("✅ Setup complete!");
    Serial.println("📡 Waiting for loop...");
    Serial.println();
}

// ============================================
// LOOP
// ============================================

void loop() {
    // Print status every 5 seconds
    if (millis() - lastSerialPrint > 5000) {
        lastSerialPrint = millis();
        printStatus();
    }
    
    // Small delay to prevent watchdog issues
    delay(10);
}

// ============================================
// HARDWARE INITIALIZATION
// ============================================

void initHardware() {
    Serial.println("🔧 Initializing hardware...");
    
    // Configure pins
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    
    // Set initial states
    digitalWrite(RELAY_PIN, LOW);  // Relay OFF by default
    
    // Print pin configuration
    Serial.println("   Pin configuration:");
    Serial.printf("   - LDR:      GPIO%d (ADC)\n", LDR_PIN);
    Serial.printf("   - DS18B20:  GPIO%d (OneWire)\n", DS18B20_PIN);
    Serial.printf("   - Relay:    GPIO%d (Output)\n", RELAY_PIN);
    Serial.printf("   - Switch:   GPIO%d (Input Pull-up)\n", SWITCH_PIN);
    Serial.printf("   - OLED SDA: GPIO%d (I2C)\n", OLED_SDA);
    Serial.printf("   - OLED SCL: GPIO%d (I2C)\n", OLED_SCL);
    Serial.println();
    
    // Read initial sensor values
    int ldrValue = analogRead(LDR_PIN);
    int switchState = digitalRead(SWITCH_PIN);
    
    Serial.println("📊 Initial readings:");
    Serial.printf("   - LDR value:    %d\n", ldrValue);
    Serial.printf("   - Switch:       %s\n", switchState ? "RELEASED" : "PRESSED");
    Serial.printf("   - Relay:        %s\n", digitalRead(RELAY_PIN) ? "ON" : "OFF");
    Serial.println();
}

// ============================================
// STATUS PRINTING
// ============================================

void printStatus() {
    Serial.println("----------------------------------------");
    Serial.println("📊 SYSTEM STATUS");
    Serial.println("----------------------------------------");
    
    // Read current values
    int ldrValue = analogRead(LDR_PIN);
    int switchState = digitalRead(SWITCH_PIN);
    int relayState = digitalRead(RELAY_PIN);
    
    // Determine LDR status
    String ldrStatus;
    if (ldrValue < LIGHT_ON_THRESHOLD) {
        ldrStatus = "DRK (Dark)";
    } else if (ldrValue > LIGHT_OFF_THRESHOLD) {
        ldrStatus = "BRT (Bright)";
    } else {
        ldrStatus = "NRM (Normal)";
    }
    
    // Print status
    Serial.printf("   ⏰ Uptime:   %lu seconds\n", millis() / 1000);
    Serial.printf("   💡 LDR:      %d (%s)\n", ldrValue, ldrStatus.c_str());
    Serial.printf("   🔦 Relay:    %s\n", relayState ? "ON" : "OFF");
    Serial.printf("   🔘 Switch:   %s\n", switchState ? "RELEASED" : "PRESSED");
    
    // Decision hierarchy info
    Serial.println("   📋 Decision: [MANUAL → AI → LDR]");
    if (switchState == LOW) {
        Serial.println("   🟡 MANUAL OVERRIDE ACTIVE!");
    } else {
        Serial.println("   ⚪ Waiting for AI decision (coming soon)");
    }
    Serial.println("----------------------------------------");
    Serial.println();
}