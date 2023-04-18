// Drive the motor forwards and backwards at different speeds
// motor driver - https://www.pololu.com/product/2960

int LED = 13; // there's always an LED on pin 13

// motor pins
int leftPWM = 5; // ENABLE
int leftDIR = 6; // PHASE

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // turn on the LED so we know the teensy is on
  Serial.begin(9600);

  // set up the motor pins
  pinMode(leftPWM, OUTPUT);
  pinMode(leftDIR, OUTPUT);
  analogWrite(leftPWM, 0);
  digitalWrite(leftDIR, LOW);
}

void loop() {
  // note the direction of the motor depends on the DIR pin, the two motors are probably opposite
  analogWrite(leftPWM, 128);
  digitalWrite(leftDIR, LOW);
  Serial.println("LEFT LOW 50%");
  delay(3000);

  analogWrite(leftPWM, 255);
  digitalWrite(leftDIR, LOW);
  Serial.println("LEFT LOW 100%");
  delay(3000);

  analogWrite(leftPWM, 128);
  digitalWrite(leftDIR, HIGH);
  Serial.println("LEFT HIGH 50%");
  delay(3000);

  analogWrite(leftPWM, 255);
  digitalWrite(leftDIR, HIGH);
  Serial.println("LEFT HIGH 100%");
  delay(3000);

  analogWrite(leftPWM, 0);
  digitalWrite(leftDIR, LOW);
  Serial.println("BOTH OFF");
  delay(3000);
}