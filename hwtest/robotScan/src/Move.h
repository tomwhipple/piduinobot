#ifndef _Move_h
#define _Move_h


#include "robotDefines.h"
#include "RobotMotor.h"


void moveBegin();
void moveLeft();
void moveRight();
void moveForward();
void moveBackward();
void moveRotate(int angle);

void moveStop();
void moveBrake();
void moveSetSpeed(int speed);
void moveSlower(int decrement);
void moveFaster(int increment);
int moveGetState();

long rotationAngleToTime( int angle, int speed);
void calibrateRotationRate(int direction, int angle);
void changeMoveState(int newState);
void timedMove(int direction, int duration);
void movingDelay(long duration);

// HACK: circular dependency!!  
extern boolean checkMovement();

#endif