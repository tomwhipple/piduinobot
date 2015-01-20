#ifndef _IrSensors_h
#define _IrSensors_h

#include "robotDefines.h"
#include <Arduino.h>

void irSensorBegin();
void irSensorCalibrate(byte sensor);
boolean irSensorDetect(int sensor);
boolean irEdgeDetect(int sensor);

#endif