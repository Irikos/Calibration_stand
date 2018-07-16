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

void step (boolean dir, byte dirPin, byte stepperPin, int steps)
{
    digitalWrite (dirPin, dir);
    delay (50);
    for (int i = 0; i < steps; i++) 
    {
        digitalWrite (stepperPin, HIGH);
        delayMicroseconds (800);
        digitalWrite (stepperPin, LOW);
        delayMicroseconds (800);
    }
}

void setup () {   // The stepper motor used in the IO pin is set to output
    pinMode (MOTOR_1_DIR, OUTPUT); pinMode (MOTOR_1_STEP, OUTPUT);
    pinMode (MOTOR_2_DIR, OUTPUT); pinMode (MOTOR_2_STEP, OUTPUT);
    pinMode (MOTOR_3_DIR, OUTPUT); pinMode (MOTOR_3_STEP, OUTPUT);
    pinMode (MOTOR_4_DIR, OUTPUT); pinMode (MOTOR_4_STEP, OUTPUT);
    pinMode (EN, OUTPUT);
    digitalWrite (EN, LOW);
}

void loop () {
    step (false, MOTOR_1_DIR, MOTOR_1_STEP, STEPS); // X 
    step (false, MOTOR_2_DIR, MOTOR_2_STEP, STEPS); // z
    step (false, MOTOR_3_DIR, MOTOR_3_STEP, STEPS); // y 
    step (false, MOTOR_4_DIR, MOTOR_4_STEP, STEPS); // a 
    delay (1000);
    step (true, MOTOR_1_DIR, MOTOR_1_STEP, STEPS); // X 
    step (true, MOTOR_2_DIR, MOTOR_2_STEP, STEPS); // z
    step (true, MOTOR_3_DIR, MOTOR_3_STEP, STEPS); // y 
    step (false, MOTOR_4_DIR, MOTOR_4_STEP, STEPS); // a
    delay (1000);
} 
