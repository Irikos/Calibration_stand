#define EN        8
#define X_DIR     2
#define Y_DIR     3
#define X_STP     5
#define Y_STP     6

#define Y_HOME_PIN 13
#define X_HOME_PIN 12

#define STEPS_90 800
#define STEPS_180 1600

// lower this value to increase motor speed
#define MOTOR_SPEED 1200
#define CALIBRATION_SPEED 2400

boolean xDir = true;
boolean yDir = true;

void step(boolean dir, byte dirPin, byte stepperPin, int steps, int motorSpeed = MOTOR_SPEED)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(motorSpeed);
  }
  delay(1000);
}

void calibrateY(boolean dir, int motorSpeed) {
  boolean homeY = digitalRead(Y_HOME_PIN);
  digitalWrite(Y_DIR, dir);
  while (!homeY) {
    digitalWrite(Y_STP, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(motorSpeed);
    homeY = digitalRead(Y_HOME_PIN);
  }
  delay(500);
  if (dir) {
//    step(!dir, Y_DIR, Y_STP, 0, motorSpeed);
  }
  else {
    step(dir, Y_DIR, Y_STP, 8, motorSpeed);
  }
  delay(1000);
}


void calibrateX(boolean dir, int motorSpeed) {
  boolean homeX = digitalRead(X_HOME_PIN);
  digitalWrite(X_DIR, dir);
  while (!homeX) {
    digitalWrite(X_STP, HIGH);
    delayMicroseconds(motorSpeed);
    digitalWrite(X_STP, LOW);
    delayMicroseconds(motorSpeed);
    homeX = digitalRead(X_HOME_PIN);
  }
  delay(500);
  if (dir) {
    step(!dir, X_DIR, X_STP, 35, motorSpeed);
  }
  else {
    step(dir, X_DIR, X_STP, 50, motorSpeed);
  }
  delay(1000);
}

void rotate90X(boolean dir, int motorSpeed = MOTOR_SPEED) {
  step(dir, X_DIR, X_STP, STEPS_90 * 2.84, motorSpeed);
  delay(1000);
}

void rotate180X(boolean dir, int motorSpeed = MOTOR_SPEED) {
  step(dir, X_DIR, X_STP, STEPS_180 * 2.84, motorSpeed);
  delay(1000);
}

void rotate90Y(boolean dir, int motorSpeed = MOTOR_SPEED) {
  step(dir, Y_DIR, Y_STP, STEPS_90, motorSpeed);
  delay(1000);
}


void rotate180Y(boolean dir, int motorSpeed = MOTOR_SPEED) {
  step(dir, Y_DIR, Y_STP, STEPS_180, motorSpeed);
}

void setup() { // set the IO pins for the stepper motors as output
  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  pinMode(Y_HOME_PIN, INPUT);
  pinMode(X_HOME_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    
    switch (incomingByte) {
      case '1':
        calibrateX(xDir, CALIBRATION_SPEED);
        break;
      case '2':
        calibrateX(!xDir, CALIBRATION_SPEED);
        break;
      case '3':
        calibrateY(!yDir, CALIBRATION_SPEED);
        break;
      case '4':
        calibrateY(yDir, CALIBRATION_SPEED);
        break;
      case '5':
        rotate180X(!xDir);
        break;
      case '6':
        rotate90X(!xDir);
        break;
      case '7':
        rotate90X(xDir);
        break;
      case '8':
        rotate180X(xDir);
        break;
      case '9':
        rotate180Y(yDir);
        break;
      case '0':
        rotate90Y(yDir);
        break;
      case '-':
        rotate90Y(!yDir);
        break;
      case '=':
        rotate180Y(!yDir);
        break;
    }

    Serial.write(incomingByte);
  }
}


