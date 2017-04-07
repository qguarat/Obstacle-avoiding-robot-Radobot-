#include <Servo.h>
#include "Ultrasonic.h"

int motorA1 = 12;
int motorA2 = 11;
int motorB1 = 10;
int motorB2 = 9;
int servoPin = 13;
int utp = 5;
int uep = 4;

int enA = 8;
int enB = 7;
bool moving = false;
Servo servo;
Ultrasonic usonic(uep, utp);

int rightDistance = 0;
int leftDistance = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  servo.attach(servoPin);
  pinMode(uep, INPUT);
  pinMode(utp, OUTPUT);

  //pinMode(enA, OUTPUT);
  //pinMode(enB, OUTPUT);

  
  analogWrite(enA, 240);
  analogWrite(enB, 255);
  //digitalWrite(enA, LOW);
  //digitalWrite(enB, LOW);
  
  
}

void loop()
{
  rightDistance = 0;
  leftDistance = 0;

  triggerParktronic();
  long duration = pulseIn(uep, HIGH);
  long cm = microsecondsToCentimeters(duration);
  
  if(cm <= 10)
  {
    stopAndBackward();
    rightDistance = lookRight();
    delay(1500);
    leftDistance = lookLeft();
    delay(1500);

    if(rightDistance > leftDistance)
    {
      right();
      delay(1500);
    }
    else if(leftDistance > rightDistance)
    {
      left();
      delay(1500);
    }
    else if(leftDistance == rightDistance)
    {
      right();
      delay(1500);
    }
  }

  forward();
  servo.write(90);

  delay(150);
}

void forward()
{
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void backward()
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void left()
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void right()
{
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW); 
}

void stopMotors()
{
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

void triggerParktronic() // function to send sound waves
{
  digitalWrite(utp, LOW);
  delayMicroseconds(2);
  digitalWrite(utp, HIGH);
  delayMicroseconds(10);
  digitalWrite(utp, LOW);
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29 / 2;
}

void stopAndBackward()
{
    stopMotors();
    backward();
    delay(1000);
    stopMotors();
}

int lookRight()
{
  servo.write(150);
  triggerParktronic();
  long duration = pulseIn(uep, HIGH);
  long cm = microsecondsToCentimeters(duration);
  
  return cm;
}

int lookLeft()
{
  servo.write(30);
  triggerParktronic();
  long duration = pulseIn(uep, HIGH);
  long cm = microsecondsToCentimeters(duration);
  
  return cm;
}

