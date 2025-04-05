int water;

void setup()
{
    pinMode(3, OUTPUT);
    pinMode(6, INPUT); 
    Serial.begin(9600);
    Serial.println("System Started. Waiting for sensor input...");
}

void loop()
{
    water = digitalRead(6);

    if (water == HIGH)
    {
        digitalWrite(3, LOW);
        Serial.println("Soil is wet - Pump OFF");
    }
    else
    {
        digitalWrite(3, HIGH);
        Serial.println("Soil is dry - Pump ON");
    }

    delay(1000);
}
