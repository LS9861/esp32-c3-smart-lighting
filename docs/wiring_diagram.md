# Wiring Diagram

## ESP32-C3 Super Mini Pinout
┌─────────────────┐
│ ESP32-C3 │
│ Super Mini │
│ │
GND ────────────►│ GND │
3.3V ───────────►│ 3V3 │
│ │
OLED SDA ───────►│ GPIO5 (SDA) │
OLED SCL ───────►│ GPIO6 (SCL) │
│ │
LDR Signal ─────►│ GPIO0 (ADC) │
│ │
DS18B20 Data ───►│ GPIO7 (1-Wire) │
│ │
Relay IN ───────►│ GPIO8 (Out) │
│ │
Switch Signal ──►│ GPIO9 (In) │
└─────────────────┘


## Component Connections

### OLED SSD1306 (I2C)
- VCC → 3.3V
- GND → GND
- SDA → GPIO5
- SCL → GPIO6
- Address: 0x3C

### LDR (Analog)
- VCC → 3.3V (with 10kΩ pull-up resistor)
- GND → GND
- Signal → GPIO0 (ADC)

### DS18B20 (Digital)
- VCC → 3.3V
- GND → GND
- Data → GPIO7 (with 4.7kΩ pull-up to 3.3V)

### Relay Module
- VCC → 5V (external power recommended)
- GND → GND
- IN → GPIO8

### Manual Switch (Momentary Push Button)
- One side → GPIO9
- Other side → GND
- Internal pull-up enabled

## Power Requirements
- ESP32-C3: 3.3V @ ~70-100mA
- OLED: 3.3V @ ~20mA
- Relay: 5V @ ~50mA
- DS18B20: 3.3V @ ~5mA
- LDR: 3.3V @ ~1mA

**Total**: ~150mA peak