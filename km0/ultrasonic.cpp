#include "pins.h"
#include "globals.h"
#include "ultrasonic.h"

namespace KM0CAR {
  /****************************************************************
   * double _calculate(const int position) const
   * 
   ****************************************************************/
  double Ultrasonic::_calculate(const int position) const {
    _servo.setPosition(position);
        
    return _sonar.convert_cm(_sonar.ping_median(_PING_NUMBER));
  }

  /****************************************************************
   * Ultrasonic()
   ****************************************************************/
  Ultrasonic::Ultrasonic() : _sonar(PIN_TRIGGER, PIN_ECHO, DISTANCE_MAX),
                             _servo(PIN_SERVO)
                             {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void Ultrasonic::init() {
    _servo.init();
    _servo.setPosition(_FORWARD_POSITION);
  }

  /****************************************************************
   * void calculate()
   ****************************************************************/
  void Ultrasonic::calculate() {
    _distance = _calculate(_FORWARD_POSITION);
  }

  /****************************************************************
   * void calculateRight()
   ****************************************************************/
  void Ultrasonic::calculateRight() {
    _distanceMiddleRight = _calculate(_MIDDLE_RIGHT_POSITION);
    _distanceRight       = _calculate(_RIGHT_POSITION);
  }

  /****************************************************************
   * void calculateLeft()
   ****************************************************************/
  void Ultrasonic::calculateLeft() {
    _distanceMiddleLeft = _calculate(_MIDDLE_LEFT_POSITION);
    _distanceLeft       = _calculate(_LEFT_POSITION);
  }
}
