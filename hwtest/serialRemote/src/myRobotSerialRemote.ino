/******************************************************************************
myRobotSerialRemote.ino

Robot sketch with serial remote commands

Created by Michael Margolis 10 June 2012
******************************************************************************/

#include <AFMotor.h>  // adafruit motor shield library
#include "RobotMotor.h"    // 2wd or 4wd motor library

#include "robotDefines.h"  // global defines

const char* states[] = {"Left", "Right", "Forward", "Back", "Rotate", "Stop"};
const char* locationString[] = {"Left", "Right", "Center"}; // labels for debug

#include "Remote.h"


// Setup runs at startup and is used configure pins and init system variables
void setup()
{
  Serial.begin(9600);    
  while(!Serial);  // only needed for leonardo
  
  moveBegin();  
  moveSetSpeed(MIN_SPEED + 10) ;  // Run at 10% above minimum speed     
}

void loop()
{
  remoteService(); // wait for serial commands
}

// function to check if robot can continue moving when taking evasive action
// returns true if robot is not blocked when moving to avoid obstacles
// this 'placeholder' version always returns true
boolean checkMovement()
{
  return true; 
}

