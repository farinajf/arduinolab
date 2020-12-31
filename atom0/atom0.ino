/**
 * ATOM CAR
 */
#include <Wire.h>
#include "atom0.h"

ATOM0::ATOM0 atom0;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  atom0.init();
}

/**
 * void loop()
 */
void loop() {
  atom0.drive();
}
