#ifndef BOCINA_H
#define BOCINA_H

#include "pins.h"

namespace KM0CAR {
  class Bocina {
    private:

    public:
      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        pinMode     (PIN_BUZZER, OUTPUT);
        digitalWrite(PIN_BUZZER, LOW);
      }

      /****************************************************************
       * void beep(int x)
       * 
       * d: duracion en ms.
       * 
       ****************************************************************/
      void beep(int d) const {
//        digitalWrite(PIN_BUZZER, HIGH);
//        delay(d);
//        digitalWrite(PIN_BUZZER, LOW);
      }

      /****************************************************************
       * void beep(int n, int d)
       * 
       * n: numero de beeps
       * d: duracion en ms.
       * 
       ****************************************************************/
      void beep(int n, int d) const {
//        for (int i = 0; i < n; i++)
//        {
//          digitalWrite(PIN_BUZZER, HIGH);
//          delay(d);
//          digitalWrite(PIN_BUZZER, LOW);
//          delay(d);
//        }
      }
  };
}

#endif
