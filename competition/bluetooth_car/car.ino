#define LEFT_IN1   4
#define LEFT_IN2   5
#define RIGHT_IN1  6
#define RIGHT_IN2  7

char data; // incoming command

void setup() {
  Serial.begin(9600);

  pinMode(LEFT_IN1,  OUTPUT);
  pinMode(LEFT_IN2,  OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.read();
    Serial.println(data);

    switch (data) {
      case 'F': // forward
        digitalWrite(LEFT_IN1,  HIGH);
        digitalWrite(LEFT_IN2,  LOW);
        digitalWrite(RIGHT_IN1, HIGH);
        digitalWrite(RIGHT_IN2, LOW);
        break;

      case 'B': // backward
        digitalWrite(LEFT_IN1,  LOW);
        digitalWrite(LEFT_IN2,  HIGH);
        digitalWrite(RIGHT_IN1, LOW);
        digitalWrite(RIGHT_IN2, HIGH);
        break;

      case 'L': // spin left
        digitalWrite(LEFT_IN1,  LOW);
        digitalWrite(LEFT_IN2,  HIGH);
        digitalWrite(RIGHT_IN1, HIGH);
        digitalWrite(RIGHT_IN2, LOW);
        break;

      case 'R': // spin right
        digitalWrite(LEFT_IN1,  HIGH);
        digitalWrite(LEFT_IN2,  LOW);
        digitalWrite(RIGHT_IN1, LOW);
        digitalWrite(RIGHT_IN2, HIGH);
        break;

      case 'S': // stop
      default:
        digitalWrite(LEFT_IN1,  LOW);
        digitalWrite(LEFT_IN2,  LOW);
        digitalWrite(RIGHT_IN1, LOW);
        digitalWrite(RIGHT_IN2, LOW);
        break;
    }
  }
}
