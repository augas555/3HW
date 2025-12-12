
#include "Servo.h"

Servo myservo;

// Define the servo pin:
#define servoPin 9
#define triggerPin 12
#define echoPin 11
float duration, distance;

void setup() {
  myservo.attach(servoPin);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {

  for (int angle = 60; angle <= 240; angle += 10) {
    myservo.write(angle);
    delay(500);
    UltraSonic();
  }
  for (int angle = 240; angle >= 60; angle -= 10) {
      myservo.write(angle);
      delay(500);
      UltraSonic();
    }


}

void UltraSonic(){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(500);

}