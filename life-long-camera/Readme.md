# Wearable Timelapse Body Camera (ESP32-CAM)

A compact, low-power wearable camera that captures a photo every 10 minutes and saves it on an SD card. Designed for memory-keeping during special days and events.

---

## Features

- Takes a photo automatically every 10 minutes
- Stores photos on a microSD card
- Timestamped filenames using a real-time clock (DS3231)
- Push button to manually capture photos
- Battery-powered and rechargeable via USB
- LED indicator for photo capture
- Compact and wearable (cardboard prototype, 3D printable case planned)

---

## Components Used

| Component | Description |
|----------|-------------|
| ESP32-CAM-MB | WiFi + Bluetooth camera board with OV2640 and microSD slot |
| OV2640 Camera | 2MP camera module |
| TP4056 Module | Li-ion/LiPo charging via USB |
| 1000mAh LiPo Battery | Powers the device (3.7V) |
| DS3231 RTC Module | Keeps accurate time for timestamps |
| Tactile Push Button | Optional manual photo trigger |
| 16GB MicroSD Card | Storage for photos |
| LED + Resistor | Photo capture status indicator |
| Jumper wires + Breadboard | For initial prototyping |

---

## Circuit Diagram (Coming Soon)

- ESP32-CAM → RTC (I2C: SDA/SCL)
- ESP32-CAM → Button (GPIO)
- ESP32-CAM → LED (GPIO + resistor)
- LiPo Battery → TP4056 → ESP32 5V/VIN pin
- microSD card inbuilt on ESP32-CAM

---

## Arduino Code (Coming Soon)

- Initializes RTC, SD card, camera
- Captures photo every 10 minutes using `millis()`
- Adds timestamps to filenames
- Saves images to SD card
- Manual capture if button is pressed
- Flashes LED on each capture

---

## Planned Improvements

- Add power-saving sleep mode between captures
- OLED display for preview or battery status
- BLE integration to transfer photos or trigger capture
- Weatherproof enclosure
- Multiple capture modes: timelapse, motion-based, manual

---

## Project Status

- [x] Idea finalized
- [x] Components selected
- [ ] Components purchased
- [ ] Prototype (breadboard)
- [ ] Code tested
- [ ] Cardboard body prototype
- [ ] 3D printed case
- [ ] Final wearable assembly

## Extra components needed to bought (Rs. 600)

- MT3608 2A Max DC-DC Step Up Power Module Booster Power Module
- Duracell CR2032 3V Lithium Coin Battery
- DFRobot USB Charger for 7.4V LiPo Battery
