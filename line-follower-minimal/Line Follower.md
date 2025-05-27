# 🚗 PID Line Follower Robot

A smart line-following robot using an Arduino UNO, TB6612FNG motor driver, and a TCRT5000L 5-channel IR sensor. This project uses a **PID (Proportional–Integral–Derivative)** control algorithm for accurate line tracking, including U-turns on a **black line over a white background**.

---

## 🛠️ Components Used

| Component              | Quantity |
|------------------------|----------|
| Arduino UNO R3         | 1        |
| TCRT5000L IR Sensor (5 Channel) | 1 |
| TB6612FNG Motor Driver | 1        |
| BO Motors (Gear Motor) | 2        |
| Chassis Kit            | 1        |
| Breadboard             | 1        |
| Jumper Wires           | ~10      |
| 7.4V Li-ion Battery Pack | 1      |
| 9V Battery with Caps (or) | 1 |
| Wheels                 | 2        |

---

## ⚙️ Circuit Connections

### 🧠 Sensor (IR)

| Sensor Pin | Arduino Pin |
|------------|-------------|
| IR0 (Leftmost) | A0 |
| IR1           | A1 |
| IR2 (Center)  | A2 |
| IR3           | A3 |
| IR4 (Rightmost) | A4 |

### 🔌 Motor Driver (TB6612FNG)

| TB6612FNG Pin | Arduino Pin | Description        |
|---------------|-------------|--------------------|
| AIN1          | 4           | Left Motor IN1     |
| AIN2          | 5           | Left Motor IN2     |
| PWMA          | 9           | Left Motor PWM     |
| BIN1          | 6           | Right Motor IN1    |
| BIN2          | 7           | Right Motor IN2    |
| PWMB          | 10          | Right Motor PWM    |
| STBY          | 8           | Standby control    |
| VM (Motor VCC)| Battery +ve |
| GND           | Battery -ve + Arduino GND |
| VCC           | 5V from Arduino |

### 🔋 Power Supply

- Connect **7.4V or 9V battery**:
  - +ve → TB6612FNG **VM**
  - -ve → GND rail shared with Arduino and Motor Driver
- Arduino powered via **DC jack** or **Vin pin**

---

## 📦 Features

- PID Control (Proportional, Derivative)
- U-turn recovery logic
- Smooth and accurate movement
- Supports **black line on white background**

---

## 💻 Code

The code is written in Arduino C and includes:

- Sensor reading
- PID calculation
- Dynamic motor speed adjustment
- Lost-line recovery (U-turn)

---

## 📸 Sample Output

> Robot follows line smoothly and performs U-turns accurately on well-prepared tracks.

---

## 🤖 PID Tuning Tips

- **Kp** increases responsiveness (too high = jittery)
- **Kd** stabilizes movement (reduces overshoot)
- **Ki** is often unnecessary for basic line following

---
