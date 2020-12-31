#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "globals.h"

namespace ATOM0 {
  
  extern volatile unsigned long _measurePrevTime;
  extern volatile char          _measureFlag;
  extern volatile double        HCSR04distance;
  extern unsigned long          _distancePrevTime;

  void _measureDistance();
  void ultrasonicInit();
  void ultrasonicCalculate();
}

#endif
