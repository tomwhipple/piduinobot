#ifndef _Look_h
#define _Look_h

#include <Arduino.h>
#include "IrSensors.h"
#include "Move.h"

void lookBegin();
boolean lookForObstacle(int obstacle);
int lookAt(int angle);
boolean checkMovement();
void roam();
void avoidEdge();

#endif