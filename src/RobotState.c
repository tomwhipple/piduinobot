#include <Arduino.h>
#include <string.h>

#include "RobotState.h"

void initalizeRobotState(robot_state_t* state) {
  state->distance = 0;
  state->count = 0;
}

void getRobotStateString(char buf[], robot_state_t* state) {
  sprintf(buf, "{\"c\":%li, \"dist\":%i},", state->count, state->distance);
} 

void incrementCount(robot_state_t* state) {
  state->count++;
}
