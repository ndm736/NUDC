// Drive the two motors forwards and backwards at different speeds
// motor driver - https://www.pololu.com/product/2960

int LED = 13; // there's always an LED on pin 13

// motor pins
int leftPWM = 2;
int leftDIR = 3;
int rightPWM = 4;
int rightDIR = 5;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH); // turn on the LED so we know the teensy is on
  Serial.begin(9600);

  // set up the motor pins
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

  analogWrite(rightPWM, 128);
  digitalWrite(rightDIR, LOW);
  Serial.println("RIGHT LOW 50%");
  delay(3000);

  analogWrite(rightPWM, 255);
  digitalWrite(rightDIR, LOW);
  Serial.println("RIGHT LOW 100%");
  delay(3000);

  analogWrite(rightPWM, 128);
  digitalWrite(rightDIR, HIGH);
  Serial.println("RIGHT HIGH 50%");
  delay(3000);

  analogWrite(rightPWM, 255);
  digitalWrite(rightDIR, HIGH);
  Serial.println("RIGHT HIGH 100%");
  delay(3000);

  analogWrite(rightPWM, 0);
  digitalWrite(rightDIR, LOW);
  Serial.println("BOTH OFF");
  delay(3000);

}
