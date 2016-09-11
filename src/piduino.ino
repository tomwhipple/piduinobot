/**
piduino entry point
**/

#define SERIAL_BAUD 9600
#define LOOP_DELAY 100

#include "RobotState.h"
#include "Ping.h"

robot_state_t robot_state
char* output_buffer[STATE_BUFFER_SIZE];

void setup()
{
  Serial.begin(SERIAL_BAUD);
  while(!Serial);
  intalizeRobotState(&robot_state);
}

void loop() {
  // read serial to desired state
  
  // read sensors
  robot_state.distance = getEchoDuration()

  // get & write state
  getRobotStateString(&output_buffer, &robot_state);
  Serial.println(output_buffer);

  // wait before repeating
  delay(LOOP_DELAY);
}
