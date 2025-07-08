#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"
#include <Wire.h>
#include "RTClib.h"

// RTC Setup
RTC_DS3231 rtc;

// Button on GPIO13
const int buttonPin = 13;

// Track button press state
bool lastButtonState = HIGH;
bool captureRequested = false;

// Camera pin configuration (AI Thinker ESP32-CAM)
#define PWDN_GPIO_NUM -1
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

void setupCamera()
{
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

    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed: 0x%x", err);
        while (true)
            ;
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(buttonPin, INPUT_PULLUP);

    // Init RTC
    Wire.begin();
    if (!rtc.begin())
    {
        Serial.println("RTC not found!");
        while (1)
            ;
    }

    // Uncomment to set time once
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // Init SD card
    if (!SD_MMC.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }

    uint8_t cardType = SD_MMC.cardType();
    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return;
    }

    Serial.println("SD card initialized");

    // Init camera
    setupCamera();
}

void loop()
{
    bool currentState = digitalRead(buttonPin);

    // Detect falling edge
    if (lastButtonState == HIGH && currentState == LOW)
    {
        Serial.println("Button Pressed!");
        captureRequested = true;
    }

    lastButtonState = currentState;

    if (captureRequested)
    {
        captureRequested = false;

        DateTime now = rtc.now();

        // Format filename: YYYY-MM-DD_HH-MM-SS.jpg
        char filename[32];
        sprintf(filename, "/%04d-%02d-%02d_%02d-%02d-%02d.jpg",
                now.year(), now.month(), now.day(),
                now.hour(), now.minute(), now.second());

        camera_fb_t *fb = esp_camera_fb_get();
        if (!fb)
        {
            Serial.println("Camera capture failed");
            return;
        }

        File file = SD_MMC.open(filename, FILE_WRITE);
        if (!file)
        {
            Serial.println("Failed to open file");
        }
        else
        {
            file.write(fb->buf, fb->len);
            Serial.print("Saved: ");
            Serial.println(filename);
        }
        file.close();
        esp_camera_fb_return(fb);
    }
}
