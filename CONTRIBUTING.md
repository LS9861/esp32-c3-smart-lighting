# Contributing to ESP32-C3 Smart Lighting

We love your input! We want to make contributing as easy and transparent as possible.

## Development Process

1. Fork the repo and create your branch from `main`
2. If you've added code, add tests
3. Ensure the code works on ESP32-C3
4. Update documentation
5. Issue that pull request!

## Development Setup

```bash
# Clone your fork
git clone https://github.com/yourusername/esp32-c3-smart-lighting.git

# Install PlatformIO
# https://platformio.org/install/ide?install=vscode

# Install dependencies (auto-detected by PlatformIO)
# Just open the project in VS Code with PlatformIO extension

# Build
pio run

# Upload
pio run -t upload

# Monitor
pio device monitor