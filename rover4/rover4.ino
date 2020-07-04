/**
 * ROVER 4
 */
#include "globals.h"
#include "pins.h"
#include "rover4.h"

ROVER4::Rover4 rover4;

/**
 * void init()
 */
void setup() {
  Serial.begin(9600);

  ultrasonicInit();
  rover4.init();
}

/**
 * void loop()
 */
void loop() {
  rover4.drive();
}
