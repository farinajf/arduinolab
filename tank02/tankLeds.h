#include "pins.h"

#ifndef TANK_LEDS_H
#define TANK_LEDS_H

namespace TANK02
{
  class TankLeds
  {
    private:
      void _high(int pin) {digitalWrite(pin, HIGH);}
      void _low (int pin) {digitalWrite(pin, LOW);}

    public:
      /****************************************************************
       * 
       ****************************************************************/
      void init() {
        pinMode(PIN_LED_RIGHT,  OUTPUT);
        pinMode(PIN_LED_CENTER, OUTPUT);
        pinMode(PIN_LED_LEFT,   OUTPUT);

        _high(PIN_LED_RIGHT);
        _high(PIN_LED_CENTER);
        _high(PIN_LED_LEFT);

        delay(1000);

        _low(PIN_LED_RIGHT);
        _low(PIN_LED_CENTER);
        _low(PIN_LED_LEFT);
      }

      /****************************************************************
       * 
       ****************************************************************/
      void switchOnCenter() {_high(PIN_LED_CENTER);}
      void switchOnRight()  {_high(PIN_LED_RIGHT);}
      void switchOnLeft()  {_high(PIN_LED_LEFT);}

      void switchOn() {
        switchOnCenter();
        switchOnRight();
        switchOnLeft();
      }

      /****************************************************************
       * 
       ****************************************************************/
      void switchOff() {
        _low(PIN_LED_RIGHT);
        _low(PIN_LED_CENTER);
        _low(PIN_LED_LEFT);
      }
  };
}
#endif
