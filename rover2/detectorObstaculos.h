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

    public:
      DetectorObstaculos(DistanceSensor &sonar, DistanceSensor &sonarL, DistanceSensor &sonarR) :
        _sonar   (sonar),
        _sonarL  (sonarL),
        _sonarR  (sonarR),
        _average (_sonar.getDistanciaMaxima()),
        _averageL(_sonarL.getDistanciaMaxima()),
        _averageR(_sonarR.getDistanciaMaxima())
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
        unsigned int d  = _average.add (_sonar.getDistancia());
        unsigned int dl = _averageL.add(_sonarL.getDistancia());
        unsigned int dr = _averageR.add(_sonarR.getDistancia());

        Serial.print("Ping: "); Serial.print(dl); Serial.print(" cm. "); Serial.print(d); Serial.print(" cm. "); Serial.print(dr); Serial.println(" cm.");

        //0.- Valor inicial
        positionObstacle_t result = NONE;

        //1.- Si estamos muy cerca, nos vamos para atrás
        if (_sonar.hayObjetoCerca(d) == true) return FRONT;

        //2.-
        if (dl < dr) return (_sonarL.hayObjetoCerca(dl) == true) ? LEFT : NONE;
        else         return (_sonarR.hayObjetoCerca(dr) == true) ? RIGHT : NONE;
      }
  };
}

#endif
