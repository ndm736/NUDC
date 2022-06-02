// ramp up the motor speeds while printing the velocities
#include <Encoder.h>

int LED = 13; // there's always an LED on pin 13

int leftPWM = 2;
int leftDIR = 3;
int rightPWM = 4;
int rightDIR = 5;

int leftEncoderA = 6;
int leftEncoderB = 7;
int rightEncoderA = 8;
int rightEncoderB = 9;
// swap A and B if turning the motor forwards gives a negative position
Encoder encoderLeft(leftEncoderB, leftEncoderA);
Encoder encoderRight(rightEncoderA, rightEncoderB);
long encoderCountLeft  = 0;
long encoderCountRight = 0;


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
}

void loop() {
  int i = 0;
  int j = 0;
  float leftAngle1 = 0, leftAngle2 = 0, leftVelocity;
  float rightAngle1 = 0, rightAngle2 = 0, rightVelocity;

  for (i = 0; i < 255; i++) {
    analogWrite(leftPWM, i);
    digitalWrite(leftDIR, HIGH);
    analogWrite(rightPWM, i);
    digitalWrite(rightDIR, LOW);
    for (j = 0; j < 1; j++) {
      encoderCountLeft = encoderLeft.read();
      encoderCountRight = encoderRight.read();
      leftAngle1 = encoderCountLeft * 360.0 / 1632.0;
      rightAngle1 = encoderCountRight * 360.0 / 1632.0;
      delay(100);
      encoderCountLeft = encoderLeft.read();
      encoderCountRight = encoderRight.read();
      leftAngle2 = encoderCountLeft * 360.0 / 1632.0;
      rightAngle2 = encoderCountRight * 360.0 / 1632.0;
      leftVelocity = (leftAngle2 - leftAngle1) / 0.1;
      rightVelocity = (rightAngle2 - rightAngle1) / 0.1;
      Serial.print(i);
      Serial.print(" ");
      Serial.print(leftVelocity);
      Serial.print(" ");
      Serial.println(rightVelocity);
      delay(100);
    }
  }

  for (i = 255; i > 0; i--) {
    analogWrite(leftPWM, i);
    digitalWrite(leftDIR, HIGH);
    analogWrite(rightPWM, i);
    digitalWrite(rightDIR, LOW);
    for (j = 0; j < 1; j++) {
      encoderCountLeft = encoderLeft.read();
      encoderCountRight = encoderRight.read();
      leftAngle1 = encoderCountLeft * 360.0 / 1632.0;
      rightAngle1 = encoderCountRight * 360.0 / 1632.0;
      delay(100);
      encoderCountLeft = encoderLeft.read();
      encoderCountRight = encoderRight.read();
      leftAngle2 = encoderCountLeft * 360.0 / 1632.0;
      rightAngle2 = encoderCountRight * 360.0 / 1632.0;
      leftVelocity = (leftAngle2 - leftAngle1) / 0.1;
      rightVelocity = (rightAngle2 - rightAngle1) / 0.1;
      Serial.print(i);
      Serial.print(" ");
      Serial.print(leftVelocity);
      Serial.print(" ");
      Serial.println(rightVelocity);
      delay(100);
    }
  }
}
