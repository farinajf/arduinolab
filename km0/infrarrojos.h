#ifndef INFRARROJOS_H
#define INFRARROJOS_H

#include "pins.h"

namespace KM0CAR {
  class IR {
    private:
      const    int  _pinRight           = PIN_IR_RIGHT;
      const    int  _pinLeft            = PIN_IR_LEFT;
      
      unsigned long _checkRightPrevTime = 0;
      unsigned long _checkLeftPrevTime  = 0;
      bool          _rightOK            = true;
      bool          _leftOK             = true;

    public:
      bool isRightOK() const {return _rightOK;}
      bool isLeftOK()  const {return _leftOK;}
      
      void init();
      void checkIRObstacle();
  };
}

#endif
