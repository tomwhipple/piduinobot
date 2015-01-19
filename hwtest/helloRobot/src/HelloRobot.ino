/****************************************************
HelloRobot.ino: Initial Robot test sketch

Michael Margolis 4 July 2012
*****************************************************/
// include motor libraries
#include <AFMotor.h>     // adafruit motor shield library
#include <RobotMotor.h>  // 2wd or 4wd motor library

/***** Global Defines ****/ 
// defines to identify sensors
const int SENSE_IR_LEFT   = 0;
const int SENSE_IR_RIGHT  = 1;
const int SENSE_IR_CENTER = 2;

// defines for directions
const int DIR_LEFT   = 0;
const int DIR_RIGHT  = 1;
const int DIR_CENTER = 2;  

const char* locationString[] = {"Left", "Right",   "Center"}; // Debug labels
// http://arduino.cc/en/Reference/String for more on character string arrays

// obstacles constants 
const int OBST_NONE       = 0;  // no obstacle detected
const int OBST_LEFT_EDGE  = 1;  // left edge detected 
const int OBST_RIGHT_EDGE = 2;  // right edge detected
const int OBST_FRONT_EDGE = 3;  // edge detect at both left and right sensors

const int LED_PIN = 13;
/**** End of Global Defines ****************/

// Setup runs at startup and is used configure pins and init system variables
void setup()
{
  Serial.begin(9600); 
  blinkNumber(8); // open port while flashing. Needed for Leonardo only 
  
  motorBegin(MOTOR_LEFT); 
  motorBegin(MOTOR_RIGHT); 
 
  irSensorBegin();    // initialize sensors 
  pinMode(LED_PIN, OUTPUT); // enable the LED pin for output

  Serial.println("Waiting for a sensor to detect blocked reflection");
}

void loop()
{
   // call a function when reflection blocked on left side
   if(lookForObstacle(OBST_LEFT_EDGE) == true)   {   
     calibrateRotationRate(DIR_LEFT,360);  // calibrate CCW rotation
   }
   // as above for right sensor
   if(lookForObstacle(OBST_RIGHT_EDGE) == true)   {   
     calibrateRotationRate(DIR_RIGHT, 360);  // calibrate CW rotation
   }  
}

// function to indicate numbers by flashing the built-in LED
void blinkNumber( byte number) {
   pinMode(LED_PIN, OUTPUT); // enable the LED pin for output
   while(number--) {
     digitalWrite(LED_PIN, HIGH); delay(100);
     digitalWrite(LED_PIN, LOW);  delay(400);
   }
}

/**********************
 code to look for obstacles
**********************/

// returns true if the given obstacle is detected
boolean lookForObstacle(int obstacle)
{
  switch(obstacle) {
     case  OBST_FRONT_EDGE: return irEdgeDetect(DIR_LEFT) || irEdgeDetect(DIR_RIGHT);
     case  OBST_LEFT_EDGE:  return irEdgeDetect(DIR_LEFT); 
     case  OBST_RIGHT_EDGE: return irEdgeDetect(DIR_RIGHT);      
  }
  return false; 
}

/*************************************
 functions to rotate the robot
*************************************/
  
// return the time in milliseconds to turn the given angle at the given speed
long rotationAngleToTime( int angle, int speed)
{
int fullRotationTime; // time to rotate 360 degrees at given speed

  if(speed < MIN_SPEED)
    return 0; // ignore speeds slower then the first table entry
  
  angle = abs(angle);
  
  if(speed >= 100)
    fullRotationTime = rotationTime[NBR_SPEEDS-1]; // the last entry is 100%
  else
  { 
    int index = (speed - MIN_SPEED) / SPEED_TABLE_INTERVAL; // index into speed
                                                            // and time tables
    int t0 =  rotationTime[index];
    int t1 = rotationTime[index+1];    // time of the next higher speed 
    fullRotationTime = map(speed,  
                           speedTable[index],  
                           speedTable[index+1], t0, t1);
    // Serial.print("index= ");  Serial.print(index); Serial.print(", t0 = ");  
    // Serial.print(t0);  Serial.print(", t1 = ");  Serial.print(t1); 
  }
  // Serial.print(" full rotation time = ");  Serial.println(fullRotationTime);
  long result = map(angle, 0,360, 0, fullRotationTime);
  return result; 
}

