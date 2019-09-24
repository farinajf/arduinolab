#include "tankGlobals.h"
#include "pinChangeInt.h"
#include "tankDriver.h"
#include "tankLeds.h"
#include "ultrasonic.h"

TANK02::TankDriver td;
TANK02::TankLeds   leds;

/****************************************************************
 * 
 ****************************************************************/
void setup() {
  Serial.begin(9600);

  leds.init();

  ultrasonicInit();
  td.init();

  td.setForwardSpeed (_FORWARD_SPEED);
  td.setBackwardSpeed(_BACKWARD_SPEED);
  td.setTurnSpeed    (_TURN_SPEED);
}

/****************************************************************
 * 
 ****************************************************************/
void loop() {
  getDistance();
  
  td.drive();
  td.obstacleAvoidanceMode(distance, leds, isObstacleLeft, isObstacleRight);

  checkObstacle();
}
