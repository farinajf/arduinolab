#ifndef SENSORS_H
#define SENSORS_H

#include "infrarrojos.h"
#include "ultrasonic.h"

/**
 * Sensors: HC-SR04 + Infrarrojos
 */
namespace KM0CAR {
  class Sensors {
    private:
      TrakingLine _tl;
      Ultrasonic  _sonar;
      IR          _ir;

      /****************************************************************
       * boolean _alertColissionForward()
       ****************************************************************/
      boolean _alertColissionForward() const {
        return (_sonar.getDistanceForward() <= DISTANCE_SUPER_MIN) ? true: false;
      }

    public:
      Sensors() {}

      double getSensorDistance() const {return _sonar.getDistanceForward();}
      
      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _sonar.init();
        _ir.init();
        _tl.init();
      }

      /****************************************************************
       * boolean isOK()
       ****************************************************************/
      boolean isOK() const {
        return isForwardOK() && _ir.isRightOK() && _ir.isLeftOK() && _tl.isRightOK() && _tl.isLeftOK();
      }

      /****************************************************************
       * boolean alertColission()
       ****************************************************************/
      boolean alertColission() const {
        return _alertColissionForward();
      }

      /****************************************************************
       * boolean isForwardOK()
       ****************************************************************/
      boolean isForwardOK() const {
        return (_sonar.getDistanceForward() > DISTANCE_MIN) ? true: false;
      }

      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() const {
        _sonar.calculate();
        
        _ir.checkIRObstacle();
        _tl.checkLine();
      }
  };
}
#endif
