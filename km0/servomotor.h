#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <ServoTimer2.h>

namespace KM0CAR {
  class ServoMotor {
    private:
      ServoTimer2 _servo;
      int         _pin;

    public:
      ServoMotor(const int pin) :
        _pin(pin)
        {}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _servo.attach(_pin);
      }

      /****************************************************************
       * void setPosition(const float x)
       * 
       * x: posicion en angulos º, entre 0º  180º
       ****************************************************************/
      void setPosition(const float x) const {
        float y = 750.0 + (x/180.0)*1500.0;
        
        if      (y <= 750)  _servo.write( 750);
        else if (y >= 2250) _servo.write(2250);
        else                _servo.write(y);
      }
  };
}

#endif
