# PID Line Follower Robot using Arduino Nano

This project demonstrates a 2WD PID-controlled line follower robot built using an Arduino Nano, TB6612FNG motor driver, 7-channel IR sensor array, and standard DC motors. The robot is capable of detecting and following black lines on various types of tracks using PID control for smooth turns and accuracy.

---

## 📦 Components Required

| Component                      | Quantity | Description                                 |
|-------------------------------|----------|---------------------------------------------|
| Arduino Nano                  | 1        | Microcontroller for control logic           |
| TB6612FNG Motor Driver        | 1        | Dual H-Bridge to control 2 motors           |
| DC Geared Motors (BO type)    | 2        | For driving the robot wheels                |
| Wheels                        | 2        | Compatible with BO motors                   |
| 7-Channel IR Sensor Array     | 1        | For line detection                          |
| 7.4V Li-ion/LiPo Battery Pack | 1        | Power source (recommended)                  |
| LM2596 Buck Converter         | 1        | To regulate 7.4V down to 5V                 |
| Breadboard                    | 1        | For prototyping and distributing 5V logic   |
| Jumper Wires                  | Several  | For connections                             |
| Battery Holder or Switch      | Optional | For easy control of power supply            |
| 4×1.2V AA Batteries (for testing only) | Optional | Temporary power source for testing       |

---

## ⚙️ Circuit Setup

The robot is powered by a 7.4V battery connected in two branches:

1. One branch powers the TB6612FNG motor driver’s VM pin directly (motor power).
2. The second branch is passed through an LM2596 buck converter to supply 5V regulated power to:
   - Arduino Nano (via 5V pin)
   - TB6612FNG VCC (logic power)
   - IR Sensor Array (5V and GND)

⚠️ Do not use the VIN pin when using a buck converter for 5V. Connect 5V directly to the Nano’s 5V pin.

🛠️ TB6612FNG Motor Driver Connections:

| TB6612FNG Pin | Arduino Nano Pin | Description                     |
|---------------|------------------|---------------------------------|
| PWMA          | D5               | PWM speed control for Motor A   |
| AIN1          | D4               | Direction control for Motor A   |
| AIN2          | D3               | Direction control for Motor A   |
| PWMB          | D6               | PWM speed control for Motor B   |
| BIN1          | D7               | Direction control for Motor B   |
| BIN2          | D8               | Direction control for Motor B   |
| STBY          | D9 or 5V         | Standby pin (pull HIGH to enable) |
| VCC           | 5V (from regulator) | Logic power supply           |
| VM            | 7.4V Battery +   | Motor power input               |
| GND           | GND (common)     | Ground                          |

🛠️ IR Sensor Connections:

| IR Sensor Pin | Arduino Nano Pin |
|---------------|------------------|
| S1            | A0               |
| S2            | A1               |
| S3            | A2               |
| S4            | A3               |
| S5            | A4               |
| S6            | A5               |
| S7            | A6               |
| VCC           | 5V               |
| GND           | GND              |

Ensure all GND connections are tied to a common ground (battery, Arduino, sensor, and motor driver).

---

## 💡 Features

- Uses PID algorithm to follow black lines precisely.
- Supports variable track conditions and curves.
- Modular power supply (can use AA batteries for testing or 7.4V Li-ion/LiPo for performance).
- Easily adaptable to digital or analog IR sensor arrays.

---

## 🚀 Getting Started

1. Assemble the components and complete wiring as described.
2. Upload the PID control Arduino sketch (pid_line_follower.ino) to your Arduino Nano.
3. Place the robot on a black line track.
4. Power the robot and observe line following behavior.
5. Tune the PID values in the code for optimal performance based on your track.

---

## 📝 PID Tuning Tips

- Increase Kp until the robot follows but overshoots/oscillates.
- Add Kd to reduce oscillations and sharpen turns.
- Add Ki only if there's a consistent drift over time.

Example values:

```cpp
float Kp = 25;
float Ki = 0;
float Kd = 15;
```

---

## 🧪 Testing Option

You can temporarily use 4x 1.2V AA NiMH rechargeable batteries (4.8V total) for slow-speed testing. Connect this directly to the Arduino Nano's 5V pin and to TB6612 VCC. Do not use the VIN pin in this case. The motors may run slower, but it's safe for sensor and logic testing.

---

## 📜 License

This project is licensed under the **MIT License**.  
You are free to use, modify, and distribute this project with proper attribution.

## 🙌 Credits

Created and developed by [Rajjit Laishram](https://rajjitlaishram.netlify.app/).  
Special thanks to the Arduino and open-source robotics communities.
