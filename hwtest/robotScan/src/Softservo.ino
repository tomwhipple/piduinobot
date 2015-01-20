/*******************************
 Softservo.ino
 software servo control without using timers
 note that these functions block until complete
*******************************/ 

int servoPin;

void softServoAttach(int pin)
{
   servoPin = pin;
   pinMode(pin, OUTPUT); 
}

// writes given angle to servo for given delay in milliseconds
void softServoWrite(int angle, long servoDelay)
{
  int pulsewidth = map(angle, 0, 180, 544, 2400); // width in microseconds
  do {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servoPin, LOW);
    delay(20); // wait for 20 milliseconds
    servoDelay -= 20; 
  } while(servoDelay >=0);
}
