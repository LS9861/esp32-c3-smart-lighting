# ESP32-C3 Smart Lighting System

[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32--C3-blue)](https://platformio.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![DeepSeek](https://img.shields.io/badge/AI-DeepSeek-purple)](https://deepseek.com/)

## 🏠 Overview

A complete smart lighting system for **ESP32-C3 Super Mini** with AI-powered decisions using DeepSeek API. This project demonstrates professional IoT development with PlatformIO.

### ✨ Features

- **🤖 AI Decision Engine**: Uses DeepSeek API for intelligent lighting decisions
- **📱 Remote Control**: Monitor and control via Blynk mobile app
- **🖥️ OLED Display**: Clean, compact 128x64 screen with Room & City info
- **🔦 Multi-layer Fallback**: Manual Switch → AI → LDR (redundant safety)
- **🌡️ Environmental Monitoring**: Temperature & light level tracking
- **📊 City Information**: Display time, weather, and conditions
- **🔒 Secure**: Secrets handled via separate file (gitignored)

### 🎯 Decision Hierarchy
1. Manual Switch (HIGHEST PRIORITY)
└── Override everything, relay ON

2. DeepSeek AI Decision
└── Contextual decision based on time, weather, location

3. LDR Fallback (LOWEST PRIORITY)
└── Light threshold: Dark=ON, Bright=OFF


## 🛠️ Hardware Requirements

- **ESP32-C3 Super Mini**
- **SSD1306 OLED** 128x64 (I2C)
- **LDR Sensor** (Analog)
- **DS18B20 Temperature Sensor** (OneWire)
- **5V Relay Module**
- **Push Button Switch** (Manual override)

## 📡 Wiring Diagram

| Component | ESP32-C3 Pin | Notes |
|-----------|--------------|-------|
| OLED SDA | GPIO5 | I2C Data |
| OLED SCL | GPIO6 | I2C Clock |
| LDR | GPIO0 | ADC Input |
| DS18B20 | GPIO7 | OneWire Data |
| Relay | GPIO8 | Digital Output |
| Manual Switch | GPIO9 | INPUT_PULLUP |

## 🚀 Getting Started

### Prerequisites

- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode)
- Git (for cloning)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/esp32-c3-smart-lighting.git
   cd esp32-c3-smart-lighting