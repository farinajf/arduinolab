/**
 * KM0 CAR
 */
#include "sensors.h"
#include "km0car.h"

KM0CAR::KM0CAR  km0car;
KM0CAR::Sensors sensors;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  sensors.init();
  km0car.init();
}

/**
 * void loop()
 */
void loop() {
  //1.- Get information from sensors
  sensors.calculate();

  //2.- Get the state of motion of the car
  if (km0car.setMotionMode(sensors) == STOP) delay(10000);

  //3.- Set the state of the engines
  km0car.drive();
}
