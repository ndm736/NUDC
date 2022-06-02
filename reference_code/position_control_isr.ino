// use a timer based interrupt to control the velocities of the motors
// timer based interrupt: https://www.pjrc.com/teensy/td_timing_IntervalTimer.html

IntervalTimer myTimer;

#include <Encoder.h>

int LED = 13; // there's always an LED on pin 13

// motor pins
int leftPWM = 2;
int leftDIR = 3;
int rightPWM = 4;
int rightDIR = 5;

// encoder pins
int leftEncoderA = 6;
int leftEncoderB = 7;
int rightEncoderA = 8;
int rightEncoderB = 9;
// swap A and B if turning the motor forwards gives a negative position
Encoder encoderLeft(leftEncoderB, leftEncoderA);
Encoder encoderRight(rightEncoderA, rightEncoderB);
long encoderCountLeft  = 0;
long encoderCountRight = 0;

// variables shared between loop() and motorPID()
volatile float desiredLeftVelocity = 0;
volatile float desiredRightVelocity = 0;
volatile float KP = 0.1; // how hard to try to follow the desired velocity

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // turn on the LED so we know the teensy is on

  Serial.begin(9600);

  pinMode(leftPWM, OUTPUT);
  pinMode(leftDIR, OUTPUT);
  analogWrite(leftPWM, 0);
  digitalWrite(leftDIR, LOW);

  pinMode(rightPWM, OUTPUT);
  pinMode(rightDIR, OUTPUT);
  analogWrite(rightPWM, 0);
  digitalWrite(rightDIR, LOW);

  // turn on the automatic function call to control the motor velocities
  myTimer.begin(motorPID, 10000);  //(in microseconds) run motorPID() every 0.01s (100Hz)
}


// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.
void motorPID() {
  static float prevLeftAngle = 0;
  static float prevRightAngle = 0;
  static int leftDuty = 0;
  static int rightDuty = 0;

  float leftAngle, leftVelocity;
  float rightAngle, rightVelocity;

  // calculate the motor angles
  encoderCountLeft = encoderLeft.read();
  encoderCountRight = encoderRight.read();
  leftAngle = encoderCountLeft * 360.0 / 1632.0;
  rightAngle = encoderCountRight * 360.0 / 1632.0;

  // calculate the motor velocities (to do: filter for smoothness)
  leftVelocity = (leftAngle - prevLeftAngle) / 0.01;
  rightVelocity = (rightAngle - prevRightAngle) / 0.01;
  Serial.print(leftVelocity);
  Serial.print(" ");
  Serial.println(rightVelocity);
  // remember the position for next time (needed for velocity calculation)
  prevLeftAngle = leftAngle;
  prevRightAngle = rightAngle;

  // calculate error in velocity
  float leftVelocityError = desiredLeftVelocity - leftVelocity;
  float rightVelocityError = desiredRightVelocity - rightVelocity;

  // if the velocity error is 0, then continue to use the duty cycle
  // else change the duty cycle accordingly
  int leftDutyChange = KP * leftVelocityError;
  leftDuty += leftDutyChange;
  if (leftDuty < 0) {
    leftDuty = 0;
  }
  if (leftDuty > 255) {
    leftDuty = 255;
  }
  // to do: negative velocities
  analogWrite(leftPWM, leftDuty);
  digitalWrite(leftDIR, HIGH);

  int rightDutyChange = KP * rightVelocityError;
  rightDuty += rightDutyChange;
  if (rightDuty < 0) {
    rightDuty = 0;
  }
  if (rightDuty > 255) {
    rightDuty = 255;
  }
  analogWrite(rightPWM, rightDuty);
  digitalWrite(rightDIR, LOW);
}

void loop() {
  // set the desired velocity and the motorPID() function makes it happen
  desiredLeftVelocity = 0;
  desiredRightVelocity = 0;
  delay(1000);

  desiredLeftVelocity = 200;
  desiredRightVelocity = 200;
  delay(1500);

  desiredLeftVelocity = 600;
  desiredRightVelocity = 600;
  delay(1500);
}
