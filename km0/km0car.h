#ifndef KM0CAR_H
#define KM0CAR_H

#include "pins.h"
#include "globals.h"
#include "l298nEngine.h"
#include "bocina.h"
#include "luces.h"
#include "sensors.h"

namespace KM0CAR {
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
    TURN_RIGHT,
    FLIP_LEFT,
    FLIP_RIGHT
  };

  /**
   * TODO
   */
  class KM0CAR {
    private:
      MotionModeEnum _motionMode;
      L298NEngine    _rightEngine;
      L298NEngine    _leftEngine;
      Sensors        _sensors;
      Bocina         _bocina;
      Luces          _luces;
      bool           _alert           = false;
      int            _forwardSpeed    = FORWARD_SPEED_FAST; //velocidad es 100x(_velocidad/255)%
      int            _backwardSpeed   = BACKWARD_SPEED;
      int            _turnSpeed       = TURN_SPEED;
      int            _turnsCounter    = 0;
      int            _backwardCounter = 0;

      bool _isStopped() const {return _motionMode == STOP;}
      void _setAlert (bool x) {_alert = x;}

      void           _forward()   const;
      void           _backward()  const;
      void           _turnRight() const;
      void           _turnLeft()  const;
      void           _flipRight() const;
      void           _flipLeft()  const;
      void           _stopCar()   const;
      void           _setSpeed();
      void           _setMotionMode();
      MotionModeEnum _setMotionModeInAlert();
      MotionModeEnum _setMotionModeLateral();

    public:
      KM0CAR() : _rightEngine(PIN_EN_D, PIN_IN1_D, PIN_IN2_D),
                 _leftEngine (PIN_EN_I, PIN_IN1_I, PIN_IN2_I)
                 {}

      void init();
      void drive();
  };
}

#endif
