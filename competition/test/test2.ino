#include <QTRSensors.h>

// —— Configuration ——
#define NUM_SENSORS 5
#define TIMEOUT 2500
#define EMITTER_PIN QTR_NO_EMITTER_PIN

uint8_t sensorPins[NUM_SENSORS] = {A0, A1, A2, A3, A4};
QTRSensorsAnalog qtr(sensorPins, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

// TB6612FNG motor pins
const uint8_t M_AIN1 = 3, M_AIN2 = 5;
const uint8_t M_BIN1 = 6, M_BIN2 = 9;

const int baseSpeed = 160;
const int maxSpeed = 255;
const int pivotSpeed = 120;      // speed while pivoting
const int sensorThreshold = 200; // raw analog threshold to detect “on line”

// —— PID Settings ——
float Kp = 0.25, Ki = 0.0001, Kd = 2.5;
float lastError = 0, integral = 0;
unsigned long lastTime;

// —— State tracking ——
bool didUTurn = false;
int endCount = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(M_AIN1, OUTPUT);
    pinMode(M_AIN2, OUTPUT);
    pinMode(M_BIN1, OUTPUT);
    pinMode(M_BIN2, OUTPUT);

    // — Calibration —
    Serial.println("Calibrating sensors...");
    for (int i = 0; i < 300; i++)
    {
        // sweep emitters over line
        if (i < 150)
        {
            driveMotors(100, -100);
        }
        else
        {
            driveMotors(-100, 100);
        }
        qtr.calibrate();
        delay(20);
    }
    stopMotors();
    Serial.println("Calibration done.");
    delay(500);
    lastTime = micros();
}

void loop()
{
    unsigned int position = qtr.readLine(sensorValues);

    // build boolean array for on/off
    bool onLine[NUM_SENSORS];
    bool anyOn = false;
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        onLine[i] = sensorValues[i] > sensorThreshold;
        anyOn |= onLine[i];
    }

    // 1) End-of-line detection
    if (!anyOn)
    {
        endCount++;
        Serial.print("End-of-line #");
        Serial.println(endCount);
        if (endCount == 1)
        {
            performUTurn();
            integral = lastError = 0;
            lastTime = micros();
            return;
        }
        else
        {
            Serial.println("Destination reached.");
            stopMotors();
            while (true)
                ; // halt
        }
    }

    // 2) Sharp-corner detection
    // left turn: sensors 0/1 see line but center does not
    if (onLine[0] && onLine[1] && !onLine[2])
    {
        Serial.println("Sharp LEFT corner");
        performCornerTurn(true);
        integral = lastError = 0;
        lastTime = micros();
        return;
    }
    // right turn: sensors 4/3 see line but center does not
    if (onLine[4] && onLine[3] && !onLine[2])
    {
        Serial.println("Sharp RIGHT corner");
        performCornerTurn(false);
        integral = lastError = 0;
        lastTime = micros();
        return;
    }

    // 3) Regular PID line-follow
    float error = (int)position - 2000.0; // center = 2000
    unsigned long now = micros();
    float dt = (now - lastTime) / 1e6;
    lastTime = now;

    integral += error * dt;
    integral = constrain(integral, -2000, 2000);
    float derivative = (error - lastError) / dt;
    lastError = error;

    float correction = Kp * error + Ki * integral + Kd * derivative;
    correction = constrain(correction, -baseSpeed, baseSpeed);

    int leftSpeed = constrain(baseSpeed - correction, -maxSpeed, maxSpeed);
    int rightSpeed = constrain(baseSpeed + correction, -maxSpeed, maxSpeed);

    driveMotors(leftSpeed, rightSpeed);
}

// —— Helper: pivot until center sensor re-acquires the line ——
void performCornerTurn(bool left)
{
    stopMotors();
    delay(100);
    if (left)
    {
        // pivot left: left wheel backward, right wheel forward
        driveMotors(-pivotSpeed, pivotSpeed);
    }
    else
    {
        // pivot right
        driveMotors(pivotSpeed, -pivotSpeed);
    }
    // spin until center sensor sees line again
    do
    {
        qtr.read(sensorValues);
    } while (sensorValues[2] <= sensorThreshold);
    stopMotors();
    delay(200);
    Serial.println("Corner done");
}

// —— Helper: full U-turn (180°) until any sensor sees line ——
void performUTurn()
{
    Serial.println("Performing U-turn...");
    driveMotors(pivotSpeed, -pivotSpeed);
    do
    {
        qtr.read(sensorValues);
        bool any = false;
        for (int i = 0; i < NUM_SENSORS; i++)
            any |= (sensorValues[i] > sensorThreshold);
        if (any)
            break;
    } while (true);
    stopMotors();
    delay(200);
    Serial.println("U-turn complete");
}

// —— Motor drive ——
void driveMotors(int leftCmd, int rightCmd)
{
    setMotor(M_AIN1, M_AIN2, leftCmd);
    setMotor(M_BIN1, M_BIN2, rightCmd);
}

void setMotor(uint8_t pinF, uint8_t pinR, int spd)
{
    spd = constrain(spd, -255, 255);
    if (spd >= 0)
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

void stopMotors()
{
    analogWrite(M_AIN1, 0);
    digitalWrite(M_AIN2, LOW);
    analogWrite(M_BIN1, 0);
    digitalWrite(M_BIN2, LOW);
}
