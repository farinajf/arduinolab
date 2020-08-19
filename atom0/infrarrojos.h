#ifndef WD5_INFRARROJOS_H
#define WD5_INFRARROJOS_H

namespace ATOM0 {
  class IR {
    private:
      unsigned long _checkRightPrevTime = 0;
      unsigned long _checkLeftPrevTime  = 0;
      bool          _rightOK            = true;
      bool          _leftOK             = true;
      

    public:
      bool isRightOK() const {return _rightOK;}
      bool isLeftOK()  const {return _leftOK;}
      
      /**
       * void init()
       */
      void init() {
        pinMode(PIN_IR_LEFT,  INPUT);
        pinMode(PIN_IR_RIGHT, INPUT);
      }

      /****************************************************************
       * void checkIRObstacle()
       ****************************************************************/
      void checkIRObstacle() {
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
