
/*******************************************
* Basic motor test
* Copy AFMotor library and RobotMotor libraries to Arduino library folder
* Navigate to RobotMotor: 
*   for 4WD, copy RobotMotor4wd/RobotMotor.cpp into RobotMotor folder
*   for 2WD, copy RobotMotor2wd/RobotMotor.cpp into RobotMotor fold


* Compile and run the sketch :


* robot rotates clockwise for 2 seconds
* pause 2 seconds 
* robot rotates counter-clockwise for 2 seconds
* pause 2 seconds
* robot runs forward for 2 seconds
* pause 2 seconds
* robot runs backwards for 2 seconds
* pause 5 seconds

* Michael Margolis 24 July 2012

********************************************/
// include motor libraries
#include <AFMotor.h>     // adafruit motor shield library
#include <RobotMotor.h>  // 2wd or 4wd motor library

#define LED_PIN 13

int moveSpeed = 60; // the speed to run (as a % of maximum speed) 
int pauseMs = 2000; // time in ms for each movement

void setup()
{
  Serial.begin(9600);
  Serial.println("starting\n");
  blinkNumber(8); // open port while flashing. Needed for Leonardo only  
  motorBegin(MOTOR_LEFT); 
  motorBegin(MOTOR_RIGHT); 
  test();
}

void loop()
{
}

// function to indicate numbers by flashing the built-in LED
void blinkNumber( byte number) {
   pinMode(LED_PIN, OUTPUT); // enable the LED pin for output
   while(number--) {
     digitalWrite(LED_PIN, HIGH); delay(100);
     digitalWrite(LED_PIN, LOW);  delay(400);
   }
}

void test()
{
  Serial.println("Moving...\n");
  rotateLeft();
  delay(pauseMs); // run for 2 seconds
  stopAndWait(pauseMs);
  rotateRight();
  delay(pauseMs); // run for 2 seconds
  stopAndWait(pauseMs);
  moveForward();
  delay(pauseMs); // run for 2 seconds
  stopAndWait(pauseMs); 
  moveBackward();
  delay(pauseMs); // run for 2 seconds
  stopAndWait(pauseMs);
  
  Serial.println("Done.\n");
}

void moveForward()
{
  Serial.println("forward");
  motorForward(MOTOR_LEFT,  moveSpeed);
  motorForward(MOTOR_RIGHT, moveSpeed);
}

void moveBackward()
{
  Serial.println("backward");
  motorReverse(MOTOR_LEFT, moveSpeed);
  motorReverse(MOTOR_RIGHT, moveSpeed);  
}

void rotateLeft()
{
  Serial.println("Rotating left");  
  motorReverse(MOTOR_LEFT,  moveSpeed); 
  motorForward(MOTOR_RIGHT, moveSpeed);  
}
void rotateRight()
{
  Serial.println("Rotating right");  
  motorForward(MOTOR_LEFT,  moveSpeed);
  motorReverse(MOTOR_RIGHT, moveSpeed);
}

void stopAndWait(int waitTime)
{
  motorStop(MOTOR_LEFT);
  motorStop(MOTOR_RIGHT);
  delay(waitTime);
}


