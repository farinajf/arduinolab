#include "globals.h"
#include "pins.h"
#include "l298nEngine.h"

#ifndef ROVER4_H
#define ROVER4_H

namespace ROVER4
{
  class Rover4 {
    private:
      MOTION_MODE_ENUM _motionMode;
      L298NEngine      _rightEngine;
      L298NEngine      _leftEngine;
      
    public:
      Rover4() : _rightEngine(PIN_IN1_D, PIN_IN2_D),
                 _leftEngine (PIN_IN1_I, PIN_IN2_I)
                 {}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _motionMode = START;
      }

      /****************************************************************
       * void drive()
       ****************************************************************/
      void drive() {
        
      }
  };
}

#endif
