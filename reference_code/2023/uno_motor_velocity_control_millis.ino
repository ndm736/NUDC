// control the velocity of a the motor

#include <Encoder.h>

int LED = 13;  // there's always an LED on pin 13

// motor pins
int leftPWM = 5;
int leftDIR = 6;

// encoder pins
int leftEncoderA = 2;
int leftEncoderB = 3;
// swap A and B if turning the motor forwards gives a negative position
Encoder encoderLeft(leftEncoderB, leftEncoderA);
long encoderCountLeft = 0;

// some velocities to test
int vel_list_index = 0;
float vel_list[5] = { 0, 50, 150, 200, 250 };
int loopcount = 0;
// variables shared between loop() and motorPID()
volatile float desiredLeftVelocity = 0;
volatile float KP = 0.1;  // how hard to try to follow the desired velocity
volatile float KI = 0.001;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);  // turn on the LED so we know the arduino is on

  Serial.begin(115200);

  pinMode(leftPWM, OUTPUT);
  pinMode(leftDIR, OUTPUT);
  analogWrite(leftPWM, 0);
  digitalWrite(leftDIR, LOW);
}

// function that is called at 100Hz to control the motor velocity
void motorPID() {
  static float prevLeftAngle = 0; // remember the previous angle to calculate velocity with
  static int leftDuty = 0; 
  static int decimate = 0; // don't print every time, this is used to print at a slower rate
  static float leftVelocity = 0;
  static float leftVI = 0; // integral of the velocity
  float leftAngle, leftInstantVelocity;

  // calculate the motor angle
  encoderCountLeft = encoderLeft.read();
  leftAngle = encoderCountLeft * 360.0 / 1632.0;

  // calculate the motor velocity
  leftInstantVelocity = (leftAngle - prevLeftAngle) / 0.01; // this function happens at 100Hz, or every 0.01s
  leftVelocity = 0.5*leftVelocity + 0.5*leftInstantVelocity; // filter the velocity signal to smooth out

  // remember the position for next time (needed for velocity calculation)
  prevLeftAngle = leftAngle;

  // calculate error in velocity
  float leftVelocityError = desiredLeftVelocity - leftVelocity;
  leftVI = leftVI + leftVelocityError; // integrate the error

  // if the velocity error is 0, then continue to use the duty cycle
  // else change the duty cycle accordingly
  int leftDutyChange = KP * leftVelocityError + KI * leftVI;
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

  // plot the data every once in a while, not necessary once everything is working
  decimate++;
  if (decimate == 4) {
    decimate = 0;
    Serial.print(desiredLeftVelocity);
    Serial.print(" ");
    Serial.print(leftDuty);
    Serial.print(" ");
    Serial.println(leftVelocity);
  }
}

void loop() {
  // limit the loop speed to 100Hz
  long start_time = millis();
  motorPID();
  //Serial.println(millis()-start_time); // print how much time the function took
  while (millis() - start_time < 10) {}
  
  // sit at one desied velocity for 3 seconds
  loopcount++;
  if (loopcount % 300 == 0) {
    vel_list_index++;
  }
  if (vel_list_index == 5) {
    vel_list_index = 0;
  }
  desiredLeftVelocity = vel_list[vel_list_index];
}