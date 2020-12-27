#include "globals.h"
#include "sensors.h"

namespace KM0CAR {

  /****************************************************************
   * void init()
   ****************************************************************/
  void Sensors::init() {
    _sonar.init();
    _ir.init();
    _tl.init();
  }

  /****************************************************************
   * void checkIRObstacle()
   ****************************************************************/
  void Sensors::checkIRObstacle() {
    _ir.checkIRObstacle();
    _tl.checkIRObstacle();
  }

  /****************************************************************
   * void forwardDistance()
   ****************************************************************/
  void Sensors::forwardDistance() {
    _sonar.calculate();
  }

  /****************************************************************
   * void lateralDistance()
   ****************************************************************/
  void Sensors::lateralDistance() {
    _sonar.calculateRight();
    _sonar.calculateLeft();
  }

  /****************************************************************
   * bool isAlertColission() const
   ****************************************************************/
  bool Sensors::isAlertColission() const {
    return (_sonar.getDistanceForward() <= DISTANCE_SUPER_MIN) ? true: false;
  }

  /****************************************************************
   * bool isLateralOK() const
   ****************************************************************/
  bool Sensors::isLateralOK() const {
    return isDistanceRightOK() && isDistanceLeftOK() && isIRLeftOK() && isIRLeftOK();
  }

  /****************************************************************
   * bool isIROK() const
   ****************************************************************/
  bool Sensors::isIROK() const {
    return _ir.isRightOK() && _ir.isLeftOK() && _tl.isRightOK() && _tl.isLeftOK();
  }

  /****************************************************************
   * bool isIRRightOK() const
   ****************************************************************/
  bool Sensors::isIRRightOK() const {
    return _tl.isRightOK();
  }

  /****************************************************************
   * bool isIRLeftOK() const
   ****************************************************************/
  bool Sensors::isIRLeftOK() const {
    return _tl.isLeftOK();
  }

  /****************************************************************
   * bool isDistanceForwardOK() const
   ****************************************************************/
  bool Sensors::isDistanceForwardOK() const {
    return (_sonar.getDistanceForward() > DISTANCE_MIN) ? true: false;
  }

  /****************************************************************
   * bool isDistanceRightOK() const
   ****************************************************************/
  bool Sensors::isDistanceRightOK() const {
    return (_sonar.getDistanceMiddleRight() > DISTANCE_MIN_LATERAL) && (_sonar.getDistanceRight() > DISTANCE_MIN_LATERAL);
  }

  /****************************************************************
   * bool isDistanceLeftOK() const
   ****************************************************************/
  bool Sensors::isDistanceLeftOK() const {
    return (_sonar.getDistanceMiddleLeft() > DISTANCE_MIN_LATERAL) && (_sonar.getDistanceLeft() > DISTANCE_MIN_LATERAL);
  }
}
