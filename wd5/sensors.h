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

      double getSensorDistanceRight() const {return (HCSR04distanceRight > 0) ? HCSR04distanceRight : DISTANCE_MAX;}
      double getSensorDistanceLeft()  const {return (HCSR04distanceLeft  > 0) ? HCSR04distanceLeft  : DISTANCE_MAX;}
      double getSensorDistance()      const {return (HCSR04distance      > 0) ? HCSR04distance      : DISTANCE_MAX;}

      /****************************************************************
       * AlertSensorEnum getAlertSensor()
       ****************************************************************/
      AlertSensorEnum getAlertSensor() {
        return (getSensorDistance() <= getSensorDistanceRight()) ?
                  (getSensorDistance() <= getSensorDistanceLeft()) ? SENSOR_FORWARD : SENSOR_LEFT
                      : (getSensorDistanceRight() <= getSensorDistanceLeft()) ? SENSOR_RIGHT : SENSOR_LEFT;
      }

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
        return (HCSR04distanceRight > DISTANCE_MIN_LATERAL) ? true: false;
      }

      /****************************************************************
       * void isLeftOK()
       ****************************************************************/
      boolean isLeftOK() const {
        return (HCSR04distanceLeft > DISTANCE_MIN_LATERAL) ? true: false;
      }

      /****************************************************************
       * void alertColission()
       ****************************************************************/
      boolean alertColission() const {
        return alertColissionForward() || alertColissionRight() || alertColissionLeft();
      }

      /****************************************************************
       * void alertColissionForward()
       ****************************************************************/
      boolean alertColissionForward() const {
        return (HCSR04distance <= DISTANCE_SUPER_MIN) ? true: false;
      }

      /****************************************************************
       * void alertColissionRight()
       ****************************************************************/
      boolean alertColissionRight() const {
        return (HCSR04distanceRight <= DISTANCE_SUPER_MIN) ? true: false;
      }

      /****************************************************************
       * void alertColissionLeft()
       ****************************************************************/
      boolean alertColissionLeft() const {
        return (HCSR04distanceLeft <= DISTANCE_SUPER_MIN) ? true: false;
      }
      
      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        getDistance();

        getDistanceLeft();

        getDistanceRight();

        _voltage.calculate();
      }
  };
}
#endif
