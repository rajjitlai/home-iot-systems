#include <Arduino.h>

// ===== CONFIG =====
const uint8_t NUM_SENSORS = 5;
const uint8_t sensorPins[] = {A0, A1, A2, A3, A4};
const uint8_t btnCal = 2;
const uint8_t AIN1 = 3, AIN2 = 5,
              BIN1 = 6, BIN2 = 9;

enum LineMode
{
    DARK_ON_LIGHT,
    LIGHT_ON_DARK
};
const LineMode mode = DARK_ON_LIGHT;

// ===== PID & MOTORS =====
const int BASE_SPEED = 50; // fixed cruising speed
const int MAX_SPEED = 50;  // clamp outputs to ±60

// per-side motor scaling
const float LEFT_MOTOR_FACT = 1.30;
const float RIGHT_MOTOR_FACT = 1.00;

// PID gains
const float Kp = 0.15, Ki = 0.00, Kd = 0.02;

// ===== CROSSING LOCKOUT =====
const unsigned long CROSS_TIME = 200; // ms straight‐ahead on “+”
bool inCross = false;
unsigned long crossStart = 0;

// ===== STATE =====
int sensorMin[NUM_SENSORS], sensorMax[NUM_SENSORS];
float lastError = 0, integral = 0;
unsigned long lastTime = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(btnCal, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        pinMode(sensorPins[i], INPUT);
        sensorMin[i] = 1023;
        sensorMax[i] = 0;
    }
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);

    // optional 3s calibration when D2 held LOW at reset
    if (digitalRead(btnCal) == LOW)
    {
        unsigned long t0 = millis();
        Serial.println(F("Calibrating sensors… wave over LINE & BG for 3 s"));
        while (millis() - t0 < 3000)
        {
            for (uint8_t i = 0; i < NUM_SENSORS; i++)
            {
                int v = analogRead(sensorPins[i]);
                sensorMin[i] = min(sensorMin[i], v);
                sensorMax[i] = max(sensorMax[i], v);
            }
        }
        Serial.println(F("Calibration done."));
        digitalWrite(LED_BUILTIN, HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN, LOW);
    }

    lastTime = millis();
    Serial.println(F("Setup complete."));
}

void loop()
{
    // 1) read & normalize [0..1000], detect which sensors see the line
    bool onLine[NUM_SENSORS];
    int activeCount = 0;
    long weighted = 0;

    for (uint8_t i = 0; i < NUM_SENSORS; i++)
    {
        int raw = analogRead(sensorPins[i]);
        int norm = (sensorMax[i] > sensorMin[i])
                       ? constrain(map(raw, sensorMin[i], sensorMax[i], 0, 1000), 0, 1000)
                       : (raw < 512 ? 0 : 1000);

        onLine[i] = (mode == DARK_ON_LIGHT) ? (norm > 500) : (norm < 500);
        if (onLine[i])
        {
            activeCount++;
            weighted += (int(i) - 2) * 1000; // positions −2…+2
        }
    }

    // 2) CROSSING LOCKOUT: timed straight‐through & clear exit
    if (!inCross && activeCount >= NUM_SENSORS)
    {
        inCross = true;
        crossStart = millis();
    }
    if (inCross)
    {
        // drive straight while within CROSS_TIME
        driveMotors(BASE_SPEED, BASE_SPEED);

        // only exit once both:
        //  a) we've driven straight for CROSS_TIME
        //  b) the high-count of sensors has dropped below a simple path (e.g. <=2)
        if (millis() - crossStart >= CROSS_TIME && activeCount <= 2)
        {
            inCross = false;
        }
        return; // skip PID & steering
    }

    // 3) PID error calculation
    float error, dt;
    unsigned long now = millis();
    dt = (now - lastTime) / 1000.0;
    lastTime = now;

    if (activeCount == 0)
    {
        // no sensors see the line → keep turning toward last error
        error = lastError;
    }
    else
    {
        error = (float)weighted / activeCount; // −2000…+2000
        lastError = error;
    }
    integral += error * dt;
    float derivative = (error - lastError) / max(dt, 0.001f);
    float control = Kp * error + Ki * integral + Kd * derivative;

    // 4) compute motor speeds and clamp to ±BASE_SPEED
    int leftSpeed = constrain(int(BASE_SPEED + control), -MAX_SPEED, MAX_SPEED);
    int rightSpeed = constrain(int(BASE_SPEED - control), -MAX_SPEED, MAX_SPEED);

    // 5) drive with motor scaling
    driveMotors(leftSpeed, rightSpeed);
}

// Scale, clamp, and write PWM to each motor
void driveMotors(int left, int right)
{
    int pwmL = constrain(int(fabs(left) * LEFT_MOTOR_FACT), 0, MAX_SPEED);
    int pwmR = constrain(int(fabs(right) * RIGHT_MOTOR_FACT), 0, MAX_SPEED);

    // left motor
    if (left > 0)
    {
        analogWrite(AIN1, pwmL);
        digitalWrite(AIN2, LOW);
    }
    else if (left < 0)
    {
        analogWrite(AIN2, pwmL);
        digitalWrite(AIN1, LOW);
    }
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
    }
    // right motor
    if (right > 0)
    {
        analogWrite(BIN1, pwmR);
        digitalWrite(BIN2, LOW);
    }
    else if (right < 0)
    {
        analogWrite(BIN2, pwmR);
        digitalWrite(BIN1, LOW);
    }
    else
    {
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
    }
}
