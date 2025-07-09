# 🔧 My Personal IoT Systems

This repository contains various IoT projects built for learning, experimentation, and practical applications. Each subfolder includes project-specific code, documentation, and hardware integration.

---

## 📋 Project Status Overview

| Project                               | Status           | Description                                               |
|---------------------------------------|------------------|-----------------------------------------------------------|
| Smart Plant Watering System           | ✅ Done           | Automatically waters plants based on soil moisture level. |
| Temperature Display System            | ✅ Done           | Shows real-time room temperature using DHT sensor.        |
| PID Line Follower                     | 🚧 In Progress    | Follows black lines using PID algorithm and IR sensors.   |
| Bluetooth Control Car                 | 🚧 In Progress    | Controlled wirelessly via phone over Bluetooth.           |
| Life-Logging Camera                   | ⚙️ Prototype      | Takes photos at intervals using ESP32-CAM.                |
| Object Avoidance Car                 | ❌ Not Started    | Avoids obstacles using ultrasonic sensors.                |

---

## 📦 Common Components Used

- Arduino UNO / Nano / ESP32 / ESP32-CAM
- DHT22 Temperature & Humidity Sensor
- Ultrasonic Sensor (HC-SR04)
- Soil Moisture Sensor
- L298N Motor Driver
- IR Sensor (TCRT5000)
- Servo Motor (SG90)
- DC BO Motors
- LCD Display (I2C-based)
- Bluetooth Module (HC-05)
- Jumper Wires, Breadboard
- 9V / 7.4V Batteries or 5V Adapter
- SD Card (ESP32-CAM)
- Resistors (10kΩ, etc.)

---

## 📂 Project Setup

Each project folder contains:

- `README.md`: Specific setup and circuit details
- `code.ino` or `main.cpp`: Arduino/ESP32 code
- `circuit_diagram.png`: Wiring and schematics (if available)
- `LICENSE`: Project license (MIT)

To get started:

1. Open the folder of the desired project.
2. Read the project-specific `README.md`.
3. Upload the code to your Arduino/ESP32.
4. Build the circuit using the schematic.
5. Power the device and monitor via Serial Monitor or display.

---

## 🚀 Getting Started

You can clone the repository using:

```bash
git clone https://github.com/rajjitlai/home-iot-systems.git
cd home-iot-systems
```

Choose any project folder and follow the instructions inside.

---

## 🎯 Extra: Competitions & Exhibitions

Some of these projects have been used or showcased in various tech competitions and hardware exhibitions. More information will be added in future updates.

## 📜 License

This project is licensed under the **MIT License**.  
You are free to use, modify, and distribute this project with proper attribution.

## 🙌 Credits

Created and developed by [Rajjit Laishram](https://rajjitlaishram.netlify.app/).  
Special thanks to the Arduino and open-source robotics communities.
