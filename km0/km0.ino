/**
 * KM0 CAR
 */

#include <Wire.h>
#include "km0car.h"

KM0CAR::KM0CAR  km0car;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  km0car.init();
}

/**
 * void loop()
 */
void loop() {
  km0car.drive();
}
