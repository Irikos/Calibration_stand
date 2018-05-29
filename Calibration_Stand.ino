#define EN        8
#define X_DIR     5
#define Y_DIR     3
#define X_STP     2
#define Y_STP     6

#define Y_HOME_PIN 13
#define X_HOME_PIN 12

#define STEPS_90 800
#define STEPS_180 1600

// lower this value to increase motor speed
#define MOTOR_SPEED 800

// for incoming serial data
int incomingByte = 0;  

void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(MOTOR_SPEED);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(MOTOR_SPEED);
  }
}

void calibrateY() {
  boolean homeY = digitalRead(Y_HOME_PIN);
  digitalWrite(Y_DIR, true);
  while (!homeY) {
    digitalWrite(Y_STP, HIGH);
    delayMicroseconds(MOTOR_SPEED);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(MOTOR_SPEED);
    homeY = digitalRead(Y_HOME_PIN);
  }
}


void calibrateX() {
  boolean homeX = digitalRead(X_HOME_PIN);
  digitalWrite(X_DIR, true);
  while (!homeX) {
    digitalWrite(X_STP, HIGH);
    delayMicroseconds(MOTOR_SPEED);
    digitalWrite(X_STP, LOW);
    delayMicroseconds(MOTOR_SPEED);
    homeX = digitalRead(Y_HOME_PIN);
  }
}

void rotate90X() {
  step(true, X_DIR, X_STP, STEPS_90);
}

void rotate180X() {
  step(true, X_DIR, X_STP, STEPS_180);
}

void rotate90Y() {
  step(true, Y_DIR, Y_STP, STEPS_90);
}


void rotate180Y() {
  step(true, Y_DIR, Y_STP, STEPS_180);
}

void blockMotorY(int blockedTime) {
  int now = millis();
  while (millis() - now < blockedTime) {
    digitalWrite(X_STP, HIGH);
  }
  digitalWrite(X_STP, LOW);
}

void blockMotorX(int blockedTime) {
  int now = millis();
  while (millis() - now < blockedTime) {
    digitalWrite(Y_STP, HIGH);
  }
  digitalWrite(Y_STP, LOW);
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
  // reply only when you receive data
  if (Serial.available() > 0) {
    // read the incoming byte
    incomingByte = Serial.read();
    // convert it to char
    char i = incomingByte;
    Serial.println(i);

    switch (incomingByte) {
      case '1':
        rotate90Y();
        Serial.write('1');
        break;
      case '2':
        rotate180Y();
        Serial.write('2');
        break;
      case '3':
        rotate90X();
        Serial.write('3');
        break;
      case '4':
        rotate180X();
        Serial.write('4');
        break;
      case '5':
        calibrateY();
        Serial.write('5');
      case '6':
        calibrateX();
        Serial.write('6');
      default:
        Serial.write('7');
        break;
    }
  }
}


