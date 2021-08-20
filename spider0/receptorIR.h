#ifndef RECEPTOR_IR_H
#define RECEPTOR_IR_H

#include "globals.h"
//#include <IRremote.h>

namespace SPIDER {
  enum CodigoIR {
    IR_OK,
    IR_UP,
    IR_DOWN,
    IR_LEFT,
    IR_RIGHT,
    IR_ASTERISK,
    IR_HASH,
    IR_T_0,
    IR_T_1,
    IR_T_2,
    IR_T_3,
    IR_T_4,
    IR_T_5,
    IR_T_6,
    IR_T_7,
    IR_T_8,
    IR_T_9,
    IR_CODE_REPEAT,
    IR_NONE
  };

  /**
   * 
   */
  class ReceptorIR {
    private:
//      const IRrecv _receiver;
      CodigoIR     _lastResult = IR_NONE;

//      void     _encoding    (const decode_results *results) const;
//      void     _ircode      (const decode_results *results) const;
//      void     _dumpInfo    (const decode_results *results) const;
//      CodigoIR _getResultado(const decode_results *results) const;

    public:
//      ReceptorIR() : _receiver(PIN_IR_RECEIVER) {}

      void     init();
      CodigoIR receive();
  };
}

#endif
