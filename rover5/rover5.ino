/**
 * ROVER5 CAR
 */
#include "rover5globals.h"
#include "sensors.h"
#include "rover5.h"

ROVER5::Rover5  rover5;
ROVER5::Sensors sensors;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  sensors.init();
  rover5.init();
}

/**
 * void loop()
 */
void loop() {
  //1.- Get information from sensors
  sensors.calculate();
  
  //2.- Get the state of motion of the car
  if (rover5.setMotionMode(sensors) == STOP) delay(10000);

  //3.- Set the state of the engines
  rover5.drive();
}
