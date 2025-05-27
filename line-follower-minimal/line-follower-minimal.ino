// === IR Sensor Pins ===
#define IR0 A0 // Leftmost
#define IR1 A1
#define IR2 A2 // Center
#define IR3 A3
#define IR4 A4 // Rightmost

// === Motor Driver Pins ===
// Motor A (Left Motor)
#define AIN1 4
#define AIN2 5
#define PWMA 9

// Motor B (Right Motor)
#define BIN1 6
#define BIN2 7
#define PWMB 10

// Standby Pin
#define STBY 8

// === PID Parameters ===
int baseSpeed = 90; // Reduce for better U-turns
float Kp = 25;      // Proportional gain
float Ki = 0.0;     // Integral gain
float Kd = 15;      // Derivative gain

// === PID Variables ===
float lastError = 0;
float integral = 0;

void setup()
{
    // Sensor inputs
    pinMode(IR0, INPUT);
    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
    pinMode(IR3, INPUT);
    pinMode(IR4, INPUT);

    // Motor driver outputs
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(STBY, OUTPUT);

    digitalWrite(STBY, HIGH); // Enable motor driver

    Serial.begin(9600);
}

void loop()
{
    // === Read sensors (inverted: white = 1, black = 0) ===
    int s[5];
    s[0] = !digitalRead(IR0);
    s[1] = !digitalRead(IR1);
    s[2] = !digitalRead(IR2);
    s[3] = !digitalRead(IR3);
    s[4] = !digitalRead(IR4);

    int weights[5] = {-2, -1, 0, 1, 2};
    int activeCount = 0;
    int position = 0;

    for (int i = 0; i < 5; i++)
    {
        if (s[i])
        {
            position += weights[i];
            activeCount++;
        }
    }

    float error = 0;

    if (activeCount > 0)
    {
        error = (float)position / activeCount;

        // === PID calculation ===
        integral += error;
        float derivative = error - lastError;
        float correction = Kp * error + Ki * integral + Kd * derivative;
        lastError = error;

        int leftSpeed = baseSpeed + correction;
        int rightSpeed = baseSpeed - correction;

        leftSpeed = constrain(leftSpeed, 0, 255);
        rightSpeed = constrain(rightSpeed, 0, 255);

        motorLeft(HIGH, LOW, leftSpeed);
        motorRight(HIGH, LOW, rightSpeed);
    }
    else
    {
        // === Line lost: recovery turn ===
        if (lastError > 0)
        {
            // Spin right
            motorLeft(HIGH, LOW, baseSpeed);
            motorRight(LOW, HIGH, baseSpeed);
        }
        else
        {
            // Spin left
            motorLeft(LOW, HIGH, baseSpeed);
            motorRight(HIGH, LOW, baseSpeed);
        }
    }

    delay(10); // Small delay for stability
}

// === Motor Control Functions ===
void motorLeft(bool in1, bool in2, int pwm)
{
    digitalWrite(AIN1, in1);
    digitalWrite(AIN2, in2);
    analogWrite(PWMA, pwm);
}

void motorRight(bool in1, bool in2, int pwm)
{
    digitalWrite(BIN1, in1);
    digitalWrite(BIN2, in2);
    analogWrite(PWMB, pwm);
}
