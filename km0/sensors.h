#ifndef SENSORS_H
#define SENSORS_H

#include "infrarrojos.h"
#include "trackingline.h"
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

      double getSensorDistance()            const {return _sonar.getDistanceForward();}
      double getSensorDistanceMiddleRight() const {return _sonar.getDistanceMiddleRight();}
      double getSensorDistanceMiddleLeft()  const {return _sonar.getDistanceMiddleLeft();}
      double getSensorDistanceRight()       const {return _sonar.getDistanceRight();}
      double getSensorDistanceLeft()        const {return _sonar.getDistanceLeft();}
      
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
        return isForwardOK() && isTrackingLineOK() && _ir.isRightOK() && _ir.isLeftOK();
      }

      /****************************************************************
       * boolean isLateralOK()
       ****************************************************************/
      boolean isLateralOK() const {
        return isLateralRightOK() && isLateralLeftOK();
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
       * boolean isLateralRightOK()
       ****************************************************************/
      boolean isLateralRightOK() const {
        return isDistanceLateralRightOK();
      }

      /****************************************************************
       * boolean isLateralOK()
       ****************************************************************/
      boolean isLateralLeftOK() const {
        return isDistanceLateralLeftOK();
      }

      /****************************************************************
       * boolean isDistanceLateralRightOK()
       ****************************************************************/
      boolean isDistanceLateralRightOK() const {
        return (_sonar.getDistanceMiddleRight() > DISTANCE_MIN_LATERAL) && (_sonar.getDistanceRight() > DISTANCE_MIN_LATERAL);
      }

      /****************************************************************
       * boolean isDistanceLateralLeftOK()
       ****************************************************************/
      boolean isDistanceLateralLeftOK() const {
        return (_sonar.getDistanceMiddleLeft() > DISTANCE_MIN_LATERAL) && (_sonar.getDistanceLeft() > DISTANCE_MIN_LATERAL);
      }

      /****************************************************************
       * boolean isTrackingLineOK()
       ****************************************************************/
      boolean isTrackingLineOK() const {
        return _tl.isRightOK() && _tl.isLeftOK();
      }

      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() const {
        _sonar.calculate();
        
        _ir.checkIRObstacle();
        _tl.checkLine();
      }

      /****************************************************************
       * void calculateLateral()
       ****************************************************************/
      void calculateLateral() const {
        _sonar.calculateRight();
        _sonar.calculateLeft();
      }
  };
}
#endif
