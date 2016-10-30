#include <Arduino.h>
#include <string.h>

#include "RobotState.h"

void initalizeRobotState(robot_state_t* state) {
  state->distance = 0;
  state->count = 0;
  state->turn = 0;
  state->speed = 0;
}

void getRobotStateString(char buf[], robot_state_t* state) {
  sprintf(buf, "{\"c\":%li, \"dist\":%i, \"turn\":%i, \"speed\":%i},", 
      state->count, 
      state->distance,
      state->turn,
      state->speed);
} 

void incrementCount(robot_state_t* state) {
  state->count++;
}

void parseCharCommand(robot_state_t* state, char c) {
  switch (c) {
    case '+':
      state->speed += VELOCITY_DELTA;
      break;
    case '-':
      state->speed -= VELOCITY_DELTA;
      break;
    case '>':
      state->turn += ROTATION_DELTA;
      break;
    case '<':
      state->turn -= ROTATION_DELTA;
      break;
    case ' ':
      state->speed = 0;
    case '=':
      state->turn = 0;
      break;
  }
}
