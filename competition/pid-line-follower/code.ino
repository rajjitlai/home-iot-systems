#include <QTRSensors.h>

// —— Configuration ——
// your 5 analog sensor pins
#define NUM_SENSORS 5
#define TIMEOUT 2500
#define EMITTER_PIN 255 // not driving emitters from Arduino

uint8_t sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4};
QTRSensorsAnalog qtr(sensorPins, NUM_SENSORS);
unsigned int sensorValues[NUM_SENSORS];

// TB6612FNG motor pins (PWMA, PWMB, STBY tied to 5 V on the board)
const uint8_t M_AIN1 = 3; // Motor A forward
const uint8_t M_AIN2 = 5; // Motor A reverse
const uint8_t M_BIN1 = 6; // Motor B forward
const uint8_t M_BIN2 = 9; // Motor B reverse

// PID gains — start here and tune!
float Kp = 0.15;
float Ki = 0.0005;
float Kd = 1.2;

float lastError = 0;
float integral = 0;
unsigned long lastTime;

const int baseSpeed = 150; // 0–255

// —— Setup & Calibration ——
void setup()
{
    Serial.begin(115200);

    // Calibrate by spinning in place over the line for ~5s:
    pinMode(M_AIN1, OUTPUT);
    pinMode(M_AIN2, OUTPUT);
    pinMode(M_BIN1, OUTPUT);
    pinMode(M_BIN2, OUTPUT);
    unsigned long start = millis();
    while (millis() - start < 5000)
    {
        qtr.calibrate(); // accumulates min/max readings
        // in-place turn:
        analogWrite(M_AIN1, 120);
        digitalWrite(M_AIN2, LOW);
        analogWrite(M_BIN2, 120);
        digitalWrite(M_BIN1, LOW);
    }
    // stop motors and finalize calibration
    analogWrite(M_AIN1, 0);
    digitalWrite(M_AIN2, LOW);
    analogWrite(M_BIN1, 0);
    digitalWrite(M_BIN2, LOW);

    lastTime = micros();
}

// —— Main Loop ——
void loop()
{
    // 1) read calibrated line position: 0..(NUM_SENSORS−1)*1000
    unsigned int position = qtr.readLine(sensorValues);

    // 2) compute PID terms
    float error = (float)position - 2000.0; // center = 2×1000
    unsigned long now = micros();
    float dt = (now - lastTime) / 1e6; // seconds
    lastTime = now;

    integral += error * dt;
    float derivative = (error - lastError) / dt;
    lastError = error;

    float correction = Kp * error + Ki * integral + Kd * derivative;

    // 3) mix to motor speeds
    int speedA = constrain(baseSpeed + correction, -255, 255);
    int speedB = constrain(baseSpeed - correction, -255, 255);

    driveMotor(M_AIN1, M_AIN2, speedA);
    driveMotor(M_BIN1, M_BIN2, speedB);
}

// —— Drive helper ——
// spd: –255..+255
void driveMotor(uint8_t pinF, uint8_t pinR, int spd)
{
    if (spd > 0)
    {
        analogWrite(pinF, spd);
        digitalWrite(pinR, LOW);
    }
    else
    {
        analogWrite(pinR, -spd);
        digitalWrite(pinF, LOW);
    }
}
