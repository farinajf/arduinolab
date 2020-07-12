#include "rover5globals.h"
#include "pins.h"
#include <NewPing.h>

#ifndef ROVER5_ULTRASONIC_H
#define ROVER5_ULTRASONIC_H

NewPing _sonarRight(PIN_TRIGGER_RIGHT,  PIN_ECHO_RIGHT,  DISTANCE_MAX);
NewPing _sonarLeft (PIN_TRIGGER_LEFT,   PIN_ECHO_LEFT,   DISTANCE_MAX);
NewPing _sonar     (PIN_TRIGGER_CENTER, PIN_ECHO_CENTER, DISTANCE_MAX);

////////////////////////////////////////////////////////////////////
//Private
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Public
////////////////////////////////////////////////////////////////////
/**
 * void ultrasonicInit()
 */
void ultrasonicInit() {}

/**
 * void getDistance()
 * 
 * Calcula la distancia a la izquierda.
 * 
 */
double getDistanceFront() {
  double result = _sonar.convert_cm(_sonar.ping_median(3));
  
  return (result > 0) ? result : DISTANCE_MAX;
}

/**
 * void getDistanceRight()
 * 
 * Calcula la distancia a la derecha.
 * 
 */
double getDistanceRight() {
  double result = _sonarRight.convert_cm(_sonarRight.ping_median(3));
  
  return (result > 0) ? result : DISTANCE_MAX;
}

/**
 * void getDistanceLeft()
 * 
 * Calcula la distancia al frente.
 * 
 */
double getDistanceLeft() {
  double result = _sonarLeft.convert_cm(_sonarLeft.ping_median(3));
  
  return (result > 0) ? result : DISTANCE_MAX;
}


#endif
