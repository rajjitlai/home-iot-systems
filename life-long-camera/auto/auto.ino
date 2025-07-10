#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"

// AI Thinker pin mapping (via camera_pins.h)
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

int imageCounter = 1;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n📷 Starting camera...");

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
    config.fb_count = 1;
    config.jpeg_quality = 10;
    config.fb_location = CAMERA_FB_IN_PSRAM;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("❌ Camera init failed with error 0x%x\n", err);
        return;
    }

    sensor_t *s = esp_camera_sensor_get();
    if (s->id.PID == OV3660_PID)
    {
        s->set_vflip(s, 1);
        s->set_brightness(s, 1);
        s->set_saturation(s, -2);
    }

    s->set_framesize(s, FRAMESIZE_QVGA); // Good balance of quality and size

    Serial.println("📀 Mounting SD card...");
    if (!SD_MMC.begin())
    {
        Serial.println("❌ SD card mount failed");
        return;
    }
    if (SD_MMC.cardType() == CARD_NONE)
    {
        Serial.println("❌ No SD card detected");
        return;
    }
    Serial.println("✅ SD card ready");
}

void loop()
{
    Serial.printf("📸 Capturing image %d...\n", imageCounter);

    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb)
    {
        Serial.println("❌ Failed to capture image");
        delay(3000);
        return;
    }

    char filename[20];
    sprintf(filename, "/%d.jpg", imageCounter);
    File file = SD_MMC.open(filename, FILE_WRITE);
    if (!file)
    {
        Serial.printf("❌ Failed to open file: %s\n", filename);
    }
    else
    {
        file.write(fb->buf, fb->len);
        Serial.printf("✅ Saved %s (%d bytes)\n", filename, fb->len);
        file.close();
        imageCounter++;
    }

    esp_camera_fb_return(fb);
    delay(3000); // wait before next capture
}
