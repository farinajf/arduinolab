#include "pins.h"
#include "ultrasonic.h"

#ifndef ROVER5_SENSORS_H
#define ROVER5_SENSORS_H

#define DEBUG true

/**
 * 
 */
namespace ROVER5
{
  class Sensors {
    private:
      unsigned long _distanceRightPrevTime = 0;
      unsigned long _distanceLeftPrevTime  = 0;
      unsigned long _distancePrevTime      = 0;     
      double        _distanceRight         = 0;
      double        _distanceLeft          = 0;
      double        _distance              = 0;
      bool          _batteryOK             = true;

    public:
      double getSensorRightDistance() const {return _distanceRight;}
      double getSensorLeftDistance()  const {return _distanceLeft;}
      double getSensorDistance()      const {return _distance;}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        //TODO
      }

      /****************************************************************
       * void isBatteryOK()
       ****************************************************************/
      boolean isBatteryOK() {
        //TODO
        return _batteryOK;
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
        return (_distance > DISTANCE_MIN) ? true: false;
      }

      /****************************************************************
       * void isRightOK()
       ****************************************************************/
      boolean isRightOK() const {
        return (_distanceRight > DISTANCE_MIN_LATERAL) ? true: false;
      }

      /****************************************************************
       * void isLeftOK()
       ****************************************************************/
      boolean isLeftOK() const {
        return (_distanceLeft > DISTANCE_MIN_LATERAL) ? true: false;
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
       * void calculateLeft()
       ****************************************************************/
      double calculateLeft() {
        if (millis() - _distanceLeftPrevTime <= PING_INTERVAL) return _distanceLeft;
        
        _distanceLeft         = getDistanceLeft();
        _distanceLeftPrevTime = millis();

        
        return _distanceLeft;
      }

      /****************************************************************
       * void calculateRight()
       ****************************************************************/
      double calculateRight() {
        if (millis() - _distanceRightPrevTime <= PING_INTERVAL) return _distanceRight;
        
        _distanceRight         = getDistanceRight();
        _distanceRightPrevTime = millis();
        
        return _distanceRight;
      }

      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        calculateForward();

        calculateRight();

        calculateLeft();
      }
  };
}
#endif
