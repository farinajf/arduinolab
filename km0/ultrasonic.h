#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "pins.h"
#include "globals.h"
#include <NewPing.h>
#include "servomotor.h"

#define _SERVO_DELAY 15
#define _TIME_MIN    50
#define _PING_NUMBER  3

namespace KM0CAR {
  class Ultrasonic {
    private:
      const int     _LEFT_POSITION         = 180;
      const int     _MIDDLE_LEFT_POSITION  = 135;
      const int     _FORWARD_POSITION      =  90;
      const int     _MIDDLE_RIGHT_POSITION = 45;
      const int     _RIGHT_POSITION        =  0;
      
      ServoMotor    _servo;
      NewPing       _sonar;
      double        _distance = 0;

      /****************************************************************
       * double _calculate(const int position)
       * 
       ****************************************************************/
      double _calculate(const int position) {
        _servo.setPosition(position);
        delay(_SERVO_DELAY);
        
        return _sonar.convert_cm(_sonar.ping_median(_PING_NUMBER));
      }
      
    public:
      Ultrasonic() : _sonar(PIN_TRIGGER, PIN_ECHO, DISTANCE_MAX),
                     _servo(PIN_SERVO)
                     {}

      double getDistanceForward() const {return _distance;}
      
      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _servo.init();
        _servo.setPosition(_FORWARD_POSITION);
      }

      /****************************************************************
       * void init()
       ****************************************************************/
      void calculate() {
        _distance = _calculate(_FORWARD_POSITION);
      }
  };
}

#endif
