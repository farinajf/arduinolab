#ifndef BOCINA_H
#define BOCINA_H

#include "pins.h"

namespace KM0CAR {
  class Bocina {
    private:
      const int _pin = PIN_BUZZER;

    public:
      void init();
      void beep(int d) const;
      void beep(int n, int d) const;
  };
}

#endif
