# 🤖 Ultrasonic Object Avoidance Car using Arduino

This project demonstrates an autonomous robot car that uses an ultrasonic sensor mounted on a servo to detect obstacles and avoid them intelligently. Controlled by an Arduino UNO and powered via an L298N motor driver.

---

## 📦 Components Required

| Component              | Quantity |
|------------------------|----------|
| Arduino UNO            | 1        |
| L298N Motor Driver     | 1        |
| BO Motor (Gear Motor)  | 2        |
| HC-SR04 Ultrasonic Sensor | 1     |
| SG90 Servo Motor       | 1        |
| Wheels                 | 2        |
| Caster Wheel           | 1        |
| AA Battery (1.5V)      | 4        |
| Battery Holder (4xAA)  | 1        |
| Jumper Wires           | -        |
| Chassis Board          | 1        |
| Breadboard (optional)  | 1        |

---

## 🔌 Circuit Connections

### Motor Driver (L298N) to BO Motors

- `OUT1` → Left Motor +
- `OUT2` → Left Motor −  
- `OUT3` → Right Motor +
- `OUT4` → Right Motor −

### Motor Driver to Arduino

- `IN1` → D7  
- `IN2` → D6  
- `IN3` → D5  
- `IN4` → D4  
- `ENA` → D10 (PWM)  
- `ENB` → D11 (PWM)  
- `GND` → GND  
- `+12V` → 6V Battery Pack (4x AA)  
- *(Optionally connect `5V` to Arduino 5V only if jumper is removed)*

### Ultrasonic Sensor (HC-SR04)

- `VCC` → 5V  
- `GND` → GND  
- `TRIG` → D9  
- `ECHO` → D8  

### Servo Motor (SG90)

- `Signal` → D3  
- `VCC` → 5V  
- `GND` → GND  

---

## ⚙️ Setup Instructions

1. **Assemble the robot car** chassis with motors and wheels.
2. **Mount the ultrasonic sensor** onto the servo for rotation.
3. **Wire up all components** as per the connection table.
4. **Power the Arduino UNO** and L298N with a 6V battery pack (4x AA).
5. **Upload the provided Arduino code** using the Arduino IDE.
6. Place the car on the floor and observe how it moves and avoids obstacles.

---

## 💡 Features

- Dynamic obstacle detection and avoidance.
- Servo-controlled scanning for smarter path decisions.
- Adjustable motor speed via PWM.

---

## 📝 License

This project is licensed under the MIT License.

---

## 🙌 Credits

Created and developed by [Rajjit Laishram](https://rajjitlaishram.netlify.app/).  
Special thanks to the Arduino and open-source robotics communities.
