#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <NewPing.h>
#include "servomotor.h"

namespace KM0CAR {
  class Ultrasonic {
    private:
      const int  _LEFT_POSITION         = 180;
      const int  _MIDDLE_LEFT_POSITION  = 135;
      const int  _FORWARD_POSITION      =  90;
      const int  _MIDDLE_RIGHT_POSITION =  45;
      const int  _RIGHT_POSITION        =  0;
      const int  _PING_NUMBER           =  3;
      
      ServoMotor _servo;
      NewPing    _sonar;
      double     _distance            = 0;
      double     _distanceMiddleRight = 0;
      double     _distanceMiddleLeft  = 0;
      double     _distanceRight       = 0;
      double     _distanceLeft        = 0;

      double _calculate(const int position) const;

    public:
      Ultrasonic();

      double getDistanceForward()     const {return _distance;}
      double getDistanceMiddleRight() const {return _distanceMiddleRight;}
      double getDistanceRight()       const {return _distanceRight;}
      double getDistanceMiddleLeft()  const {return _distanceMiddleLeft;}
      double getDistanceLeft()        const {return _distanceLeft;}

      void init();
      void calculate();
      void calculateRight();
      void calculateLeft();
  };
}

#endif
