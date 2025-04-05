const int relayPin = 3;
const int sensorPin = 6;

const unsigned long pumpInterval = 6UL * 3600UL * 1000UL;
const unsigned long pumpDuration = 5000;

unsigned long lastPumpTime = 0;

void setup()
{
    pinMode(relayPin, OUTPUT);
    pinMode(sensorPin, INPUT);
    Serial.begin(9600);
    Serial.println("System Started. Monitoring sensor and pump schedule...");

    digitalWrite(relayPin, LOW);

    lastPumpTime = millis();
}

void loop()
{
    int sensorState = digitalRead(sensorPin);

    if (sensorState == HIGH)
    {
        Serial.println("Soil is wet. No pumping required.");
    }
    else
    {
        Serial.println("Soil is dry.");

        if (millis() - lastPumpTime >= pumpInterval)
        {
            Serial.println("Minimum interval met. Activating pump for 5 seconds.");

            digitalWrite(relayPin, HIGH);
            delay(pumpDuration);
            digitalWrite(relayPin, LOW);

            Serial.println("Pump deactivated.");

            lastPumpTime = millis();
        }
        else
        {
            unsigned long timeLeft = pumpInterval - (millis() - lastPumpTime);
            Serial.print("Waiting for next scheduled pump cycle: ");
            Serial.print(timeLeft / 1000);
            Serial.println(" seconds remaining.");
        }
    }

    delay(1000);
}
