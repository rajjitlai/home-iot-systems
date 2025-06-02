#include <SoftwareSerial.h>

// Bluetooth module connected to D2 (RX), D3 (TX)
SoftwareSerial BT(2, 3); // RX, TX

char command;

const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

void setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    Serial.begin(9600); // USB Serial Monitor
    BT.begin(9600);     // Bluetooth module baud rate

    Serial.println("Bluetooth Car Ready. Waiting for commands...");
}

void loop()
{
    if (BT.available())
    {
        command = BT.read();
        command = toupper(command);

        Serial.print("Received command: ");
        Serial.println(command);

        switch (command)
        {
        case 'F':
            forward();
            Serial.println("Moving Forward");
            break;
        case 'B':
            backward();
            Serial.println("Moving Backward");
            break;
        case 'L':
            left();
            Serial.println("Turning Left");
            break;
        case 'R':
            right();
            Serial.println("Turning Right");
            break;
        case 'S':
            stopMotors();
            Serial.println("Stopped");
            break;
        default:
            Serial.println("Unknown command");
            break;
        }
    }
}

// Motor Control Functions
void forward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void backward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void left()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void right()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}

void stopMotors()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
