#include <NewPing.h>

// NewPing - Version: 1.9.1
#include <NewPing.h>

#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

namespace ROVER2 {
class DistanceSensor
{
  private:
    unsigned int _distanciaMax;
    unsigned int _distanciaMin;
    NewPing      _sonar;

  public:
    DistanceSensor(int pinEcho, int pingTrig, unsigned int distanciaMin, unsigned int distanciaMax) :
      _distanciaMin(distanciaMin),
      _distanciaMax(distanciaMax),
      _sonar       (pingTrig, pinEcho, _distanciaMax)
    {}

    unsigned int getDistanciaMinima() const {return _distanciaMin;}
    unsigned int getDistanciaMaxima() const {return _distanciaMax;}
    
    bool hayObjetoCerca(unsigned int x) const {return (x <= _distanciaMin);}
    
    /**
     * Devuelve la distancia al objeto.
     */
    unsigned int getDistancia() {
      unsigned int result = 0;

      if ((result = _sonar.convert_cm(_sonar.ping_median(3))) == 0) return _distanciaMax;

      return result;
    }
};
}

#endif
