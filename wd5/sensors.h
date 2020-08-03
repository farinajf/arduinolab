#include "wd5globals.h"
#include "pins.h"
#include "hcsr04sensor.h"
#include "voltage.h"
#include "infrarrojos.h"

#ifndef WD5_SENSORS_H
#define WD5_SENSORS_H

/**
 * 
 */
namespace WD5 {
  class Sensors {
    private:
      Voltage _voltage;
      IR      _ir;

      /****************************************************************
       * boolean _alertColissionForward()
       ****************************************************************/
      boolean _alertColissionForward() const {
        return (HCSR04distance <= DISTANCE_SUPER_MIN) ? true: false;
      }

      /****************************************************************
       * boolean _alertColissionRight()
       ****************************************************************/
      boolean _alertColissionRight() const {
        return (HCSR04distanceRight <= DISTANCE_SUPER_MIN) ? true: false;
      }

      /****************************************************************
       * boolean _alertColissionLeft()
       ****************************************************************/
      boolean _alertColissionLeft() const {
        return (HCSR04distanceLeft <= DISTANCE_SUPER_MIN) ? true: false;
      }

    public:
      Sensors() {}

      double getSensorDistanceRight() const {return (HCSR04distanceRight >= 0) ? HCSR04distanceRight : DISTANCE_MAX;}
      double getSensorDistanceLeft()  const {return (HCSR04distanceLeft  >= 0) ? HCSR04distanceLeft  : DISTANCE_MAX;}
      double getSensorDistance()      const {return (HCSR04distance      >= 0) ? HCSR04distance      : DISTANCE_MAX;}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        ultrasonicInit();
        _voltage.init();
        _ir.init();
      }

      /****************************************************************
       * boolean isBatteryOK()
       ****************************************************************/
      boolean isBatteryOK() const {
        return _voltage.isVoltageHigh();
      }

      /****************************************************************
       * boolean isOK()
       ****************************************************************/
      boolean isOK() const {
        return isForwardOK() && isRightOK() && isLeftOK();
      }

      /****************************************************************
       * boolean alertColission()
       ****************************************************************/
      boolean alertColission() const {
        return _alertColissionForward() || _alertColissionRight() || _alertColissionLeft();
      }

      /****************************************************************
       * boolean isLateralOK()
       ****************************************************************/
      boolean isLateralOK() const {
        return isLateralRightOK() && isLateralLeftOK();
      }
      
      /****************************************************************
       * boolean isForwardOK()
       ****************************************************************/
      boolean isForwardOK() const {
        return (HCSR04distance > DISTANCE_MIN) ? true: false;
      }

      /****************************************************************
       * boolean isRightOK()
       ****************************************************************/
      boolean isRightOK() const {
        return isDistanceRightOK() && isLateralRightOK();
      }

      /****************************************************************
       * boolean isDistanceRightOK()
       ****************************************************************/
      boolean isDistanceRightOK() const {
        return (HCSR04distanceRight > DISTANCE_MIN_LATERAL) ? true: false;
      }
      
      /****************************************************************
       * boolean isLateralRightOK()
       ****************************************************************/
      boolean isLateralRightOK() const {
        return _ir.isRightOK();
      }

      /****************************************************************
       * boolean isLeftOK()
       ****************************************************************/
      boolean isLeftOK() const {
        return isDistanceLeftOK() && isLateralLeftOK();
      }

      /****************************************************************
       * boolean isDistanceLeftOK()
       ****************************************************************/
      boolean isDistanceLeftOK() const {
        return (HCSR04distanceLeft > DISTANCE_MIN_LATERAL) ? true: false;
      }

      /****************************************************************
       * boolean isLateralLeftOK()
       ****************************************************************/
      boolean isLateralLeftOK() const {
        return _ir.isLeftOK();
      }
      
      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        getDistance();

        getDistanceLeft();

        getDistanceRight();

        _voltage.calculate();

        _ir.checkIRObstacle();
      }
  };
}
#endif
