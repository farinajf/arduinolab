/**
 * SPIDER 1
 */

#ifndef ARDUINO_AVR_MEGA2560
#error Wrong board. Please choose "Arduino/Genuino Mega or Mega 2560"
#endif

#include "spider.h"

SPIDER::Spider0 _spider;

/**
 * void setup()
 */
void setup() {
  //Serial.begin(9600);

  _spider.init(true);
}

/**
 * void loop()
 */
void loop() {
  _spider.update();
}
