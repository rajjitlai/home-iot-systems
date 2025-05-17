const int relayPin = 3;

// Set interval and duration
const unsigned long pumpInterval = 6UL * 3600UL * 1000UL; // 6 hours in milliseconds
const unsigned long pumpDuration = 6000;                  // Pump ON duration in milliseconds (5 seconds)

unsigned long lastPumpTime = 0;

void setup()
{
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW); // Ensure pump is OFF at start

    Serial.begin(9600);
    Serial.println("System Started. Pump will run every 6 hours.");

    lastPumpTime = millis(); // Start the timer
}

void loop()
{
    unsigned long currentTime = millis();

    // Check if it's time to run the pump
    if (currentTime - lastPumpTime >= pumpInterval)
    {
        Serial.println("Time to water. Activating pump...");

        digitalWrite(relayPin, HIGH); // Turn ON the pump
        delay(pumpDuration);          // Wait while pump runs
        digitalWrite(relayPin, LOW);  // Turn OFF the pump

        Serial.println("Pump deactivated.");

        lastPumpTime = currentTime; // Reset pump timer
    }
    else
    {
        // Countdown timer display (optional)
        unsigned long timeLeft = (pumpInterval - (currentTime - lastPumpTime)) / 1000;
        Serial.print("Next pump in: ");
        Serial.print(timeLeft);
        Serial.println(" seconds.");
    }

    delay(1000); // Check every 1 second
}
