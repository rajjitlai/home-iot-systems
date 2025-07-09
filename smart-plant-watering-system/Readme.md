# 🌱 Arduino Soil Moisture Pump Control System

This project uses a soil moisture sensor to monitor the moisture level of soil and automatically turns a water pump **ON** or **OFF** based on the dryness of the soil. It is a simple, cost-effective, and beginner-friendly automatic irrigation system.

---

## 🔧 Components Required

| Component              | Quantity | Description                                |
|------------------------|----------|--------------------------------------------|
| Arduino Uno / Nano     | 1        | Microcontroller board                       |
| Soil Moisture Sensor   | 1        | Digital output sensor (connected to D6)     |
| Relay Module / Motor Driver | 1   | To control the water pump (connected to D3) |
| Water Pump             | 1        | Small DC pump for irrigation               |
| Jumper Wires           | As needed | For connections                            |
| Power Source (USB/9V)  | 1        | To power the Arduino board                 |

---

## ⚙️ Circuit Connections

| Arduino Pin | Component         | Description                 |
|-------------|-------------------|-----------------------------|
| D6          | Soil Sensor OUT   | Reads moisture level        |
| D3          | Relay/Pump IN     | Controls pump ON/OFF        |
| GND         | All components    | Common ground               |
| VCC (5V)    | Sensor + Relay    | Power supply                |

---

## 🚀 How It Works

- The soil moisture sensor outputs `HIGH` when the soil is **wet**.
- It outputs `LOW` when the soil is **dry**.
- The Arduino reads this signal on digital pin D6.
- If the soil is dry (`LOW`), it turns ON the pump (sets D3 `HIGH`).
- If the soil is wet (`HIGH`), it turns OFF the pump (sets D3 `LOW`).
- Status messages are printed via Serial Monitor every second.

---

## 📜 License

This project is licensed under the **MIT License**.  
You are free to use, modify, and distribute this project with proper attribution.

## 🙌 Credits

Created and developed by [Rajjit Laishram](https://rajjitlaishram.netlify.app/).  
Special thanks to the Arduino and open-source robotics communities.
