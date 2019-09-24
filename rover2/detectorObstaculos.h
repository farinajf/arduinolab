#include "distanceSensor.h"

#ifndef DETECTOR_OBSTACULOS_H
#define DETECTOR_OBSTACULOS_H

namespace ROVER2
{
  enum positionObstacle_t {
    RIGHT,
    LEFT,
    FRONT_LEFT,
    FRONT_RIGHT,
    NONE
  };
  
  class DetectorObstaculos {
    private:
      DistanceSensor _sonar;
      DistanceSensor _sonarL;
      DistanceSensor _sonarR;

    public:
      DetectorObstaculos(DistanceSensor &sonar, DistanceSensor &sonarL, DistanceSensor &sonarR) :
        _sonar   (sonar),
        _sonarL  (sonarL),
        _sonarR  (sonarR)
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
        unsigned int d  = _sonar.getDistancia();
        unsigned int dl = _sonarL.getDistancia();
        unsigned int dr = _sonarR.getDistancia();


        Serial.print("Ping: "); Serial.print(dl); Serial.print(" cm. "); Serial.print(d); Serial.print(" cm. "); Serial.print(dr); Serial.println(" cm.");

        //0.- Valor inicial
        positionObstacle_t result = NONE;

        //1.- Si estamos muy cerca, nos vamos para atrás
        if (_sonar.hayObjetoCerca(d) == true)
        {
          return (dl < dr) ? FRONT_LEFT : FRONT_RIGHT;
        }

        //2.-
        if (dl < dr) return (_sonarL.hayObjetoCerca(dl) == true) ? LEFT  : NONE;
        else         return (_sonarR.hayObjetoCerca(dr) == true) ? RIGHT : NONE;
      }
  };
}

#endif
