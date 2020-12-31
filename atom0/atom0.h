#ifndef ATOM0CAR_H
#define ATOM0CAR_H

#include "globals.h"
#include "l298nEngine.h"
#include "sensors.h"

namespace ATOM0 {
  /**
   * 
   */
  enum MotionModeEnum {
    START,
    STOP,
    ALERT,
    FORWARD,
    BACKWARD,
    TURN_LEFT,
    TURN_RIGHT
  };

  /**
   * 
   */
  class ATOM0 {
    private:
      unsigned long  _printPrevTime   = 0;
      MotionModeEnum _motionMode;
      L298NEngine    _rightEngine;
      L298NEngine    _leftEngine;
      Sensors        _sensors;
      bool           _alert           = false;
      int            _forwardSpeed    = FORWARD_SPEED_FAST; //velocidad es 100x(_velocidad/255)%
      int            _backwardSpeed   = BACKWARD_SPEED;
      int            _turnSpeed       = TURN_SPEED;
      int            _turnsCounter    = 0;
      int            _backwardCounter = 0;

      bool _isStopped() const {return _motionMode == STOP;}

      String         _motionMode2char() const;
      void           _setAlert(const bool x);
      void           _forward()         const;
      void           _backward()        const;
      void           _turnRight()       const;
      void           _turnLeft()        const;
      void           _stopCar()         const;
      void           _setSpeed();
      MotionModeEnum _setMotionMode();
      MotionModeEnum _setMotionModeInAlert();
      MotionModeEnum _setMotionModeLateral();

    public:
      ATOM0() : _rightEngine(PIN_EN_D, PIN_IN1_D, PIN_IN2_D),
                   _leftEngine (PIN_EN_I, PIN_IN1_I, PIN_IN2_I)
                   {}

      void init();
      void drive();
  };
}

#endif
