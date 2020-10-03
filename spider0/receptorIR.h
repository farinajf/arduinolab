#ifndef RECEPTOR_IR_H
#define RECEPTOR_IR_H

#include "pins.h"
#include "IRremote.h"

/**
 * 
 */
namespace SPIDER {
  enum CodigoIR {
    OK,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ASTERISK,
    HASH,
    T_0,
    T_1,
    T_2,
    T_3,
    T_4,
    T_5,
    T_6,
    T_7,
    T_8,
    T_9,
    CODE_REPEAT,
    NONE
  };

  class ReceptorIR {
    private:
      const IRrecv _receiver;
      CodigoIR     _lastResult = NONE;

      void     _encoding    (const decode_results *results) const;
      void     _ircode      (const decode_results *results) const;
      void     _dumpInfo    (const decode_results *results) const;
      CodigoIR _getResultado(const decode_results *results) const;
      
    public:
      ReceptorIR() : _receiver(PIN_IR_RECEIVER) {}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init();

      /****************************************************************
       * CodigoIR receive()
       ****************************************************************/
      CodigoIR receive();
  };
}
#endif
