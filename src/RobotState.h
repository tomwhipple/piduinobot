#ifndef _RobotState_H
#define _RobotState_H

#ifdef __cplusplus
extern "C" {
#endif

#define STATE_BUFFER_SIZE 50

typedef struct {
  int distance;
} robot_state_t;


void initalizeRobotState(robot_state_t*);

void getRobotStateString(char**, robot_state_t*);

#ifdef __cplusplus
}
#endif

#endif 
