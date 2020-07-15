/**
 * 4WD CAR
 */
#include "sensors.h"
#include "wd5car.h"

WD5::WD5CAR  wd5car;
WD5::Sensors sensors;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  sensors.init();
  wd5car.init();
}

/**
 * void loop()
 */
void loop() {
  //1.- Get information from sensors
  sensors.calculate();
  
  //2.- Get the state of motion of the car
  if (wd5car.setMotionMode(sensors) == STOP) delay(10000);

  //3.- Set the state of the engines
  wd5car.drive();
}
