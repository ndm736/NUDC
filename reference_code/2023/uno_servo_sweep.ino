// sweep the servo from 10 degrees to 170 degrees
// then move as fast as possible 90 degrees

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  // pin 9 to Orange wire
  // 5V to Red wire
  // GND to Brown wire
}

void loop() {
  int pos;
  for (pos = 10; pos <= 170; pos += 1) { 
    // in steps of 1 degree
    myservo.write(pos); 
    delay(30);  
  }
  for (pos = 170; pos >= 10; pos -= 1) {
    myservo.write(pos); 
    delay(30);
  }

  delay(3000); // wait 5 seconds
  // servo is at 10 degrees
  myservo.write(100); // move as quickly as possible to 100 degrees
  delay(3000);
  myservo.write(10);
  delay(3000);
}
