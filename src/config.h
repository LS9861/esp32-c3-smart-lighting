#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// PIN DEFINITIONS
// ============================================

// OLED Display (I2C)
#define OLED_SDA 5
#define OLED_SCL 6
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

// Sensors
#define LDR_PIN 0           // Analog input
#define DS18B20_PIN 7       // OneWire data

// Actuators
#define RELAY_PIN 8         // Digital output

// Manual Switch
#define SWITCH_PIN 9        // INPUT_PULLUP

// ============================================
// LDR THRESHOLDS
// ============================================

#define LIGHT_ON_THRESHOLD 250    // Below this = dark → relay ON
#define LIGHT_OFF_THRESHOLD 350   // Above this = bright → relay OFF
#define LDR_HYSTERESIS 30         // Prevents rapid toggling

// ============================================
// TIMING CONSTANTS
// ============================================

#define SCREEN_SWITCH_INTERVAL 5000      // 5 seconds
#define TEMPERATURE_READ_INTERVAL 2000   // 2 seconds
#define AI_UPDATE_INTERVAL 300000        // 5 minutes
#define DEEPSEEK_TIMEOUT 5000            // 5 seconds

// ============================================
// BLYNK VIRTUAL PINS
// ============================================

#define V0_TEMPERATURE 0
#define V1_RELAY_STATUS 1
#define V2_LDR_STATUS 2
#define V3_AI_STATUS 3
#define V4_MANUAL_OVERRIDE 4
#define V5_AI_DECISION 5
#define V6_DEEPSEEK_STATUS 6

#endif