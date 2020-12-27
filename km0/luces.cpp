#include "luces.h"

namespace KM0CAR {
  /****************************************************************
   * void init()
   ****************************************************************/
  void Luces::init() {
    pinMode(_pinRight, OUTPUT);
    pinMode(_pinLeft,  OUTPUT);
        
    digitalWrite(_pinRight, LOW);
    digitalWrite(_pinLeft,  LOW);
  }

  /****************************************************************
   * void switchOff()
   * 
   ****************************************************************/
  void Luces::switchOff() const {
    digitalWrite(_pinRight, LOW);
    digitalWrite(_pinLeft,  LOW);
  }

  /****************************************************************
   * void switchOn()
   * 
   ****************************************************************/
  void Luces::switchOn() const {
    digitalWrite(_pinRight, HIGH);
    digitalWrite(_pinLeft,  HIGH);
  }

  /****************************************************************
   * void switchRight()
   * 
   ****************************************************************/
  void Luces::switchRight() const {
    digitalWrite(_pinRight, HIGH);
    digitalWrite(_pinLeft,  LOW);
  }

  /****************************************************************
   * void switchLeft()
   * 
   ****************************************************************/
  void Luces::switchLeft() const {
    digitalWrite(_pinRight, LOW);
    digitalWrite(_pinLeft,  HIGH);
  }
}
