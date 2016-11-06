#include <Arduino.h>
#include <string.h>
#include <RobotMotor.h>
#include <limits.h>

#include "numeric.h"
#include "RobotState.h"

void initalizeRobotState(robot_state_t* state) {
  state->count = 0;
  state->distance = 0;
  state->turn = 0;
  state->speed = 0;
  state->head = 80;
  state->cmd_pending = 1;
}

void initializeMotors() {
  motorBegin(MOTOR_RIGHT);
  motorBegin(MOTOR_LEFT);
}

void getRobotStateString(char buf[], robot_state_t* state) {
  sprintf(buf, "{\"c\":%lu, \"dist\":%li, \"head\":%i, \"turn\":%i, \"speed\":%i},", 
      state->count, 
      state->distance,
      state->head,
      state->turn,
      state->speed);
} 

void incrementCount(robot_state_t* state) {
  state->count++;
  //if (state->count == ULONG_MAX) state->count = 0;
}

void parseCharCommand(robot_state_t* state, char c) {
  state->cmd_pending = 1; 
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
    case 'r':
      state->head++;
      break;
    case 'l':
      state->head--; 
      break;
    default:
      state->cmd_pending = 0;
  }
}

void setMotorRotation(int motor, int speed) {
  if (speed > 0) {
    motorForward(motor, speed);
  }
  else if (speed < 0) {
    motorReverse(motor, -speed);
  }
  else {
    motorStop(motor);
  } 
}

void updateMotorState(robot_state_t* state) {
  int cmd_right_motor = max(MAX_SPEED, state->speed - state->turn);
  int cmd_left_motor = max(MAX_SPEED, state->speed + state->turn);

  setMotorRotation(MOTOR_RIGHT, cmd_right_motor);
  setMotorRotation(MOTOR_LEFT, cmd_left_motor);
} 
