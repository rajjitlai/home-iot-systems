// ======= PIN & MODE CONFIG =======
const uint8_t sensorPins[5] = { A0, A1, A2, A3, A4 };
const uint8_t btnCal = 2;  // calibration button → D2

// TB6612FNG pins (PWMA/PWMB tied HIGH to 5 V)
const uint8_t AIN1 = 3, AIN2 = 5, BIN1 = 6, BIN2 = 9;

enum LineMode { DARK_ON_LIGHT,
                LIGHT_ON_DARK };
const LineMode mode = DARK_ON_LIGHT;

// ======= SPEED & STATE =======
const int baseSpeed = 70;  // [0..255]
int threshold = 600;       // overwritten by calibration
unsigned long lastTime;

void setup() {
  Serial.begin(115200);
  pinMode(btnCal, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  for (auto p : sensorPins) pinMode(p, INPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // optional one-shot calibration at startup
  if (digitalRead(btnCal) == LOW) {
    calibrateThreshold();
  }
  lastTime = millis();
}

void loop() {
  // 1) READ & THRESHOLD
  int sumActive = 0;
  long weighted = 0;
  for (uint8_t i = 0; i < 5; i++) {
    int v = analogRead(sensorPins[i]);
    bool onLine = (mode == DARK_ON_LIGHT) ? (v > threshold) : (v < threshold);
    if (onLine) {
      weighted += (int(i) - 2);
      sumActive++;
    }
  }

  // 2) NO LINE → STOP
  if (sumActive == 0) {
    stopAll();
    return;
  }

  // 3) SIMPLE SKID-STEER LOGIC
  // error < 0 → line on left, reverse left wheel
  // error > 0 → line on right, reverse right wheel
  int error = (weighted * 100) / sumActive;
  if (error < 0) {
    driveMotor(AIN1, AIN2, -baseSpeed);
    driveMotor(BIN1, BIN2, baseSpeed);
  } else if (error > 0) {
    driveMotor(AIN1, AIN2, baseSpeed);
    driveMotor(BIN1, BIN2, -baseSpeed);
  } else {
    driveMotor(AIN1, AIN2, baseSpeed);
    driveMotor(BIN1, BIN2, baseSpeed);
  }
}

// ======= THRESHOLD CALIBRATION =======
void calibrateThreshold() {
  digitalWrite(LED_BUILTIN, HIGH);
  long sumLine = 0, sumBg = 0;
  const int N = 50;

  // first half over the line
  for (int i = 0; i < N; i++) {
    for (auto p : sensorPins) sumLine += analogRead(p);
    delay(20);
  }
  // then half over background
  for (int i = 0; i < N; i++) {
    for (auto p : sensorPins) sumBg += analogRead(p);
    delay(20);
  }

  threshold = int((sumLine + sumBg) / (2.0 * N * 5));
  Serial.print("Calibrated threshold = ");
  Serial.println(threshold);

  // blink LED 5× to signal done
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(150);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

// ======= MOTOR HELPERS =======
// speed >0 ⇒ forward, <0 ⇒ backward, 0 ⇒ stop
void driveMotor(uint8_t in1, uint8_t in2, int speed) {
  if (speed > 0) {
    analogWrite(in1, speed);
    digitalWrite(in2, LOW);
  } else if (speed < 0) {
    analogWrite(in2, -speed);
    digitalWrite(in1, LOW);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void stopAll() {
  driveMotor(AIN1, AIN2, 0);
  driveMotor(BIN1, BIN2, 0);
}
