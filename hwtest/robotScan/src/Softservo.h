#ifndef _Softservo_h
#define _Softservo_h

#include <Arduino.h>

void softServoAttach(int pin);
void softServoWrite(int angle, long servoDelay);

#endif