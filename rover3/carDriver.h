#include "l298nEngine.h"

#ifndef CAR_DRIVER_H
#define CAR_DRIVER_H

namespace ROVER3
{
  class CarDriver
  {
    private:
      L298NEngine _motorDerecho;
      L298NEngine _motorIzquierdo;

    public:
      CarDriver(L298NEngine &md, L298NEngine &mi) :
        _motorDerecho  (md),
        _motorIzquierdo(mi)
        {}

    /**
     * 
     */
    void init() {
      _motorDerecho.init();
      _motorIzquierdo.init();
    }

    /**
     * 
     */
    void forward() {
      _motorDerecho.forward();
      _motorIzquierdo.forward();
    }

    /**
     * 
     */
    void backward() {
      _motorDerecho.backward();
      _motorIzquierdo.backward();
    }

    /**
     * 
     */
    void derecha() {
      _motorDerecho.backward();
      _motorIzquierdo.forward();
    }

    /**
     * 
     */
    void izquierda() {
      _motorDerecho.forward();
      _motorIzquierdo.backward();
    }

    /**
     * 
     */
    void parar() {
      _motorDerecho.parar();
      _motorIzquierdo.parar();
    }
  };
}
#endif
