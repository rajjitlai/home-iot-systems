#include <Servo.h>

// ─── MOTOR DRIVER PINS (L298N) ─────────────────────
const int IN1 = 2;      // Left motor direction
const int IN2 = 3;
const int ENA = 9;      // Left motor speed (PWM)

const int IN3 = 4;      // Right motor direction
const int IN4 = 5;
const int ENB = 10;     // Right motor speed (PWM)

// ─── ULTRASONIC SENSOR PINS ────────────────────────
const int TRIG = 11;
const int ECHO = 12;

// ─── SERVO (SG90) ──────────────────────────────────
const int SERVO_PIN = 6;
Servo scanner;

// ─── PARAMETERS ────────────────────────────────────
const int MOTOR_SPEED = 200;         // Speed 0–255
const int OBSTACLE_DIST_CM = 20;     // Stop distance

const int ANGLE_LEFT   = 30;
const int ANGLE_RIGHT  = 150;
const int ANGLE_CENTER = 90;

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  scanner.attach(SERVO_PIN);
  scanner.write(ANGLE_CENTER);

  delay(500);
}

void loop() {
  int distFront = readDistance();
  Serial.print("Front: "); Serial.print(distFront); Serial.print(" cm  ");

  if (distFront > OBSTACLE_DIST_CM) {
    driveForward(MOTOR_SPEED);
  } else {
    stopCar();
    delay(200);

    // Scan Left
    scanner.write(ANGLE_LEFT);
    delay(300);
    int distLeft = readDistance();

    // Scan Right
    scanner.write(ANGLE_RIGHT);
    delay(300);
    int distRight = readDistance();

    // Back to Center
    scanner.write(ANGLE_CENTER);
    Serial.print("Left: "); Serial.print(distLeft); Serial.print(" cm  ");
    Serial.print("Right: "); Serial.print(distRight); Serial.println(" cm");

    // Decision Logic
    if (distLeft > distRight && distLeft > OBSTACLE_DIST_CM) {
      turnLeft();
    } else if (distRight > distLeft && distRight > OBSTACLE_DIST_CM) {
      turnRight();
    } else {
      // Both sides blocked
      driveBackward(MOTOR_SPEED);
      delay(500);
      stopCar();
      delay(200);
    }

    driveForward(MOTOR_SPEED);
  }

  delay(50);
}

// ─── FUNCTIONS ──────────────────────────────────────

void driveForward(int speed) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void driveBackward(int speed) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void turnLeft() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, MOTOR_SPEED / 2);
  analogWrite(ENB, MOTOR_SPEED);
  delay(400);
  stopCar();
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED / 2);
  delay(400);
  stopCar();
}

int readDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  if (duration == 0) return 999;

  int distance = duration * 0.034 / 2;
  return distance;
}
