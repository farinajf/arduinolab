/**
 * ATOM CAR
 */
#include "sensors.h"
#include "atom0car.h"

ATOM0::ATOM0CAR atom0car;
ATOM0::Sensors  sensors;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  sensors.init();
  atom0car.init();
}

/**
 * void loop()
 */
void loop() {
  //1.- Get information from sensors
  sensors.calculate();
  
  //2.- Get the state of motion of the car
  if (atom0car.setMotionMode(sensors) == STOP) delay(10000);

  //3.- Set the state of the engines
  atom0car.drive();
}
