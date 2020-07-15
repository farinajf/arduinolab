#include "wd5globals.h"
#include "pins.h"
#include "hcsr04sensor.h"
#include "voltage.h"

#ifndef WD5_SENSORS_H
#define WD5_SENSORS_H

/**
 * 
 */
namespace WD5
{
  class Sensors {
    private:
      Voltage _voltage;

    public:
      Sensors() {}

      double getSensorDistance() const {return HCSR04distance;}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        ultrasonicInit();
        _voltage.init();
      }

      /****************************************************************
       * void isBatteryOK()
       ****************************************************************/
      boolean isBatteryOK() const {
        return _voltage.isVoltageHigh();
      }

      /****************************************************************
       * void isOK()
       ****************************************************************/
      boolean isOK() const {
        return isForwardOK() && isRightOK() && isLeftOK();
      }

      /****************************************************************
       * void isForwardOK()
       ****************************************************************/
      boolean isForwardOK() const {
        return (HCSR04distance > DISTANCE_MIN) ? true: false;
      }

      /****************************************************************
       * void isRightOK()
       ****************************************************************/
      boolean isRightOK() const {
        //TODO
        return true;
      }

      /****************************************************************
       * void isLeftOK()
       ****************************************************************/
      boolean isLeftOK() const {
        //TODO
        return true;
      }


      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        getDistance();

        //getDistanceLeft();

        //getDistanceRight();

        _voltage.calculate();
      }
  };
}
#endif
