// ramp up the motor speed while printing the velocity
#include <Encoder.h>

int LED = 13; // there's always an LED on pin 13

int leftPWM = 5;
int leftDIR = 6;

int leftEncoderA = 2;
int leftEncoderB = 3;
// swap A and B if turning the motor forwards gives a negative position
Encoder encoderLeft(leftEncoderB, leftEncoderA);
long encoderCountLeft  = 0;

void setup() {

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // turn on the LED so we know the teensy is on

  Serial.begin(9600);

  pinMode(leftPWM, OUTPUT);
  pinMode(leftDIR, OUTPUT);
  analogWrite(leftPWM, 0);
  digitalWrite(leftDIR, LOW);
}

void loop() {
  int i = 0;
  int j = 0;
  float leftAngle1 = 0, leftAngle2 = 0, leftVelocity;
  delay(5000);

  // ramp up the velocity
  for (i = 0; i < 255; i=i+5) {
    analogWrite(leftPWM, i);
    digitalWrite(leftDIR, HIGH);
    // calculate the velocity and print
    for (j = 0; j < 1; j++) {
      encoderCountLeft = encoderLeft.read();
      leftAngle1 = encoderCountLeft * 360.0 / 1632.0;
      delay(100);
      encoderCountLeft = encoderLeft.read();
      leftAngle2 = encoderCountLeft * 360.0 / 1632.0;
      leftVelocity = (leftAngle2 - leftAngle1) / 0.1;
      Serial.print(100);
      Serial.print(" ");
      Serial.print(i);
      Serial.print(" ");
      Serial.println(leftVelocity);
      delay(10);
    }
  }
  // ramp down the velocity
  for (i = 255; i > 0; i=i-5) {
    analogWrite(leftPWM, i);
    digitalWrite(leftDIR, HIGH);
    for (j = 0; j < 1; j++) {
      encoderCountLeft = encoderLeft.read();
      leftAngle1 = encoderCountLeft * 360.0 / 1632.0;
      delay(100);
      encoderCountLeft = encoderLeft.read();
      leftAngle2 = encoderCountLeft * 360.0 / 1632.0;
      leftVelocity = (leftAngle2 - leftAngle1) / 0.1;
      Serial.print(100);
      Serial.print(" ");
      Serial.print(i);
      Serial.print(" ");
      Serial.println(leftVelocity);
      delay(10);
    }
  }

  
  for (i = 0; i < 255; i=i+5) {
    analogWrite(leftPWM, i);
    digitalWrite(leftDIR, LOW);
    for (j = 0; j < 1; j++) {
      encoderCountLeft = encoderLeft.read();
      leftAngle1 = encoderCountLeft * 360.0 / 1632.0;
      delay(100);
      encoderCountLeft = encoderLeft.read();
      leftAngle2 = encoderCountLeft * 360.0 / 1632.0;
      leftVelocity = (leftAngle2 - leftAngle1) / 0.1;
      Serial.print(-100);
      Serial.print(" ");
      Serial.print(-i);
      Serial.print(" ");
      Serial.println(leftVelocity);
      delay(10);
    }
  }

  for (i = 255; i > 0; i=i-5) {
    analogWrite(leftPWM, i);
    digitalWrite(leftDIR, LOW);
    for (j = 0; j < 1; j++) {
      encoderCountLeft = encoderLeft.read();
      leftAngle1 = encoderCountLeft * 360.0 / 1632.0;
      delay(100);
      encoderCountLeft = encoderLeft.read();
      leftAngle2 = encoderCountLeft * 360.0 / 1632.0;
      leftVelocity = (leftAngle2 - leftAngle1) / 0.1;
      Serial.print(-100);
      Serial.print(" ");
      Serial.print(-i);
      Serial.print(" ");
      Serial.println(leftVelocity);
      delay(10);
    }
  }

}