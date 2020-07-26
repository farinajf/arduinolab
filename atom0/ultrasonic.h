#include "pins.h"
#include "atom0globals.h"
#include <NewPing.h>

#ifndef ATOM0_ULTRASONIC_H
#define ATOM0_ULTRASONIC_H

namespace ATOM0 {
  class Sonars {
    private:
      NewPing       _sonar;
      unsigned long _distancePrevTime = 0;
      double        _distance         = 0;

      /**
       * double _calculateDistanceFront()
       */
      double _calculateDistanceFront() {
        double result = _sonar.convert_cm(_sonar.ping_median(3));
        
        return (result > 0) ? result : DISTANCE_MAX;
      }
      
    public:
      Sonars() : _sonar (PIN_TRIGGER_CENTER, PIN_ECHO_CENTER, DISTANCE_MAX),
                 _distancePrevTime(0),
                 _distance(0)
                 {}
                 
      double getDistanceFront() const {return _distance;}
      
      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {}

      /**
       * double checkDistanceFront()
       * 
       * Calcula la distancia a la izquierda.
       * 
       */
      double checkDistanceFront() {
        if (millis() - _distancePrevTime <= PING_INTERVAL) return _distance;

        _distance         = _calculateDistanceFront();
        _distancePrevTime = millis();
        
        return _distance;
      }
  };
}
#endif
