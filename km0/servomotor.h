#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Arduino.h>
#include <ServoTimer2.h>

namespace KM0CAR {
  class ServoMotor {
    private:
      const int   _SERVO_DELAY = 200;
      const int   _pin;
      
      ServoTimer2 _servo;
      int         _position = -1;

    public:
      ServoMotor(const int pin) : _pin(pin)
                                  {}

      void init();
      void setPosition(const int x);
  };
}

#endif
