#include "Arduino.h"
#include "one_blink.h"

void doOneBlink(){
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
}

