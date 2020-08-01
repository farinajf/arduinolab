#ifndef ATOM0_SENSORS_H
#define ATOM0_SENSORS_H

#include "atom0globals.h"
#include "ultrasonic.h"
#include "infrarrojos.h"


/**
 * 
 */
namespace ATOM0 {
  class Sensors {
    private:
      IR _ir;

    public:
      Sensors() {}

      double getSensorDistance() const {return (HCSR04distance > 0) ? HCSR04distance : DISTANCE_MAX;}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        ultrasonicInit();
        _ir.init();
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
       * HIGH -> OK
       ****************************************************************/
      boolean isRightOK() const {
        return _ir.isRightOK();
      }

      /****************************************************************
       * void isLeftOK()
       * HIGH -> OK
       ****************************************************************/
      boolean isLeftOK() const {
        return _ir.isLeftOK();
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
        return (HCSR04distance <= DISTANCE_SUPER_MIN) ? true: false;
      }

      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        getDistance();

        _ir.checkIRObstacle();
      }
  };
}

#endif
