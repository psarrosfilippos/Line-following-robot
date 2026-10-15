// Motor Driver Pin Definitions
const int MOTOR_A_POS = 13; // Motor A +
const int MOTOR_A_NEG = 12; // Motor A -
const int ENABLE_1_2  = 11; // Enable 1&2 (PWM Speed Motor A)
const int ENABLE_3_4  = 10; // Enable 3&4 (PWM Speed Motor B)
const int MOTOR_B_NEG = 9;  // Motor B -
const int MOTOR_B_POS = 8;  // Motor B +

// IR Sensor Pin Definitions
const int SENSOR_L1 = 6; // Far Left Sensor
const int SENSOR_L2 = 5; // Left Sensor
const int SENSOR_M  = 4; // Middle Sensor
const int SENSOR_R2 = 3; // Right Sensor
const int SENSOR_R1 = 2; // Far Right Sensor

/* Function Declarations */
void forward(void);
void backward(void);
void leftS(void);
void leftF(void);
void left(void);
void rightS(void);
void rightF(void);
void right(void);
void stopRobot(void);

void setup() {
  // Configure Motor Control Pins as OUTPUT
  pinMode(MOTOR_A_POS, OUTPUT);
  pinMode(MOTOR_A_NEG, OUTPUT);
  pinMode(ENABLE_1_2, OUTPUT);
  pinMode(ENABLE_3_4, OUTPUT);
  pinMode(MOTOR_B_NEG, OUTPUT);
  pinMode(MOTOR_B_POS, OUTPUT);

  // Configure Sensor Pins as INPUT
  pinMode(SENSOR_L1, INPUT);
  pinMode(SENSOR_L2, INPUT);
  pinMode(SENSOR_M, INPUT);
  pinMode(SENSOR_R2, INPUT);
  pinMode(SENSOR_R1, INPUT);
}

void loop() {
  // Read sensor states into variables for clean code
  int l1 = digitalRead(SENSOR_L1);
  int l2 = digitalRead(SENSOR_L2);
  int m  = digitalRead(SENSOR_M);
  int r2 = digitalRead(SENSOR_R2);
  int r1 = digitalRead(SENSOR_R1);

  // Decision Logic for Line Tracking
  if (l1 == 1 && l2 == 1 && m == 0 && r2 == 1 && r1 == 1) {
    forward();
  }
  else if (l1 == 1 && l2 == 1 && m == 1 && r2 == 1 && r1 == 1) {
    backward();
  }
  else if (l1 == 1 && l2 == 0 && m == 0 && r2 == 1 && r1 == 1) {
    leftS();
  }
  else if (l1 == 0 && l2 == 0 && m == 0 && r2 == 1 && r1 == 1) {
    leftF();
  }
  else if (l1 == 1 && l2 == 0 && m == 1 && r2 == 1 && r1 == 1) {
    left();
  }
  else if (l1 == 1 && l2 == 1 && m == 0 && r2 == 0 && r1 == 1) {
    rightS();
  }
  else if (l1 == 1 && l2 == 1 && m == 0 && r2 == 0 && r1 == 0) {
    rightF();
  }
  else if (l1 == 1 && l2 == 1 && m == 1 && r2 == 0 && r1 == 1) {
    right();
  }
  else if (l1 == 0 && l2 == 0 && m == 0 && r2 == 0 && r1 == 0) {
    stopRobot();
  }
}

/******************************************************************************
 * function forward
 * Purpose: Moves the robot straight ahead.
 * Arguments: None.
 * Results: Sets Motor A and B to forward direction.
 ******************************************************************************/
void forward(void) {
  digitalWrite(MOTOR_A_POS, HIGH);
  digitalWrite(MOTOR_A_NEG, LOW);
  digitalWrite(MOTOR_B_NEG, LOW);
  digitalWrite(MOTOR_B_POS, HIGH);
  analogWrite(ENABLE_1_2, 80);
  analogWrite(ENABLE_3_4, 80);
}

/******************************************************************************
 * function backward
 * Purpose: Moves the robot in reverse.
 * Arguments: None.
 * Results: Sets Motor A and B to reverse direction.
 ******************************************************************************/
