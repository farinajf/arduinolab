/**
 * SPIDER 0
 */
#include "sensors.h"

SPIDER::Sensors sensors;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  sensors.init();
}

/**
 * void loop()
 */
void loop() {
  //1.- Get information from sensors
  sensors.calculate();
  
  //2.- Get the state of motion of the car
  delay(1000);
}
