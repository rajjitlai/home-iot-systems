// === Motor Pins (TB6612FNG) ===
const int PWMA = 5;
const int AIN1 = 4;
const int AIN2 = 3;

const int PWMB = 6;
const int BIN1 = 7;
const int BIN2 = 8;

const int STBY = 9; // Optional standby pin

// === IR Sensor Pins ===
const int irSensor[7] = {A0, A1, A2, A3, A4, A5, A6};

// === PID Constants ===
float Kp = 25;
float Ki = 0;
float Kd = 15;

// === Variables for PID ===
int position = 0;
int lastError = 0;
int integral = 0;

// === Motor Speed Settings ===
int baseSpeed = 150; // 0-255 PWM

void setup()
{
    // Motor pins
    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(STBY, OUTPUT);

    // Start motors
    digitalWrite(STBY, HIGH);

    // IR sensor pins
    for (int i = 0; i < 7; i++)
    {
        pinMode(irSensor[i], INPUT);
    }

    Serial.begin(9600);
}

void loop()
{
    int sensor[7];
    int weightedSum = 0;
    int activeCount = 0;

    // Read sensors
    for (int i = 0; i < 7; i++)
    {
        sensor[i] = analogRead(irSensor[i]); // or digitalRead() if using digital IR
        if (sensor[i] < 500)
        { // Threshold: white=high, black=low
            weightedSum += i * 100;
            activeCount++;
        }
    }

    // Calculate position
    if (activeCount > 0)
    {
        position = weightedSum / activeCount; // value: 0 (left) to 600 (right)
    }

    int error = 300 - position; // 300 is center of line
    integral += error;
    int derivative = error - lastError;

    int correction = (Kp * error) + (Ki * integral) + (Kd * derivative);
    lastError = error;

    int leftSpeed = baseSpeed + correction;
    int rightSpeed = baseSpeed - correction;

    // Limit motor speed
    leftSpeed = constrain(leftSpeed, 0, 255);
    rightSpeed = constrain(rightSpeed, 0, 255);

    moveMotors(leftSpeed, rightSpeed);
}

// === Motor control ===
void moveMotors(int left, int right)
{
    // Left motor (A)
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, left);

    // Right motor (B)
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, right);
}
