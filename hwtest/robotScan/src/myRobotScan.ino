/******************************************************************************
myRobotScan.ino

Robot wonders using forward scanning for obstacle avoidance

Michael Margolis 28 May 2012
******************************************************************************/

#include <AFMotor.h>  // adafruit motor shield library
#include "RobotMotor.h"    // 2wd or 4wd motor library

#include "robotDefines.h"  // global defines

// Setup runs at startup and is used configure pins and init system variables
void setup()
{
  Serial.begin(9600);
  blinkNumber(8); // open port while flashing. Needed for Leonardo only    
  
  lookBegin(); 
  moveBegin();  
  moveSetSpeed(MIN_SPEED + 10) ;   // Run at 10% above minimum speed
  softServoWrite(90, 2000);        // center the servo 
  Serial.println("Ready");    
}

void loop()
{
   moveForward();
   roam();  // look around  
}

// function to indicate numbers by flashing the built-in LED
void blinkNumber( byte number) {
   pinMode(LED_PIN, OUTPUT); // enable the LED pin for output
   while(number--) {
     digitalWrite(LED_PIN, HIGH); delay(100);
     digitalWrite(LED_PIN, LOW);  delay(400);
   }
}
