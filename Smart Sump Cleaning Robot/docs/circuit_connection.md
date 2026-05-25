# ⚡ Circuit Connection Guide

## Smart Water Sump Cleaning Robot

---

## Overview

```
12V Battery
    │
    ├──▶ BMS (Battery Management System)
    │        └──▶ PDB (Power Distribution Board)
    │                  ├──▶ Motor Driver L298N (+12V)
    │                  ├──▶ Relay Module COM
    │                  └──▶ DC-DC Buck Converter (12V → 5V)
    │                              ├──▶ ESP32 VIN
    │                              └──▶ Raspberry Pi 5V pin
    │
    └──▶ Common GND (all modules share this ground)
```

---

## Module-by-Module Wiring

### 1. Motor Driver (L298N)

| L298N Terminal | Connection |
|---------------|------------|
| +12V | 12V Battery positive |
| GND | Common GND |
| IN1 | ESP32 GPIO 25 |
| IN2 | ESP32 GPIO 26 |
| IN3 | ESP32 GPIO 27 |
| IN4 | ESP32 GPIO 14 |
| ENA | ESP32 GPIO 32 (PWM) |
| ENB | ESP32 GPIO 33 (PWM) |
| OUT1 / OUT2 | DC Motor A (Left) |
| OUT3 / OUT4 | DC Motor B (Right) |

---

### 2. Relay Module (3-channel)

| Relay Channel | Control Pin | Load Device |
|--------------|-------------|-------------|
| Channel 1 | ESP32 GPIO 18 | Submersible Water Pump |
| Channel 2 | ESP32 GPIO 19 | Suction Pump |
| Channel 3 | ESP32 GPIO 23 | Rotary Brush Motor |

**Load Side Wiring (per channel):**

```
Battery (+) ──▶ Relay COM
Relay NO    ──▶ Device (+)
Device (-)  ──▶ Battery GND
```

**Relay Power:**
- VCC → 5V (from buck converter)
- GND → Common GND

---

### 3. Ultrasonic Sensor (HC-SR04)

| HC-SR04 Pin | Connection |
|------------|------------|
| VCC | 5V |
| GND | Common GND |
| TRIG | ESP32 GPIO 5 |
| ECHO | Voltage divider → ESP32 GPIO 17 |

**⚠️ ECHO Voltage Divider (5V → 3.3V):**

```
ECHO ──▶ 1kΩ ──▶ GPIO 17
                    │
                   2kΩ
                    │
                   GND
```

---

### 4. IR Sensors (×2)

| IR Sensor | Pin | Connection |
|-----------|-----|------------|
| Left IR | VCC | 3.3V |
| Left IR | GND | Common GND |
| Left IR | OUT | ESP32 GPIO 34 |
| Right IR | VCC | 3.3V |
| Right IR | GND | Common GND |
| Right IR | OUT | ESP32 GPIO 35 |

---

### 5. pH Sensor (Optional)

| pH Sensor Pin | Connection |
|--------------|------------|
| VCC | 5V |
| GND | Common GND |
| Analog OUT | ESP32 GPIO 36 |

---

### 6. ESP32 ↔ Raspberry Pi (UART)

| Raspberry Pi GPIO | ESP32 GPIO |
|------------------|-----------|
| GPIO14 (TX) | GPIO16 (RX2) |
| GPIO15 (RX) | GPIO17 (TX2) |
| GND | GND (Common) |

> Both boards **must share a common ground**.

---

### 7. Camera Module (Optional)

- Connect to Raspberry Pi **CSI ribbon cable port**

---

### 8. Power Supply

Use **LM2596 Buck Converter**:

```
12V Battery (+) ──▶ Buck Converter IN+
12V Battery (-) ──▶ Buck Converter IN- (GND)
Buck OUT (5V)   ──▶ ESP32 VIN
Buck OUT (5V)   ──▶ Raspberry Pi 5V pin
Buck GND        ──▶ Common GND
```

---

## ✅ Final Wiring Checklist

- [ ] All GNDs connected together (common ground)
- [ ] ESP32 powered with 5V only (never 12V directly)
- [ ] HC-SR04 ECHO connected via voltage divider
- [ ] Pumps controlled only through relay module
- [ ] Motors controlled only through L298N
- [ ] Buck converter output verified at 5V before connecting
- [ ] Relay load side wired correctly (COM → NO → Device)
