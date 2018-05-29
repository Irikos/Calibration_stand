#define EN        8       // stepper motor enable, low level effective
#define X_DIR     5//5       //X axis, stepper motor direction control 
#define Y_DIR     3//6       //y axis, stepper motor direction control
#define Z_DIR     7       //zaxis, stepper motor direction control
#define X_STP     2//2       //x axis, stepper motor control
#define Y_STP     6//3       //y axis, stepper motor control
#define Z_STP     4       //z axis, stepper motor control

#define Y_HOME_PIN 13
#define X_HOME_PIN 12

#define 90_STEPS 800
#define 180_STEPS 1600

int incomingByte = 0;  // for incoming serial data

void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
  digitalWrite(dirPin, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(800);
  }
}

void calibrateY() {
  boolean homeY = digitalRead(Y_HOME_PIN);
  digitalWrite(Y_DIR, true);
  while (!homeY) {
    digitalWrite(Y_STP, HIGH);
    delayMicroseconds(800);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(800);
    homeY = digitalRead(Y_HOME_PIN);
  }
}


void calibrateX() {
  boolean homeX = digitalRead(X_HOME_PIN);
  digitalWrite(X_DIR, true);
  while (!homeX) {
    digitalWrite(X_STP, HIGH);
    delayMicroseconds(800);
    digitalWrite(X_STP, LOW);
    delayMicroseconds(800);
    homeX = digitalRead(Y_HOME_PIN);
  }
}

void rotate90X() {
  step(true, X_DIR, X_STP, 90_STEPS);
}

void rotate180X() {
  step(true, X_DIR, X_STP, 180_STEPS);
}

void rotate90Y() {
  step(true, Y_DIR, Y_STP, 90_STEPS);
}


void rotate180Y() {
  step(true, Y_DIR, Y_STP, 180_STEPS);
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
  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  pinMode(Y_HOME_PIN, INPUT);
  pinMode(X_HOME_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
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


