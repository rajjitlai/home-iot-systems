
# 🚗 PID Line Follower Robot (Black Line on White Background)

This project implements a **PID-based line follower robot** using an **Arduino UNO**, **TCRT5000L 5-channel IR sensor**, and **TB6612FNG motor driver**. The robot is designed to follow a **black line on a white surface**, handling both straight paths and U-turns smoothly and efficiently.

---

## 📦 Components Used

| Component                      | Quantity |
|--------------------------------|----------|
| Arduino UNO R3                 | 1        |
| TCRT5000L IR Sensor (5-channel)| 1        |
| TB6612FNG Motor Driver         | 1        |
| BO Motors (Geared)             | 2        |
| Wheels                         | 2        |
| Chassis Kit                    | 1        |
| Breadboard                     | 1        |
| Jumper Wires                   | 10+      |
| 7.4V Li-ion Battery / 5x AA (1.5V) | 1 Pack  |
| Battery Holder with DC Jack    | 1        |

---

## 🔌 Circuit Setup

### IR Sensor Connections

| IR Sensor Pin | Arduino Pin |
|---------------|-------------|
| IR0 (Leftmost) | A0          |
| IR1           | A1          |
| IR2 (Center)  | A2          |
| IR3           | A3          |
| IR4 (Rightmost)| A4          |

### Motor Driver (TB6612FNG) to Arduino

| TB6612FNG Pin | Arduino Pin | Description         |
|---------------|-------------|---------------------|
| AIN1          | D4          | Left Motor Control  |
| AIN2          | D5          | Left Motor Control  |
| PWMA          | D9          | Left Motor PWM      |
| BIN1          | D6          | Right Motor Control |
| BIN2          | D7          | Right Motor Control |
| PWMB          | D10         | Right Motor PWM     |
| STBY          | D8          | Standby Pin         |
| VM            | 7.4V Battery +ve |
| GND           | Common Ground |
| VCC           | Arduino 5V  |

---

## ⚙️ Power Supply

You can use one of the following:
- **7.4V Li-ion Battery Pack**
- **5x AA 1.5V cells = 7.5V**

**Important:** Connect all GNDs together (Arduino, battery, motor driver).

---

## 🧠 How It Works

- The TCRT5000L IR sensor array detects a black line on a white surface.
- Sensor readings are weighted and passed into a **PID controller** which calculates a positional error.
- Based on the PID output, motor speeds are dynamically adjusted using PWM to steer the robot.
- When the line is lost (e.g., during a U-turn), the robot uses the last known direction to recover and re-center itself.

---

## 💻 Software Overview

- Developed using **Arduino IDE**
- Uses **digital sensor inputs** (LOW = black, HIGH = white)
- PID values (`Kp`, `Ki`, `Kd`) are configurable for tuning
- Serial Monitor is used for debugging sensor readings and behavior

---

## 🧪 Expected Behavior

- Smooth tracking of black lines
- Stable turns and U-turns
- Real-time correction using PID
- Auto-recovery when the line is lost

---

## 📂 File Structure

```
PID-Line-Follower/
├── PID_Line_Follower.ino       # Main Arduino code
├── README.md                   # Project documentation
```

---

## 📜 License

This project is licensed under the **MIT License**.  
You are free to use, modify, and distribute this project with proper attribution.

---

## 🙌 Credits

Created and developed by [Rajjit Laishram](https://rajjitlaishram.netlify.app/).  
Special thanks to the Arduino and open-source robotics communities.
