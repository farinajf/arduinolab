#ifndef ATOM0_SENSORS_H
#define ATOM0_SENSORS_H

#include "ultrasonic.h"
#include "infrarrojos.h"


/**
 * 
 */
namespace ATOM0 {
  class Sensors {
    private:
      Sonars _sonars;
      IR     _ir;

    public:
      Sensors() {}

      double getSensorDistance() const {return _sonars.getDistanceFront();}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _sonars.init();
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
        return (_sonars.getDistanceFront() > DISTANCE_MIN) ? true: false;
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
        return (_sonars.getDistanceFront() <= DISTANCE_SUPER_MIN) ? true: false;
      }

      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        _sonars.checkDistanceFront();

        _ir.checkIRObstacle();
      }
  };
}

#endif
