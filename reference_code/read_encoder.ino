// read the two motor encoders and print the angles

#include <Encoder.h> // https://www.pjrc.com/teensy/td_libs_Encoder.html

int LED = 13; // there's always an LED on pin 13

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

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // turn on the LED so we know the teensy is on
  Serial.begin(9600);
}

void loop() {
  encoderCountLeft = encoderLeft.read();
  encoderCountRight = encoderRight.read();

  // quadrature encoder has 12 lines, motor gear ratio is 34, so 4*12*34=1632 pulses per revolution
  float leftAngle = encoderCountLeft * 360.0 / 1632.0;
  float rightAngle = encoderCountRight * 360.0 / 1632.0;
  // turn the motor by hand to see the angle change
  Serial.print(leftAngle);
  Serial.print(" ");
  Serial.println(rightAngle);
  delay(100);
}
