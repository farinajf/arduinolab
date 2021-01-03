/**
 * SPIDER 0
 */
#include "Spider.h"

SPIDER::Spider0 _spider;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  _spider.init();
}

/**
 * void loop()
 */
void loop() {
  _spider.drive();
}
