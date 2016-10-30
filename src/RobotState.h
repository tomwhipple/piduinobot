#ifndef _RobotState_H
#define _RobotState_H

#define STATE_BUFFER_SIZE 50

#define VELOCITY_DELTA 5
#define ROTATION_DELTA 20

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int distance;
  unsigned long int count;
  int turn;
  int speed;
} robot_state_t;


void initalizeRobotState(robot_state_t*);

void getRobotStateString(char buffer[], robot_state_t*);

void incrementCount(robot_state_t*);

void parseCharCommand(robot_state_t*, char c);

int getRightMotor(robot_state_t*);
int getLeftMotor(robot_state_t*);

#ifdef __cplusplus
}
#endif

#endif 
