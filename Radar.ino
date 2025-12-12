#include "Servo.h"
#include <LedControl.h>

Servo myservo;

// Servo pins
#define servoPin 9
#define triggerPin 12
#define echoPin 11

float duration, distance;

// Matrix pins
int DIN = 7;
int CS = 6;
int CLK = 5;

int RotationLeft = 160;
int RotationRight = 80;
int step = 10;

LedControl lc = LedControl(DIN, CLK, CS, 1);

void setup() {
  Serial.begin(9600);

  myservo.attach(servoPin);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}

void loop() {


  for (int angle = RotationRight + step; angle <= RotationLeft; angle += step) {
      scanAndDisplay(angle);
  }


  for (int angle = RotationLeft - step; angle >= RotationRight; angle -= step) {
      scanAndDisplay(angle);
  }
}

void scanAndDisplay(int angle) {
  myservo.write(angle);
  delay(250);


  float dist = getDistance();

  // Map angle - row
  int row = map(angle, RotationRight, RotationLeft, 7, 0); 

  row = constrain(row, 0, 7);

  // Map distance - column 
  int col = map(dist, 0, 80, 7, 0);
  col = constrain(col, 0, 7);



  if(angle == RotationLeft || angle == RotationRight){
    lc.clearDisplay(0);
  }
  
  // Light the LED
  lc.setLed(0, row, col, true);

  delay(250);

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print("  Distance: ");
  Serial.print(dist);
  Serial.print(" cm → LED at (row=");
  Serial.print(row);
  Serial.print(" col=");
  Serial.print(col);
  Serial.println(")");
}

float getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;

  return distance;
}
