#ifndef LUCES_H
#define LUCES_H

#include "pins.h"

namespace KM0CAR {
  class Luces {
    private:

    public:
      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        pinMode(PIN_LIGHT_RIGHT, OUTPUT);
        pinMode(PIN_LIGHT_LEFT,  OUTPUT);
        
        digitalWrite(PIN_LIGHT_RIGHT, LOW);
        digitalWrite(PIN_LIGHT_LEFT,  LOW);
      }

      /****************************************************************
       * void switchOff()
       * 
       ****************************************************************/
      void switchOff() const {
        digitalWrite(PIN_LIGHT_RIGHT, LOW);
        digitalWrite(PIN_LIGHT_LEFT,  LOW);
      }

      /****************************************************************
       * void switchOn()
       * 
       ****************************************************************/
      void switchOn() const {
        digitalWrite(PIN_LIGHT_RIGHT, HIGH);
        digitalWrite(PIN_LIGHT_LEFT,  HIGH);
      }

      /****************************************************************
       * void switchRight()
       * 
       ****************************************************************/
      void switchRight() const {
        digitalWrite(PIN_LIGHT_RIGHT, HIGH);
        digitalWrite(PIN_LIGHT_LEFT,  LOW);
      }

      /****************************************************************
       * void switchLeft()
       * 
       ****************************************************************/
      void switchLeft() const {
        digitalWrite(PIN_LIGHT_RIGHT, LOW);
        digitalWrite(PIN_LIGHT_LEFT,  HIGH);
      }
  };
}

#endif
