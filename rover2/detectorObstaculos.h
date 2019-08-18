#include "movingAverage.h"
#include "distanceSensor.h"

#ifndef DETECTOR_OBSTACULOS_H
#define DETECTOR_OBSTACULOS_H

namespace ROVER2
{
  enum positionObstacle_t {
    RIGHT,
    LEFT,
    FRONT,
    NONE
  };
  
  class DetectorObstaculos {
    private:
      MovingAverage<unsigned int, 1> _average;
      MovingAverage<unsigned int, 1> _averageL;
      MovingAverage<unsigned int, 1> _averageR;
      DistanceSensor                 _sonar;
      DistanceSensor                 _sonarL;
      DistanceSensor                 _sonarR;
      const unsigned int             _minDistance;
      
      bool _isObstacle(unsigned int x) const {return (x <= _minDistance);}

    public:
      DetectorObstaculos(DistanceSensor &sonar, DistanceSensor &sonarL, DistanceSensor &sonarR, unsigned int minDistance, unsigned int maxDistance) :
        _sonar      (sonar),
        _sonarL     (sonarL),
        _sonarR     (sonarR),
        _average    (maxDistance),
        _averageL   (maxDistance),
        _averageR   (maxDistance),
        _minDistance(minDistance)
        {}
      
      void init() {
        Serial.begin(9600);
      }
      
      /**
       * positionObstacle_t turn()
       * 
       * Result:
       *     +1 : girar derecha
       *     -1 : girar izquierda
       *      0 : no hay obstaculo
       */
      positionObstacle_t turn() {
        unsigned int d  = _average.add (_sonar.getDistance());
        unsigned int dl = _averageL.add(_sonarL.getDistance());
        unsigned int dr = _averageR.add(_sonarR.getDistance());

        Serial.print("Ping: "); Serial.print(dl); Serial.print(" cm. "); Serial.print(d); Serial.print(" cm. "); Serial.print(dr); Serial.println(" cm.");

        //0.- Valor inicial
        positionObstacle_t result = NONE;

        //1.- Si estamos muy cerca, nos vamos para atrás
        if (_isObstacle(d) == true) return FRONT;

        //2.-
        if (dl < dr)
        {
          if (dl < d) return (_isObstacle(dl) == true) ? LEFT : NONE;
          return (_isObstacle(d) == true) ? FRONT : NONE;
        }

        //3.-
        if (dr < d) return (_isObstacle(dr) == true) ? RIGHT : NONE;

        //4.-
        return (_isObstacle(d) == true) ? FRONT : NONE;
      }
  };
}

#endif
