#ifndef INFRARROJOS_H
#define INFRARROJOS_H

#include "pins.h"

namespace KM0CAR {
  class IR {
    private:
      const    int  _PIN_LEFT           = PIN_IR_LEFT;
      const    int  _PIN_RIGHT          = PIN_IR_RIGHT;
      unsigned long _checkRightPrevTime = 0;
      unsigned long _checkLeftPrevTime  = 0;
      bool          _rightOK            = true;
      bool          _leftOK             = true;

    public:
      bool isRightOK() const {return _rightOK;}
      bool isLeftOK()  const {return _leftOK;}
      
      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        pinMode(_PIN_LEFT,  INPUT);
        pinMode(_PIN_RIGHT, INPUT);
      }

      /****************************************************************
       * void checkIRObstacle()
       ****************************************************************/
      void checkIRObstacle() {
        //1.- Right
        if (millis() - _checkRightPrevTime > 50)
        {
          _rightOK = (digitalRead(_PIN_RIGHT) == HIGH) ? true : false;

          _checkRightPrevTime = millis();
        }

        //2.- Left
        if (millis() - _checkLeftPrevTime > 50)
        {
          _leftOK = (digitalRead(_PIN_LEFT) == HIGH) ? true : false;
        
          _checkLeftPrevTime = millis();
        }
      }
  };
}

#endif
