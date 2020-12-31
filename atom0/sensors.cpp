#include "sensors.h"

namespace ATOM0 {

  /****************************************************************
   * void init()
   ****************************************************************/
  void Sensors::init() {
    ultrasonicInit();
    _ir.init();
  }

  /****************************************************************
   * void checkIRObstacle()
   ****************************************************************/
  void Sensors::checkIRObstacle() {
    _ir.checkIRObstacle();
  }

  /****************************************************************
   * double getDistance() const
   ****************************************************************/
  double Sensors::getDistance() const {return HCSR04distance;}

  /****************************************************************
   * bool isAlertColission() const
   ****************************************************************/
  bool Sensors::isAlertColission() const {
    return (HCSR04distance <= DISTANCE_SUPER_MIN) ? true: false;
  }

  /****************************************************************
   * bool isDistanceOK() const
   ****************************************************************/
  bool Sensors::isDistanceOK() const {
    return (HCSR04distance > DISTANCE_MIN) ? true: false;
  }

  /****************************************************************
   * bool isIRRightOK() const
   ****************************************************************/
  bool Sensors::isIRRightOK() const {
    return _ir.isRightOK();
  }

  /****************************************************************
   * bool isIRLeftOK() const
   ****************************************************************/
  bool Sensors::isIRLeftOK() const {
    return _ir.isLeftOK();
  }

  /****************************************************************
   * bool isIROK() const
   ****************************************************************/
  bool Sensors::isIROK() const {
    return _ir.isRightOK() && _ir.isLeftOK();
  }
}
