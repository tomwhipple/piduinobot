/**
piduino entry point
**/

#define SERIAL_BAUD 9600
#define LOOP_DELAY 100
#define HW_SETUP_DELAY 50
#define HEAD_CENTER 127

#include <Servo.h>

#include "RobotConfig.h"

#include "RobotState.h"
#include "Ping.h"

robot_state_t robot_state;
char output_buffer[STATE_BUFFER_SIZE];

Servo head_servo;

void setup()
{
  Serial.begin(SERIAL_BAUD);
  while(!Serial);
  initalizeRobotState(&robot_state);

  head_servo.attach(SERVO_PIN);
  delay(HW_SETUP_DELAY);
  head_servo.write(HEAD_CENTER);
}

void loop() {
  incrementCount(&robot_state);

  // read serial to desired state
  
  // read sensors
  robot_state.distance = getEchoDuration();

  // get & write state
  getRobotStateString(output_buffer, &robot_state);
  Serial.println(output_buffer);

  // wait before repeating
  delay(LOOP_DELAY);
}
