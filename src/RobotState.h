#ifndef _RobotState_H
#define _RobotState_H

#define VELOCITY_DELTA 5
#define ROTATION_DELTA 10
#define MAX_SPEED 100


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
unsigned long count;
  long distance;
  int turn;
  int speed;
  int head;
  char cmd_pending;
} robot_state_t;


void initalizeRobotState(robot_state_t*);

void initializeMotors();

void getRobotStateString(char buffer[], robot_state_t*);

void incrementCount(robot_state_t*);

void parseCharCommand(robot_state_t*, char c);

void updateMotorState(robot_state_t*);

#ifdef __cplusplus
}
#endif

#endif 
