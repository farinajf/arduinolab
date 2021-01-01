#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "globals.h"

namespace ATOM0 {
  
  extern volatile double HCSR04distance;

  void ultrasonicInit();
  void ultrasonicCalculate();
}

#endif
