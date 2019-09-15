#include "l298nEngine.h"
#include "tankGlobals.h"

#ifndef TANK_DRIVER_H
#define TANK_DRIVER_H

namespace TANK01
{
  class TankDriver
  {
    private:
      enum ESTADO {
        FORWARD,
        BACKWARD,
        TURNLEFT,
        TURNRIGHT,
        STOP,
        START
      }
      _estado = START;
      L298NEngine _motorDerecho;
      L298NEngine _motorIzquierdo;
      int         _velocidad; // velocidad es 100x(_velocidad/255)%
      int         _velocidadGiro;

    public:
      TankDriver(L298NEngine &md, L298NEngine &mi) :
        _motorDerecho  (md),
        _motorIzquierdo(mi),
        _velocidad     (VELOCIDAD),
        _velocidadGiro (VELOCIDAD_GIRO)
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
      if (_estado == FORWARD) return;
      
      _motorDerecho.forward  (_velocidad);
      _motorIzquierdo.forward(_velocidad);

      _estado = FORWARD;
    }

    /**
     * 
     */
    void backward() {
      if (_estado == BACKWARD) return;
      
      _motorDerecho.backward  (_velocidad);
      _motorIzquierdo.backward(_velocidad);

      _estado = BACKWARD;
    }

    /**
     * 
     */
    void derecha() {
      if (_estado == TURNLEFT) return;
      
      _motorDerecho.backward (_velocidadGiro);
      _motorIzquierdo.forward(_velocidadGiro);

      _estado = TURNLEFT;
    }

    /**
     * 
     */
    void izquierda() {
      if (_estado == TURNRIGHT) return;
      
      _motorDerecho.forward   (_velocidadGiro);
      _motorIzquierdo.backward(_velocidadGiro);

      _estado = TURNRIGHT;
    }

    /**
     * 
     */
    void parar() {
      _motorDerecho.parar();
      _motorIzquierdo.parar();
      _estado = STOP;
    }
  };
}
#endif