// rotate the robot from MIN_SPEED to 100% increasing by SPEED_TABLE_INTERVAL
void calibrateRotationRate(int sensor, int angle)
{  
  Serial.print(locationString[sensor]);
  Serial.println(" calibration" );
  for(int speed = MIN_SPEED; speed <= 100; speed += SPEED_TABLE_INTERVAL)
  {   

    delay(1000);
    blinkNumber(speed/10);   
 
    if( sensor == DIR_LEFT)
    {    // rotate left
      motorReverse(MOTOR_LEFT,  speed); 
      motorForward(MOTOR_RIGHT, speed);  
    }
    else if( sensor == DIR_RIGHT)
    {    // rotate right
      motorForward(MOTOR_LEFT,  speed);
      motorReverse(MOTOR_RIGHT, speed);
    }
    else
       Serial.println("Invalid sensor");     
    
    int time = rotationAngleToTime(angle, speed);

    Serial.print(locationString[sensor]); Serial.print(": rotate ");
    Serial.print(angle); Serial.print(" degrees at speed "); Serial.print(speed);
    Serial.print(" for "); Serial.print(time); Serial.println("ms");
    
    delay(time); 
    motorStop(MOTOR_LEFT);
    motorStop(MOTOR_RIGHT);  
    delay(2000); // two second delay between speeds
  }    
}

/****************************
   ir reflectance sensor code   
****************************/

const byte NBR_SENSORS = 3;  // this version only has left and right sensors
const byte IR_SENSOR[NBR_SENSORS] = {0, 1, 2}; // analog pins for sensors

int irSensorAmbient[NBR_SENSORS]; // sensor value with no reflection
int irSensorReflect[NBR_SENSORS]; // value considered detecting an object
int irSensorEdge[NBR_SENSORS];    // value considered detecting an edge
boolean isDetected[NBR_SENSORS] = {false,false}; // set true if object detected

const int irReflectThreshold = 10; // % level below ambient to trigger reflection
const int irEdgeThreshold    = 90; // % level above ambient to trigger edge

void irSensorBegin()
{
  for(int sensor = 0; sensor < NBR_SENSORS; sensor++)
     irSensorCalibrate(sensor);
}

// calibrate thresholds for ambient light 
void irSensorCalibrate(byte sensor)
{
  int ambient = analogRead(IR_SENSOR[sensor]); // get ambient level
  irSensorAmbient[sensor] = ambient; 
  // precalculate the levels for object and edge detection  
  irSensorReflect[sensor] = (ambient * (long)(100-irReflectThreshold)) / 100;
  irSensorEdge[sensor]    = (ambient * (long)(100+irEdgeThreshold)) / 100; 
}

// returns true if an object reflection detected on the given sensor
// the sensor parameter is the index into the sensor array
boolean irSensorDetect(int sensor)
{
  boolean result = false; // default value
  int value = analogRead(IR_SENSOR[sensor]); // get IR light level
  if( value <= irSensorReflect[sensor]) {
    result = true; // object detected (lower value means more reflection)
    if( isDetected[sensor] == false) { // only print on initial detection
      Serial.print(locationString[sensor]);         
      Serial.println(" object detected");
    }
  }
  isDetected[sensor] = result;  
  return result;
}

boolean irEdgeDetect(int sensor)
{
  boolean result = false; // default value
  int value = analogRead(IR_SENSOR[sensor]); // get IR light level
  if( value >= irSensorEdge[sensor]) {
    result = true; // edge detected (higher value means less reflection)
    if( isDetected[sensor] == false) { // only print on initial detection
      Serial.print(locationString[sensor]);         
      Serial.println(" edge detected");
     }
  }
  isDetected[sensor] = result; 
  return result;
}