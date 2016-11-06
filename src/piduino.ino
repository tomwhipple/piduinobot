/**
piduino entry point
**/

#include <Arduino.h>

#define LOOP_DELAY 100
#define HW_SETUP_DELAY 50
#define HEAD_CENTER 127
#define STATE_BUFFER_SIZE 200
#
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
  initializeMotors();

  head_servo.attach(SERVO_PIN);
  delay(HW_SETUP_DELAY);
}

void loop() {
  incrementCount(&robot_state);

  // read serial to desired state
  if (Serial.available()) {
    char input = (char)Serial.read();
    parseCharCommand(&robot_state, input);
  }
  
  // read sensors
  robot_state.distance = getEchoDuration();

  // get & write state
  if (robot_state.cmd_pending) {
    updateMotorState(&robot_state);
    head_servo.write(robot_state.head);
    robot_state.cmd_pending = 0;
  }

  // respond with current events
  getRobotStateString(output_buffer, &robot_state);
  Serial.println(output_buffer);

  // wait before repeating
  delay(LOOP_DELAY);
}
