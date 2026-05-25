# 📌 Pin Connections Reference

## Smart Water Sump Cleaning Robot

---

## ESP32 Complete Pin Map

| GPIO | Direction | Connected To | Notes |
|------|-----------|-------------|-------|
| GPIO 5 | OUTPUT | Ultrasonic TRIG | HC-SR04 trigger |
| GPIO 14 | OUTPUT | L298N IN4 | Motor B direction |
| GPIO 16 | INPUT | Pi GPIO14 (TX) | UART RX2 from Raspberry Pi |
| GPIO 17 | INPUT | Ultrasonic ECHO | Via 1kΩ+2kΩ voltage divider |
| GPIO 17 | OUTPUT | Pi GPIO15 (RX) | UART TX2 to Raspberry Pi |
| GPIO 18 | OUTPUT | Relay Ch1 | Water pump control |
| GPIO 19 | OUTPUT | Relay Ch2 | Suction pump control |
| GPIO 23 | OUTPUT | Relay Ch3 | Brush motor control |
| GPIO 25 | OUTPUT | L298N IN1 | Motor A direction |
| GPIO 26 | OUTPUT | L298N IN2 | Motor A direction |
| GPIO 27 | OUTPUT | L298N IN3 | Motor B direction |
| GPIO 32 | OUTPUT | L298N ENA | Motor A PWM speed |
| GPIO 33 | OUTPUT | L298N ENB | Motor B PWM speed |
| GPIO 34 | INPUT | IR Sensor Left OUT | 3.3V logic |
| GPIO 35 | INPUT | IR Sensor Right OUT | 3.3V logic |
| GPIO 36 | INPUT | pH Sensor Analog OUT | ADC input (optional) |
| VIN | POWER | Buck Converter 5V OUT | 5V regulated supply |
| GND | POWER | Common GND | Shared with all modules |

---

## Raspberry Pi GPIO Map

| GPIO | Direction | Connected To | Notes |
|------|-----------|-------------|-------|
| GPIO14 (TX) | OUTPUT | ESP32 GPIO16 (RX2) | UART transmit |
| GPIO15 (RX) | INPUT | ESP32 GPIO17 (TX2) | UART receive |
| GND | POWER | ESP32 GND | Common ground |
| 5V pin | POWER | Buck Converter 5V | Power input |
| CSI port | — | Camera Module | Ribbon cable |

---

## L298N Motor Driver Pin Map

| L298N Pin | Connected To |
|-----------|-------------|
| +12V | 12V Battery (+) |
| GND | Common GND |
| IN1 | ESP32 GPIO 25 |
| IN2 | ESP32 GPIO 26 |
| IN3 | ESP32 GPIO 27 |
| IN4 | ESP32 GPIO 14 |
| ENA | ESP32 GPIO 32 |
| ENB | ESP32 GPIO 33 |
| OUT1 | DC Motor A (+) |
| OUT2 | DC Motor A (-) |
| OUT3 | DC Motor B (+) |
| OUT4 | DC Motor B (-) |

---

## Relay Module Pin Map

| Relay Pin | Connected To |
|-----------|-------------|
| VCC | 5V (Buck Converter) |
| GND | Common GND |
| IN1 | ESP32 GPIO 18 |
| IN2 | ESP32 GPIO 19 |
| IN3 | ESP32 GPIO 23 |
| COM1 | Battery (+) |
| NO1 | Water Pump (+) |
| COM2 | Battery (+) |
| NO2 | Suction Pump (+) |
| COM3 | Battery (+) |
| NO3 | Brush Motor (+) |

---

## Sensor Pin Map

### HC-SR04 Ultrasonic Sensor

| Sensor Pin | Connected To |
|-----------|-------------|
| VCC | 5V |
| GND | Common GND |
| TRIG | ESP32 GPIO 5 |
| ECHO | 1kΩ resistor → ESP32 GPIO 17 → 2kΩ → GND |

### IR Sensors

| Sensor Pin | Left IR | Right IR |
|-----------|---------|----------|
| VCC | 3.3V | 3.3V |
| GND | Common GND | Common GND |
| OUT | ESP32 GPIO 34 | ESP32 GPIO 35 |

### pH Sensor (Optional)

| Sensor Pin | Connected To |
|-----------|-------------|
| VCC | 5V |
| GND | Common GND |
| Analog OUT | ESP32 GPIO 36 |

---

## Motor Direction Truth Table

| IN1 | IN2 | Motor A |
|-----|-----|---------|
| HIGH | LOW | Forward |
| LOW | HIGH | Backward |
| LOW | LOW | Stop |

| IN3 | IN4 | Motor B |
|-----|-----|---------|
| HIGH | LOW | Forward |
| LOW | HIGH | Backward |
| LOW | LOW | Stop |

### Robot Movement

| Action | Motor A | Motor B |
|--------|---------|---------|
| Forward | Forward | Forward |
| Backward | Backward | Backward |
| Turn Left | Backward | Forward |
| Turn Right | Forward | Backward |
| Stop | Stop | Stop |
