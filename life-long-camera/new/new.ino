#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"
#include <Wire.h>
#include "RTClib.h"

// RTC
RTC_DS3231 rtc;

// Button pin
const int buttonPin = 13;
bool lastButtonState = HIGH;
bool captureRequested = false;
int autoCaptureDelay = 3000;
unsigned long lastCaptureTime = 0;

// AI Thinker cam pins
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

void setup()
{
    Serial.begin(115200);
    pinMode(buttonPin, INPUT_PULLUP);

    Wire.begin(14, 15); // SDA, SCL for RTC
    if (!rtc.begin())
    {
        Serial.println("❌ RTC not found!");
        while (1)
            ;
    }

    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Run once to set time

    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    config.fb_location = CAMERA_FB_IN_PSRAM;

    if (esp_camera_init(&config) != ESP_OK)
    {
        Serial.println("❌ Camera init failed!");
        while (1)
            ;
    }

    if (!SD_MMC.begin())
    {
        Serial.println("❌ SD card init failed!");
        while (1)
            ;
    }

    Serial.println("✅ System ready!");
}

void loop()
{
    bool currentButton = digitalRead(buttonPin);

    if (lastButtonState == HIGH && currentButton == LOW)
    {
        captureRequested = true;
    }

    lastButtonState = currentButton;

    // Auto-capture every 3 seconds
    if (millis() - lastCaptureTime > autoCaptureDelay)
    {
        captureRequested = true;
        lastCaptureTime = millis();
    }

    if (captureRequested)
    {
        captureRequested = false;

        DateTime now = rtc.now();
        char filename[30];
        sprintf(filename, "/%04d-%02d-%02d_%02d-%02d-%02d.jpg",
                now.year(), now.month(), now.day(),
                now.hour(), now.minute(), now.second());

        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb)
        {
            Serial.println("❌ Capture failed");
            return;
        }

        File file = SD_MMC.open(filename, FILE_WRITE);
        if (!file)
        {
            Serial.println("❌ File open failed");
        }
        else
        {
            file.write(fb->buf, fb->len);
            file.close();
            Serial.print("✅ Saved: ");
            Serial.println(filename);
        }

        esp_camera_fb_return(fb);
    }
}
