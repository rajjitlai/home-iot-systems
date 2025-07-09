# 🌡️ DHT22 Temperature & Humidity Monitor with LCD Display

A compact and user-friendly Arduino-based system that reads **temperature** and **humidity** from a DHT22 sensor and displays the readings on a **16x2 I2C LCD**. The system also includes a built-in error handling mechanism that resets the device if the sensor repeatedly fails.

---

## 📦 Components Used

| Component           | Quantity | Description                            |
|---------------------|----------|----------------------------------------|
| Arduino Uno/Nano    | 1        | Microcontroller board                  |
| DHT22 Sensor        | 1        | Digital temperature and humidity sensor |
| 16x2 I2C LCD Module | 1        | Display readings via I2C interface     |
| Jumper Wires        | Several  | For connections                        |
| Breadboard (optional)| 1       | For prototyping                        |

---

## 🔌 Circuit Connections

### 🖥️ LCD (I2C)

| LCD Pin | Arduino Pin |
|---------|-------------|
| VCC     | 5V          |
| GND     | GND         |
| SDA     | A4 (on Uno) |
| SCL     | A5 (on Uno) |

> On an Arduino Nano: SDA = A4, SCL = A5

### 🌡️ DHT22 Sensor

| DHT22 Pin | Arduino Pin |
|-----------|-------------|
| VCC       | 5V          |
| GND       | GND         |
| DATA      | D2          |

---

## 📋 Features

- 📊 Real-time temperature and humidity readings displayed on LCD
- ⚠️ Error detection and retry if sensor fails
- 🔄 Automatic reset after 5 consecutive read errors
- 💡 Backlit I2C LCD for visibility in low light

---

## 🛠️ Libraries Required

Install these from the **Arduino Library Manager**:

- `LiquidCrystal_I2C` by Frank de Brabander or compatible fork
- `DHT sensor library` by Adafruit
- `Adafruit Unified Sensor`

---

## 🔁 Behavior

- System starts with a welcome message.
- Every 2 seconds:
  - Reads temperature and humidity from the DHT22 sensor.
  - Displays data on the LCD.
- If sensor returns invalid data 5 times in a row:
  - The system auto-resets using AVR inline assembly.

---

## 📝 Notes

- Ensure the DHT22 is powered correctly (5V preferred).
- Use a **pull-up resistor (10kΩ)** on the data line if necessary.
- Use I2C scanner if your LCD does not respond (address might be different).

---

## 📜 License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).

---

## 👨‍💻 Author

[**Rajjit Laishram**](https://rajjitlaishram.netlify.app/) 
Arduino hobbyist & IoT enthusiast
