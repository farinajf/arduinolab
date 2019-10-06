/**
 * 4WD CAR
 */
#include "wd4Globals.h"
#include "pinChangeInt.h"
#include "pins.h"
#include "voltage.h"
#include "ultrasonic.h"
#include "wd4car.h"

WD4::Voltage voltage;
WD4::WD4Car  wd4car;

void _printDistance() {
  Serial.print("Distance: "); Serial.print(distance);
  Serial.print("  Distance right: "); Serial.print(distanceRight);
  Serial.print("  Distance left: ");  Serial.print(distanceLeft);
  
  Serial.println(); 
}

/**
 * 
 */
void setup() {
  Serial.begin(9600);

  voltage.init();
  ultrasonicInit();

  wd4car.init();

  wd4car.setForwardSpeed (FORWARD_SPEED);
  wd4car.setBackwardSpeed(BACKWARD_SPEED);
  wd4car.setTurnSpeed    (TURN_SPEED);
}

/**
 * Loop
 */
void loop() {
  //1.- Control del voltaje
  if (voltage.isVoltageLow() == true) wd4car.stopCar();

  //2.- Calculamos las distancias
  getDistance();
  getDistanceLeft();
  getDistanceRight();

  //3.- Mover el coche
  wd4car.drive();

  //4.- Modo evitar obstaculos
  wd4car.obstacleAvoidanceMode(distance, distanceLeft, distanceRight);
}
