/**
 * 4WD CAR
 */
#include "wd4Globals.h"
#include "pinChangeInt.h"
#include "pins.h"
#include "voltage.h"
#include "ultrasonic.h"

WD4::Voltage voltage;

/**
 * 
 */
void setup() {
  Serial.begin(9600);

  voltage.init();
  ultrasonicInit();
}

/**
 * Loop
 */
void loop() {
  voltage.isVoltageLow();

  getDistance();
  getDistanceLeft();
  getDistanceRight();

  delay(200);

  Serial.print("Distance: "); Serial.print(distance); Serial.print("   Distance right: "); Serial.print(distanceRight); Serial.print("   Distance left: "); Serial.print(distanceLeft);
  Serial.println(); 
}
