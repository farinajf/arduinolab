#include "pins.h"
#include "atom0globals.h"
#include <NewPing.h>

#ifndef ATOM0_ULTRASONIC_H
#define ATOM0_ULTRASONIC_H

NewPing _sonar (PIN_TRIGGER_CENTER, PIN_ECHO_CENTER, DISTANCE_MAX);

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

#endif
