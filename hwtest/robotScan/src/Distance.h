#ifndef _Distance_h
#define _Distance_h

#include <Arduino.h>

int pingGetDistance(int pingPin);
long microsecondsToCentimeters(long microseconds);
int irGetDistance(byte pin);
int mvToDistance(int mV);



#endif