void backward(void) {
  digitalWrite(MOTOR_A_POS, LOW);
  digitalWrite(MOTOR_A_NEG, HIGH);
  digitalWrite(MOTOR_B_NEG, HIGH);
  digitalWrite(MOTOR_B_POS, LOW);
  analogWrite(ENABLE_1_2, 60);
  analogWrite(ENABLE_3_4, 60);
}

/******************************************************************************
 * function leftS
 * Purpose: Executes a smooth left turn.
 * Arguments: None.
 * Results: Adjusts motor speed ratio for gentle left steering.
 ******************************************************************************/
void leftS(void) {
  digitalWrite(MOTOR_A_POS, HIGH);
  digitalWrite(MOTOR_A_NEG, LOW);
  digitalWrite(MOTOR_B_NEG, LOW);
  digitalWrite(MOTOR_B_POS, HIGH);
  analogWrite(ENABLE_1_2, 70);
  analogWrite(ENABLE_3_4, 60);
}

/******************************************************************************
 * function leftF
 * Purpose: Executes a sharp/fast left turn.
 * Arguments: None.
 * Results: Rotates motors for quick left spin.
 ******************************************************************************/
void leftF(void) {
  digitalWrite(MOTOR_A_POS, LOW);
  digitalWrite(MOTOR_A_NEG, HIGH);
  digitalWrite(MOTOR_B_NEG, LOW);
  digitalWrite(MOTOR_B_POS, HIGH);
  analogWrite(ENABLE_1_2, 60);
  analogWrite(ENABLE_3_4, 60);
}

/******************************************************************************
 * function left
 * Purpose: Executes a standard left turn.
 * Arguments: None.
 * Results: Steers robot to the left.
 ******************************************************************************/
void left(void) {
  digitalWrite(MOTOR_A_POS, HIGH);
  digitalWrite(MOTOR_A_NEG, LOW);
  digitalWrite(MOTOR_B_NEG, LOW);
  digitalWrite(MOTOR_B_POS, HIGH);
  analogWrite(ENABLE_1_2, 70);
  analogWrite(ENABLE_3_4, 50);
}

/******************************************************************************
 * function rightS
 * Purpose: Executes a smooth right turn.
 * Arguments: None.
 * Results: Adjusts motor speed ratio for gentle right steering.
 ******************************************************************************/
void rightS(void) {
  digitalWrite(MOTOR_A_POS, HIGH);
  digitalWrite(MOTOR_A_NEG, LOW);
  digitalWrite(MOTOR_B_NEG, LOW);
  digitalWrite(MOTOR_B_POS, HIGH);
  analogWrite(ENABLE_1_2, 60);
  analogWrite(ENABLE_3_4, 70);
}

/******************************************************************************
 * function rightF
 * Purpose: Executes a sharp/fast right turn.
 * Arguments: None.
 * Results: Rotates motors for quick right spin.
 ******************************************************************************/
void rightF(void) {
  digitalWrite(MOTOR_A_POS, HIGH);
  digitalWrite(MOTOR_A_NEG, LOW);
  digitalWrite(MOTOR_B_NEG, HIGH);
  digitalWrite(MOTOR_B_POS, LOW);
  analogWrite(ENABLE_1_2, 60);
  analogWrite(ENABLE_3_4, 60);
}

/******************************************************************************
 * function right
 * Purpose: Executes a standard right turn.
 * Arguments: None.
 * Results: Steers robot to the right.
 ******************************************************************************/
void right(void) {
  digitalWrite(MOTOR_A_POS, HIGH);
  digitalWrite(MOTOR_A_NEG, LOW);
  digitalWrite(MOTOR_B_NEG, LOW);
  digitalWrite(MOTOR_B_POS, HIGH);
  analogWrite(ENABLE_1_2, 50);
  analogWrite(ENABLE_3_4, 70);
}

/******************************************************************************
 * function stopRobot
 * Purpose: Brings both motors to a complete stop.
 * Arguments: None.
 * Results: Cuts power to motor outputs.
 ******************************************************************************/
void stopRobot(void) {
  digitalWrite(MOTOR_A_POS, LOW);
  digitalWrite(MOTOR_A_NEG, LOW);
  digitalWrite(MOTOR_B_NEG, LOW);
  digitalWrite(MOTOR_B_POS, LOW);
  analogWrite(ENABLE_1_2, 0);
  analogWrite(ENABLE_3_4, 0);
}