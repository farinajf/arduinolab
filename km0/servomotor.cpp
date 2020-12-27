#include "servomotor.h"

namespace KM0CAR {
  /****************************************************************
   * void init()
   ****************************************************************/
  void ServoMotor::init() {
    _servo.attach(_pin);
  }

  /****************************************************************
   * void setPosition(const int x)
   * 
   * x: posicion en angulos º, entre 0º  180º
   * 
   ****************************************************************/
  void ServoMotor::setPosition(const int x) {
    //1.- Se calcula la nueva posicion
    float y = 750.0 + (((float) x) / 180.0)*1500.0;

    if      (y <= 750)  _servo.write( 750);
    else if (y >= 2250) _servo.write(2250);
    else                _servo.write(y);

    //2.- Si la posicion es distinta a la actual, esperamos
    if (x != _position) delay(_SERVO_DELAY);

    //3.- Actualizamos posicion
    _position = x;
  }
}
