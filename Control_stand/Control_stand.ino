// Motors are numbered bottom up, meaning Motor 1 is the motor on the bottom of the leg (aka the knee) while Motor 4 is the motor on the top of the leg (the rotating part of the hip)
# define EN 8 // stepper motor enable , active low
# define MOTOR_1_DIR 5 // X
# define MOTOR_2_DIR 7 // Z
# define MOTOR_3_DIR 6 // Y
# define MOTOR_4_DIR 13 // A

# define MOTOR_1_STEP 2
# define MOTOR_2_STEP 4
# define MOTOR_3_STEP 3
# define MOTOR_4_STEP 12

#define STEPS 1500
#define MOTOR_SPEED 800

#define MOTOR_SPEED_17 600
#define MOTOR_SPEED_14 25 // 1:100 + rotile de plastic

#define STEP_14 0.001125
#define STEP_14_ANGLE 0.000375 // 0.000375
#define STEP_17_ANGLE 5625 // 0.05625

long M1Position = 0;
long M1Target = 9000000; // 5625 / 100.000
int M1Speed = 1;
bool M1State = LOW;
bool M1Initialized = false;

float M2Position = 0;
float M2Target = 90;
int M2Speed = 1;
bool M2State = LOW;
bool M2Initialized = false;

float M3Position = 0;
float M3Target = 90;
int M3Speed = 1;
bool M3State = LOW;
bool M3Initialized = false;

float M4Position = 0;
float M4Target = 180;
int M4Speed = 60;
bool M4State = LOW;
bool M4Initialized = false;

int globalCounter = 0;

#include <ArduinoJson.h>
#include <Math.h>

char incomingBytes[128];
int serialSize = 0;
StaticJsonBuffer<200> jsonBuffer;

void step (boolean dir, byte dirPin, byte stepperPin, int steps)
{
    digitalWrite (dirPin, dir);
    delay (50);
    for (int i = 0; i < steps; i++) 
    {
        digitalWrite (stepperPin, HIGH);
        delayMicroseconds (MOTOR_SPEED);
        digitalWrite (stepperPin, LOW);
        delayMicroseconds (MOTOR_SPEED);
    }
}

void setup () {   // The stepper motor used in the IO pin is set to output
    pinMode (MOTOR_1_DIR, OUTPUT); pinMode (MOTOR_1_STEP, OUTPUT);
    pinMode (MOTOR_2_DIR, OUTPUT); pinMode (MOTOR_2_STEP, OUTPUT);
    pinMode (MOTOR_3_DIR, OUTPUT); pinMode (MOTOR_3_STEP, OUTPUT);
    pinMode (MOTOR_4_DIR, OUTPUT); pinMode (MOTOR_4_STEP, OUTPUT);
    pinMode (EN, OUTPUT);
    digitalWrite (EN, LOW);
    
    globalCounter = (globalCounter + 1) % (M1Speed + M2Speed + M3Speed + M4Speed);
    Serial.begin(9600);
}

void M1Step() {
    digitalWrite(MOTOR_1_DIR, HIGH);
    if (globalCounter % M1Speed == 0 && abs(M1Target - M1Position) >= STEP_17_ANGLE && M1State == LOW) {
    digitalWrite(MOTOR_1_STEP, HIGH);
    M1State = HIGH;
    M1Position += STEP_17_ANGLE;
  }
  
  if (globalCounter % M1Speed == 0 && abs(M1Target - M1Position) >= STEP_17_ANGLE && M1State == HIGH) {
    digitalWrite(MOTOR_1_STEP, LOW);
    M1State = LOW;
  }
  Serial.println(M1Position);
}

void M2Step() {
    digitalWrite(MOTOR_2_DIR, LOW);
    if (globalCounter % M2Speed == 0 && abs(M2Target - M2Position) > STEP_14_ANGLE && M2State == LOW) {
    digitalWrite(MOTOR_2_STEP, HIGH);
    M2State = HIGH;
    M2Position += STEP_14_ANGLE;
  }
  
  if (globalCounter % M2Speed == 0 && abs(M2Target - M2Position) > STEP_14_ANGLE && M2State == HIGH) {
    digitalWrite(MOTOR_2_STEP, LOW);
    M2State = LOW;
  }
}

void M3Step() {
    digitalWrite(MOTOR_3_DIR, HIGH);
    digitalWrite(MOTOR_3_DIR, HIGH);
    if (globalCounter % M3Speed == 0 && abs(M3Target - M3Position) > STEP_14_ANGLE && M3State == LOW) {
    digitalWrite(MOTOR_3_STEP, HIGH);
    M3State = HIGH;
    M3Position += STEP_14_ANGLE;
  }
  
  if (globalCounter % M3Speed == 0 && abs(M3Target - M3Position) > STEP_14_ANGLE && M3State == HIGH) {
    digitalWrite(MOTOR_3_STEP, LOW);
    M3State = LOW;
  }
}


void M4Step() {
    digitalWrite(MOTOR_4_DIR, HIGH);
    if (globalCounter % M4Speed == 0 && abs(M4Target - M4Position) > STEP_17_ANGLE && M4State == LOW) {
    digitalWrite(MOTOR_4_STEP, HIGH);
    M4State = HIGH;
    M4Position += STEP_17_ANGLE;
  }
  
  if (globalCounter % M4Speed == 0 && abs(M4Target - M4Position) > STEP_17_ANGLE && M4State == HIGH) {
    digitalWrite(MOTOR_4_STEP, LOW);
    M4State = LOW;
  }
}

void loop () {
  globalCounter = (globalCounter + 1) % (M1Speed + M2Speed + M3Speed + M4Speed);

  M1Step();
//  M2Step();
//  M3Step();
//  M4Step();
  



// serial part
//  serialSize = Serial.available();
//  incomingBytes[serialSize] = '\0';
//  char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
//  for (int i = 0; i < serialSize; i++) {
//    incomingBytes[i] = Serial.read();
//  }
//  if (incomingBytes[0] != '\0') {
//    JsonObject& root = jsonBuffer.parseObject(incomingBytes);
//    if (!root.success()) {
//      Serial.println("parseObject() failed");
//      return;
//    } else {
//      long times = root["time"];
//      for (int i = 0; i < 63; i++) {
//        Serial.print(json[i]);
//      }
//      Serial.println("-----------------------------");
//      Serial.write(incomingBytes);
//      Serial.println("+++++++++++++++++++++++++");
//    }
//    incomingBytes[0] = '\0';
//  }
}
