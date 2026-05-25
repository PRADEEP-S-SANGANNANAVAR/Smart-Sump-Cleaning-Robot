# 🤖 Smart Water Sump Cleaning Robot Using AI and IoT

<div align="center">

![Robot Banner](https://img.shields.io/badge/Project-Smart%20Sump%20Cleaning%20Robot-blue?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-ESP32%20%2B%20Raspberry%20Pi-green?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%7C%20Python-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

**An autonomous robot that cleans underground water sump tanks without human intervention using AI, IoT, and embedded systems.**

</div>

---

## 📋 Table of Contents

- [About the Project](#-about-the-project)
- [Problem Statement](#-problem-statement)
- [Proposed Solution](#-proposed-solution)
- [Features](#-features)
- [Components Required](#-components-required)
- [System Architecture](#-system-architecture)
- [3D Design](#-3d-design)
- [Circuit Connection](#-circuit-connection)
- [Pin Connections](#-pin-connections)
- [Working Mechanism](#-working-mechanism)
- [Code Structure](#-code-structure)
- [Getting Started](#-getting-started)
- [Experimental Results](#-experimental-results)
- [Future Scope](#-future-scope)
- [Author](#-author)
- [License](#-license)

---

## 📖 About the Project

Water sump tanks accumulate mud, algae, rust, and other waste materials over time. Manual cleaning of sump tanks is unsafe, time-consuming, and requires human entry into confined spaces.

This project proposes an **Automatic Sump Cleaning Robot** that can clean sump tanks without human intervention. The robot is designed using **Raspberry Pi + ESP32**, motors, wheels, water pump, suction pump, and cleaning mechanisms.

> **Institution:** HKBK College Of Engineering  
> **Department:** Electronics and Communication Engineering  
> **Submitted by:** Pradeep S Sangannanavr (USN: 1HK22EC122)  
> **Semester:** 8th

---

## ❗ Problem Statement

| Problem | Description |
|--------|-------------|
| ⚠️ Unsafe Process | Manual cleaning requires human entry into confined spaces |
| ☠️ Health Risks | Exposure to toxic gases inside sump tanks |
| ⏱️ Time Consuming | Manual cleaning takes significant time and effort |
| 🧹 Incomplete Cleaning | Sludge and algae not fully removed manually |
| 🔧 No Automation | Lack of automated sump maintenance systems |

---

## ✅ Proposed Solution

The Automatic Sump Cleaning Robot provides a comprehensive solution:

- 🛡️ **Enhanced Safety** — Eliminates human entry into hazardous confined spaces
- ⚡ **Efficiency and Speed** — Faster and more thorough than manual cleaning
- 🧽 **Effective Cleaning** — Mechanical brushes and suction for complete sludge/algae/rust removal
- 🤖 **Automation** — Raspberry Pi + ESP32 with sensors for autonomous navigation
- 🗑️ **Waste Management** — Pumps collected waste water outside the sump

---

## ✨ Features

- [x] Autonomous navigation inside sump tank
- [x] Sludge and mud removal
- [x] Algae and rust cleaning via rotary brush
- [x] Clean water spraying to loosen dirt
- [x] Dirty water suction and disposal
- [x] Obstacle detection using Ultrasonic + IR sensors
- [x] Wi-Fi based remote control via web UI
- [x] pH level monitoring (optional)
- [x] Camera module for visual inspection (optional)
- [x] Auto mode with collision avoidance

---

## 🔩 Components Required

| Sl. No | Component | Description |
|--------|-----------|-------------|
| 1 | Raspberry Pi + ESP32 | Main controller |
| 2 | Motor Driver (L298N) | Controls DC motors |
| 3 | DC Motors (High Torque) | Robot movement |
| 4 | Heavy Grip Wheels / Crawler Tracks | Movement on wet surface |
| 5 | Submersible Water Pump | Spraying clean water |
| 6 | Suction Pump | Removes dirty water |
| 7 | Rotary Brush Motor | Scrubbing surface |
| 8 | Relay Module | Controls pumps |
| 9 | Battery (12V) | Power supply |
| 10 | Ultrasonic Sensor + IR Sensors | Obstacle detection |
| 11 | Waterproof Chassis (IP65/67) | Robot body |
| 12 | Pipes and Nozzles | Water flow system |
| 13 | Wi-Fi / Bluetooth Module | Wireless communication (Optional) |
| 14 | Camera Module (Waterproof) | Visual inspection and monitoring (Optional) |
| 15 | pH Sensor | Measures water acidity/alkalinity (Optional) |

---

## 🏗️ System Architecture

### Block Diagram

```
┌─────────────┐     ┌──────────────────────────────────────────────────────┐
│  12V Battery│────▶│                  Waterproof Chassis                   │
└─────────────┘     │                                                        │
                    │  ┌──────────┐   ┌──────────────┐   ┌───────────────┐ │
                    │  │   BMS    │──▶│     PDB      │──▶│ DC-DC Buck 5V │ │
                    │  └──────────┘   └──────────────┘   └───────┬───────┘ │
                    │                                             │         │
                    │                                    ┌────────▼───────┐ │
                    │  ┌──────────────┐                  │ Raspberry Pi   │ │
                    │  │ Motor Driver │◀─────────────────│   + ESP32      │ │
                    │  │   (L298N)    │                  └────────┬───────┘ │
                    │  └──────┬───────┘                          │         │
                    │         │                         ┌─────────▼───────┐ │
                    │  ┌──────▼───────┐                 │  Relay Module   │ │
                    │  │  DC Motors   │                 └─────────┬───────┘ │
                    │  │(Wheels/Track)│          ┌──────┬─────────┼───────┐ │
                    │  └─────────────┘        Water  Suction  Rotary  Wi-Fi│ │
                    │                         Pump   Pump    Brush   /BT   │ │
                    │  Sensors:                                    Module  │ │
                    │  • Ultrasonic + IR                                   │ │
                    │  • pH Sensor                                         │ │
                    │  • Camera (Optional)                                 │ │
                    └─────────────────────────────────────────────────────┘
```

### Flowchart

```
START
  │
  ▼
Power ON (12V Battery)
  │
  ▼
Initialize ESP32 / Raspberry Pi
  │
  ▼
Initialize Sensors (Ultrasonic + IR + pH)
  │
  ▼
Check WiFi / Communication
  │
  ▼
Obstacle Detected? ──YES──▶ Stop Motors & Change Direction
  │ NO                              │
  ▼                                 │
Continue Forward ◀──────────────────┘
  │
  ▼
Activate Cleaning System
  ├──▶ Submersible Pump ON (Spray Clean Water)
  ├──▶ Rotary Brush Motor ON (Scrub Dirt)
  └──▶ Suction Pump ON (Remove Dirty Water)
  │
  ▼
Check Water pH Level
  │
  ▼
Send Data via WiFi / Camera Monitoring
  │
  ▼
Cleaning Completed? ──NO──▶ Repeat Cleaning
  │ YES
  ▼
Stop Robot ──▶ END
```

---

## 🎨 3D Design

The robot was designed and modeled in **Tinkercad**. The design features crawler tracks for wet surface movement, rotary brushes for scrubbing, and a sealed electronics enclosure.

> 🔗 **[👉 Click here to View & Explore the 3D Design on Tinkercad](https://www.tinkercad.com/things/gE63VaFeCaL-smart-sump-cleaning-robot-using-ai-and-iot?sharecode=1_soEt63CaqbMbnYa5QZz6g156Uk6iV0MGfUCIPT7fA)**

### Design Highlights

| Feature | Detail |
|---------|--------|
| Chassis | IP65/67 Waterproof sealed body |
| Locomotion | Crawler tracks for wet/slippery surfaces |
| Brushes | 2× Rotary brush motors (front) |
| Sensors | Ultrasonic (US) + IR sensors on all sides |
| Electronics | Sealed central enclosure with Raspberry Pi + ESP32 |
| Waste Tank | Onboard waste collection tank |

---

## ⚡ Circuit Connection

The full circuit connects the following modules to the ESP32:

```
12V Battery ──▶ Motor Driver (L298N) ──▶ DC Motors
           └──▶ Relay Module ──▶ Water Pump / Suction Pump / Brush Motor
           └──▶ Buck Converter (5V) ──▶ ESP32 + Raspberry Pi

ESP32 ◀──▶ Ultrasonic Sensor (HC-SR04)
      ◀──▶ IR Sensors (Left + Right)
      ◀──▶ pH Sensor (Analog)
      ◀──▶ Raspberry Pi (UART)
```

> See [`docs/circuit_connection.md`](docs/circuit_connection.md) for the full detailed wiring.

---

## 📌 Pin Connections

### ESP32 ↔ Raspberry Pi (UART)

| Raspberry Pi | ESP32 |
|-------------|-------|
| GPIO14 (TX) | GPIO16 (RX2) |
| GPIO15 (RX) | GPIO17 (TX2) |
| GND | GND (Common) |

### Motor Driver (L298N)

| L298N Pin | ESP32 GPIO |
|-----------|-----------|
| IN1 | GPIO 25 |
| IN2 | GPIO 26 |
| IN3 | GPIO 27 |
| IN4 | GPIO 14 |
| ENA | GPIO 32 (PWM) |
| ENB | GPIO 33 (PWM) |

### Relay Module

| Device | ESP32 GPIO |
|--------|-----------|
| Water Pump | GPIO 18 |
| Suction Pump | GPIO 19 |
| Brush Motor | GPIO 23 |

### Sensors

| Sensor | ESP32 GPIO | Notes |
|--------|-----------|-------|
| Ultrasonic TRIG | GPIO 5 | — |
| Ultrasonic ECHO | GPIO 17 | Via voltage divider (1kΩ + 2kΩ) |
| IR Left OUT | GPIO 34 | 3.3V supply |
| IR Right OUT | GPIO 35 | 3.3V supply |
| pH Sensor (Analog) | GPIO 36 | Optional |

> ⚠️ **Important:** The HC-SR04 ECHO pin outputs 5V. Always use a voltage divider to protect the ESP32's 3.3V GPIO.

> See [`docs/pin_connections.md`](docs/pin_connections.md) for the complete reference.

---

## ⚙️ Working Mechanism

1. **Placement** — Robot is placed inside the sump tank
2. **Movement** — High-torque DC motors drive crawler tracks across the tank floor
3. **Scrubbing** — Rotary brush motor scrubs mud, algae, and rust from surfaces
4. **Spraying** — Submersible pump sprays clean water to loosen dirt
5. **Suction** — Suction pump removes dirty water and sludge through pipes to outside
6. **Obstacle Avoidance** — Ultrasonic + IR sensors detect walls and redirect the robot
7. **Monitoring** — pH sensor checks water quality; camera streams live video (optional)
8. **Remote Control** — Wi-Fi web UI allows manual override and real-time monitoring

---

## 📁 Code Structure

```
smart-sump-cleaning-robot/
│
├── README.md                           # Project documentation
├── LICENSE                             # MIT License
├── .gitignore                          # Git ignore rules
│
├── esp32/
│   └── sump_robot/
│       └── sump_robot.ino              # ESP32 Arduino sketch
│
├── raspberry_pi/
│   └── controller.py                   # Raspberry Pi Python control script
│
├── docs/
│   ├── circuit_connection.md           # Detailed circuit wiring guide
│   └── pin_connections.md              # Full pin reference table
│
└── assets/                             # Images and diagrams
    ├── block_diagram.png
    ├── flowchart.png
    ├── circuit_diagram.png
    ├── 2d_diagram.png
    └── 3d_design.png
```

---

## 🚀 Getting Started

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support
- Python 3.x on Raspberry Pi
- `requests` library: `pip install requests`

### 1. ESP32 Setup

1. Install [ESP32 board support](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) in Arduino IDE
2. Open `esp32/sump_robot/sump_robot.ino`
3. Update your WiFi credentials:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
4. Select board: **ESP32 Dev Module**, then upload

### 2. Raspberry Pi Setup

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/smart-sump-cleaning-robot.git
cd smart-sump-cleaning-robot

# Install dependencies
pip install requests

# Update ESP32 IP in controller.py, then run
python raspberry_pi/controller.py
```

### 3. Web UI Control

Once the ESP32 connects to WiFi, open a browser and go to the ESP32's IP address. The web interface provides:

| Button | Action |
|--------|--------|
| Forward / Back / Left / Right | Manual movement |
| Stop | Halt all motors |
| Clean ON | Start water pump + suction + brush |
| Clean OFF | Stop all cleaning mechanisms |
| Auto Mode | Autonomous cleaning with obstacle avoidance |

---

## 🧪 Experimental Results

The robot was tested inside a small water tank environment:

| Test | Result |
|------|--------|
| Mud and sludge removal | ✅ Passed |
| Algae cleaning from tank surface | ✅ Passed |
| Dirty water pumping | ✅ Passed |
| Operation without human entry | ✅ Passed |
| Cleaning time reduction | ✅ Significant improvement |
| Stability under wet conditions | ✅ Stable |

---

## 🔮 Future Scope

| Enhancement | Description |
|-------------|-------------|
| 🗺️ Advanced Navigation | SLAM for complex sump geometries |
| 🔋 Improved Power | Induction charging or longer-lasting batteries |
| 🛡️ Material Durability | Corrosion-resistant and marine-grade materials |
| 🦠 Automated Disinfection | UV-C light or non-toxic chemical dispenser post-cleaning |
| 📱 Mobile App | Dedicated Android/iOS app for remote monitoring |
| 🧠 AI Path Planning | ML-based optimal path planning for full coverage |
| 🧱 Wall Climbing | Automatic wall-cleaning mechanism |

---

## 👤 Author

**Pradeep S Sangannanavr**  
USN: 1HK22EC122  
Department of Electronics and Communication Engineering  
HKBK College Of Engineering

---

## 📄 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

<div align="center">

Made with ❤️ for safer and smarter water tank maintenance

⭐ **Star this repo if you found it helpful!**

</div>
