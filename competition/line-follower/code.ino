/*
  5-Sensor PID Line Follower
  Arduino UNO → TB6612FNG (PWMA, PWMB, STBY = 5 V)

  Sensors:
    OUT0 → A0
    OUT1 → A1
    OUT2 → A2
    OUT3 → A3
    OUT4 → A4

  Motor A (PWMA tied HIGH):
    AIN1 → D3 (PWM)
    AIN2 → D5 (PWM)

  Motor B (PWMB tied HIGH):
    BIN1 → D6 (PWM)
    BIN2 → D9 (PWM)
*/

const uint8_t NUM_SENS = 5;
const uint8_t sensorPins[NUM_SENS] = {A0, A1, A2, A3, A4};

// ←— after calibration, fill these with your 5 per-sensor thresholds:
int thresholds[NUM_SENS] = {424, 423, 424, 424, 424};

const uint8_t M_A1 = 3; // Motor A forward PWM
const uint8_t M_A2 = 5; // Motor A reverse PWM
const uint8_t M_B1 = 6; // Motor B forward PWM
const uint8_t M_B2 = 9; // Motor B reverse PWM

// PID gains (tune these for your robot)
const float Kp = 0.8;
const float Ki = 0.0;
const float Kd = 0.1;

float lastError = 0;
float integral = 0;

void setup()
{
    Serial.begin(9600);
    for (uint8_t i = 0; i < NUM_SENS; i++)
    {
        pinMode(sensorPins[i], INPUT);
    }
    pinMode(M_A1, OUTPUT);
    pinMode(M_A2, OUTPUT);
    pinMode(M_B1, OUTPUT);
    pinMode(M_B2, OUTPUT);
}

void loop()
{
    // 1) Read sensors
    int vals[NUM_SENS];
    for (uint8_t i = 0; i < NUM_SENS; i++)
    {
        vals[i] = analogRead(sensorPins[i]);
    }

    // 2) Compute line-position error
    long activeCount = 0, weightedSum = 0;
    for (uint8_t i = 0; i < NUM_SENS; i++)
    {
        bool onBlack = vals[i] > thresholds[i];
        activeCount += onBlack;
        weightedSum += onBlack ? (i * 1000L) : 0;
    }
    float position = activeCount ? (weightedSum / (float)activeCount) : 2000;
    float error = position - 2000; // center = 2*1000

    // 3) PID
    integral += error;
    float derivative = error - lastError;
    float correction = Kp * error + Ki * integral + Kd * derivative;
    lastError = error;

    // 4) Set motor speeds
    const int baseSpeed = 150; // 0–255
    int speedA = baseSpeed + correction;
    int speedB = baseSpeed - correction;
    driveA(speedA);
    driveB(speedB);
}

// Drive Motor A with a signed speed (–255..+255)
void driveA(int spd)
{
    spd = constrain(spd, -255, 255);
    if (spd > 0)
    {
        analogWrite(M_A1, spd);
        digitalWrite(M_A2, LOW);
    }
    else if (spd < 0)
    {
        analogWrite(M_A2, -spd);
        digitalWrite(M_A1, LOW);
    }
    else
    {
        digitalWrite(M_A1, LOW);
        digitalWrite(M_A2, LOW);
    }
}

// Drive Motor B with a signed speed (–255..+255)
void driveB(int spd)
{
    spd = constrain(spd, -255, 255);
    if (spd > 0)
    {
        analogWrite(M_B1, spd);
        digitalWrite(M_B2, LOW);
    }
    else if (spd < 0)
    {
        analogWrite(M_B2, -spd);
        digitalWrite(M_B1, LOW);
    }
    else
    {
        digitalWrite(M_B1, LOW);
        digitalWrite(M_B2, LOW);
    }
}
