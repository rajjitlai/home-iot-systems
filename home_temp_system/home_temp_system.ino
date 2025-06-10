#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>

// Define pins and sensor type
#define DHTPIN 2      // Pin where DHT22 DATA is connected
#define DHTTYPE DHT22 // Using DHT22

// Initialize sensor and LCD
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 cols, 2 rows

int errorCount = 0;

void setup()
{
    lcd.init();      // Initialize LCD
    lcd.backlight(); // Turn on backlight
    dht.begin();     // Start DHT sensor

    lcd.setCursor(0, 0);
    lcd.print("Temp Monitor");
    delay(2000);
    lcd.clear();
}

void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
        errorCount++;
        lcd.setCursor(0, 0);
        lcd.print("Sensor error");
        delay(2000);

        // Reset system if error persists
        if (errorCount >= 5)
        {
            // Force a software reset
            asm volatile("  jmp 0"); // AVR reset
        }
        return;
    }

    errorCount = 0; // Reset on success

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t, 1);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(h, 1);
    lcd.print("%");

    delay(2000);
}
