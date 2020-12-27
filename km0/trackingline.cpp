#include "trackingline.h"

namespace KM0CAR {
  /****************************************************************
   * void init()
   ****************************************************************/
  void TrakingLine::init() {
    pinMode(_pinRight, INPUT);
    pinMode(_pinLeft,  INPUT);
  }

  /****************************************************************
   * void checkIRObstacle()
   ****************************************************************/
  void TrakingLine::checkIRObstacle() {
    //1.- Right
    if (millis() - _checkRightPrevTime > 50)
    {
      _rightOK = (digitalRead(_pinRight) == HIGH) ? true : false;

      _checkRightPrevTime = millis();
    }

    //2.- Left
    if (millis() - _checkLeftPrevTime > 50)
    {
      _leftOK = (digitalRead(_pinLeft) == HIGH) ? true : false;

      _checkLeftPrevTime = millis();
    }
  }
}
