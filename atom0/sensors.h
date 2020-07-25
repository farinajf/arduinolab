#ifndef ATOM0_SENSORS_H
#define ATOM0_SENSORS_H

#include "ultrasonic.h"

/**
 * 
 */
namespace ATOM0 {
  class Sensors {
    private:
      unsigned long _distancePrevTime = 0;
      double        _distance         = 0;

    public:
      Sensors() {}

      double getSensorDistance() const {return _distance;}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        //TODO
      }

      /****************************************************************
       * void isOK()
       ****************************************************************/
      boolean isOK() const {
        return isForwardOK();
      }

      /****************************************************************
       * void isForwardOK()
       ****************************************************************/
      boolean isForwardOK() const {
        return (_distance > DISTANCE_MIN) ? true: false;
      }

      /****************************************************************
       * void alertColission()
       ****************************************************************/
      boolean alertColission() const {
        return alertColissionForward();
      }

      /****************************************************************
       * void alertColissionForward()
       ****************************************************************/
      boolean alertColissionForward() const {
        return (_distance <= DISTANCE_SUPER_MIN) ? true: false;
      }

      /****************************************************************
       * void calculateForward()
       ****************************************************************/
      double calculateForward() {
        if (millis() - _distancePrevTime <= PING_INTERVAL) return _distance;

        _distance         = getDistanceFront();
        _distancePrevTime = millis();
        
        return _distance;
      }

      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        calculateForward();
      }
  };
}

#endif
