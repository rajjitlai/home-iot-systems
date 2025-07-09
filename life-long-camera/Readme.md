# ESP32-CAM Wearable Body Camera

A compact, wearable camera that captures photos with timestamps and stores them on an SD card. This project is based on the ESP32-CAM module with support for a 3.7V Li-ion battery, step-up power module, RTC, and manual trigger button. Ideal for memorial days, field journaling, and lifelogging.

---

## 📦 Components Used

| Component                | Quantity | Description                               |
| ------------------------ | -------- | ----------------------------------------- |
| ESP32-CAM Module         | 1        | Camera and microcontroller unit           |
| ESP32-CAM MB Board       | 1        | Breakout board for ESP32-CAM with USB     |
| 3.7V Li-ion Battery      | 1        | Rechargeable power source                 |
| TP4056 Charging Module   | 1        | Battery charger with protection circuit   |
| DC-DC Step-Up Module     | 1        | Boosts 3.7V to stable 5V output           |
| DS3231 RTC Module        | 1        | Real-time clock for timestamped filenames |
| MicroSD Card (FAT32)     | 1        | Storage for captured images               |
| Push Button              | 1        | Manual capture trigger                    |
| Jumper Wires             | 10+      | For circuit connections                   |
| Breadboard (optional)    | 1        | For prototyping (optional)                |
| On/Off Switch (optional) | 1        | Power toggle for wearable mode            |

---

## 🔌 Circuit Setup

### Power Flow:

* **Battery (+)** → TP4056 `BAT+`
* **Battery (−)** → TP4056 `BAT−`
* **TP4056 `OUT+`** → Step-Up `VIN+`
* **TP4056 `OUT−`** → Step-Up `VIN−`
* **Step-Up `VOUT+`** → ESP32-CAM MB `5V`
* **Step-Up `VOUT−`** → ESP32-CAM MB `GND`

### RTC Wiring:

* `RTC VCC` → ESP32-CAM `3.3V` or `5V`
* `RTC GND` → ESP32-CAM `GND`
* `RTC SDA` → ESP32-CAM GPIO 21
* `RTC SCL` → ESP32-CAM GPIO 22

### Push Button:

* One side → ESP32-CAM GPIO 13
* Other side → GND

### SD Card:

* Inserted into ESP32-CAM onboard SD slot

---

## 🔧 How to Upload Code

1. Connect ESP32-CAM MB to PC via USB.
2. In Arduino IDE:

   * Select board: `AI Thinker ESP32-CAM`
   * Select correct COM port
3. Install libraries:

   * `esp_camera`
   * `FS`, `SD_MMC`
   * `RTClib` by Adafruit
4. Upload the provided sketch (see `bodycam.ino`).
5. After upload, disconnect IO0 from GND and press RESET.

---

## 🖼️ What It Does

* Waits for a button press
* Captures an image using the ESP32-CAM
* Reads the current date & time from RTC
* Saves the image to SD card as: `YYYY-MM-DD_HH-MM-SS.jpg`

---

## 📁 Project Folder Structure

```bash
life-long-camera/
├── life-long-camera.ino              # Arduino sketch
├── README.md                # Project documentation
├── /CameraWebServer                # Optional testing files
```

---

## 📜 License

This project is licensed under the MIT License

---

## 📷 Project By

[**Rajjit Laishram**](https://rajjitlaishram.netlify.app/) — Embedded tinkerer & full-stack developer

