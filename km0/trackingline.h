#ifndef TRACKINGLINE_H
#define TRACKINGLINE_H

#include "pins.h"

namespace KM0CAR {
  class TrakingLine {
    private:
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
        pinMode(PIN_TLS_LEFT,  INPUT);
        pinMode(PIN_TLS_RIGHT, INPUT);
      }

      /****************************************************************
       * void checkLine()
       ****************************************************************/
      void checkLine() {
        //1.- Right
        if (millis() - _checkRightPrevTime > 50)
        {
          _rightOK = (digitalRead(PIN_IR_RIGHT) == HIGH) ? true : false;

          _checkRightPrevTime = millis();
        }

        //2.- Left
        if (millis() - _checkLeftPrevTime > 50)
        {
          _leftOK = (digitalRead(PIN_IR_LEFT) == HIGH) ? true : false;
        
          _checkLeftPrevTime = millis();
        }
      }
  };
}

#endif
