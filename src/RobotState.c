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
  state->head = HEAD_CENTER;
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
      // fall through & set turn
    case '=':
      state->turn = 0;
      break;
    case 'r':
      state->head--;
      break;
    case 'l':
      state->head++; 
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

int limit_speed(int speed_in) {
  if (speed_in > 0) {
    return min(MAX_SPEED,max(MIN_SPEED,speed_in));
  }
  else if (speed_in < 0) {
    return min(-MIN_SPEED,max(-MAX_SPEED,speed_in));
  }
  else {
    return 0;
  }
}

void updateMotorState(robot_state_t* state) {
  state->speed = limit_speed(state->speed);

  int cmd_right_motor = min(MAX_SPEED, state->speed - state->turn);
  int cmd_left_motor = min(MAX_SPEED, state->speed + state->turn);

  setMotorRotation(MOTOR_RIGHT, cmd_right_motor);
  setMotorRotation(MOTOR_LEFT, cmd_left_motor);
} 
