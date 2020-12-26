/**
 * SPIDER 0
 */
#include "Spider.h"
#include "sensors.h"

SPIDER::Spider0 _spider;
SPIDER::Sensors _sensors;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  _sensors.init();
  _spider.init();
}

/**
 * void loop()
 */
void loop() {
  //1.- Get information from sensors
  _sensors.calculate();

  //2.- Check battery
  if (_sensors.isBatteryOK() == true) _spider.drive();
  else delay(10000);

  //3.- End
  delay(200);
}
