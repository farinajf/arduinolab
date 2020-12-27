#ifndef LUCES_H
#define LUCES_H

#include "pins.h"

namespace KM0CAR {
  class Luces {
    private:
      const int _pinRight = PIN_LIGHT_RIGHT;
      const int _pinLeft  = PIN_LIGHT_LEFT;

    public:
      void init();

      void switchOff()   const;
      void switchOn()    const;
      void switchRight() const;
      void switchLeft()  const;
  };
}

#endif
