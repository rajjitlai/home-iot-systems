# 🚗 Bluetooth Controlled Car using Arduino UNO

This project allows you to control a simple two-wheel drive car using an Arduino UNO and an HC-05 Bluetooth module. The car receives commands (`F`, `B`, `L`, `R`, `S`) via Bluetooth and moves accordingly.

---

## 📦 Components Used

| Component                | Quantity | Notes                                  |
|--------------------------|----------|----------------------------------------|
| Arduino UNO              | 1        | Main microcontroller                   |
| HC-05 Bluetooth Module   | 1        | For wireless communication             |
| L298N Motor Driver       | 1        | Drives two DC motors                   |
| DC Geared Motors         | 2        | Left and Right wheels                  |
| AA Battery (1.5V)        | 4        | Power supply (recommend 6x or Li-ion)  |
| Battery Holder (4xAA)    | 1        | To connect batteries                   |
| Jumper Wires             | Many     | For wiring all modules                 |
| Breadboard               | 1        | Optional, for resistor divider         |
| Resistors (2kΩ + 1kΩ)    | 1 each   | For voltage divider on HC-05 RX pin    |
| Chassis + Wheels         | 1 set    | Physical frame                         |

---

## 🛠️ Wiring Connections

### HC-05 to Arduino (via voltage divider on RX):
| HC-05 Pin | Arduino Pin | Notes                         |
|-----------|-------------|-------------------------------|
| VCC       | 5V          | From Arduino                  |
| GND       | GND         | Common ground                 |
| TX        | D2          | Bluetooth TX → Arduino RX     |
| RX        | D3          | Arduino TX → HC-05 RX (via divider: 1kΩ + 2kΩ) |

### L298N Motor Driver to Arduino:
| L298N Pin | Arduino Pin | Function                      |
|-----------|-------------|-------------------------------|
| IN1       | D8          | Motor A Direction             |
| IN2       | D9          | Motor A Direction             |
| IN3       | D10         | Motor B Direction             |
| IN4       | D11         | Motor B Direction             |
| ENA/ENB   | Jumpered     | Enables motors (can use PWM) |

### Power:
- **L298N `12V` Pin** → Battery +ve (~6V to 12V recommended)
- **L298N `GND`** → Battery -ve and Arduino GND
- **Arduino** powered via USB (for testing) or 5V regulator
- **HC-05 VCC** → Arduino 5V
- **All GNDs must be common**

---

## 📱 Bluetooth Commands

Use any Bluetooth Terminal or **Arduino Bluetooth Controller App**. Send the following characters:

| Command | Action        |
|---------|---------------|
| F       | Move Forward  |
| B       | Move Backward |
| L       | Turn Left     |
| R       | Turn Right    |
| S       | Stop          |

---

## 🚀 Setup Instructions

1. **Connect all hardware** as described above.
2. **Upload the code** to Arduino Uno.
3. **Pair HC-05** with your Android phone (default password: `1234` or `0000`).
4. Open any Bluetooth terminal app.
5. Connect to HC-05 and send commands (`F`, `B`, etc.).
6. Car should move as per command.

---

## 💡 Tips

- Use **SoftwareSerial** (D2/D3) to avoid conflicts with USB serial monitor.
- Prefer **Li-ion/LiPo batteries (7.4V)** for reliable motor power.
- Make sure your **HC-05 RX has a voltage divider** to avoid damage from Arduino’s 5V TX.

---

## 📜 License

This project is licensed under the **MIT License**.  
You are free to use, modify, and distribute this project with proper attribution.

## 🙌 Credits

Created and developed by [Rajjit Laishram](https://rajjitlaishram.netlify.app/).  
Special thanks to the Arduino and open-source robotics communities.
