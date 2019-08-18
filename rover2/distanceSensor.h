#include <NewPing.h>

// NewPing - Version: 1.9.1
#include <NewPing.h>

#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

namespace ROVER2
{
  class DistanceSensor
  {
    private:
      unsigned int _maxDistance;
      NewPing        _sonar;
      
    public:
      DistanceSensor(unsigned int maxDistance, short pinEcho, short pingTrig) : _maxDistance(maxDistance),
                                                                         _sonar(pingTrig, pinEcho, maxDistance)
      {}
      
      /**
       * Devuelve la distancia al objeto.
       */
      unsigned int getDistance() {
        unsigned int result = 0;
        
        if ((result = _sonar.convert_cm(_sonar.ping_median(5))) == 0) return _maxDistance;
        
        return result;
      }
  };
}

#endif
