const int relayPin = 3;

const unsigned long pumpInterval = 6UL * 3600UL * 1000UL; // 6 hours
const unsigned long pumpDuration = 9000;                  // 9 seconds

unsigned long lastPumpTime = 0;

void setup()
{
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH); // Relay OFF (active LOW)

    Serial.begin(9600);
    Serial.println("System Started. Pump will run every 6 hours.");

    lastPumpTime = millis();
}

void loop()
{
    unsigned long currentTime = millis();

    if (currentTime - lastPumpTime >= pumpInterval)
    {
        Serial.println("Time to water. Activating pump...");

        digitalWrite(relayPin, LOW); // Relay ON (active LOW)
        delay(pumpDuration);
        digitalWrite(relayPin, HIGH); // Relay OFF

        Serial.println("Pump deactivated.");

        lastPumpTime = currentTime;
    }
    else
    {
        unsigned long timeLeft = (pumpInterval - (currentTime - lastPumpTime)) / 1000;
        Serial.print("Next pump in: ");
        Serial.print(timeLeft);
        Serial.println(" seconds.");
    }

    delay(1000);
}
