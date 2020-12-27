#include "bocina.h"

namespace KM0CAR {
  /****************************************************************
   * void init()
   ****************************************************************/
  void Bocina::init() {
    pinMode     (_pin, OUTPUT);
    digitalWrite(_pin, LOW);
  }

  /****************************************************************
    * void beep(int x)
    * 
    * d: duracion en ms.
    * 
    ****************************************************************/
  void Bocina::beep(int d) const {
    digitalWrite(_pin, HIGH);
    delay(d);
    digitalWrite(_pin, LOW);
  }

  /****************************************************************
   * void beep(int n, int d)
   * 
   * n: numero de beeps
   * d: duracion en ms.
   * 
  ****************************************************************/
  void Bocina::beep(int n, int d) const {
    for (int i = 0; i < n; i++)
    {
      digitalWrite(_pin, HIGH);
      delay(d);

      digitalWrite(_pin, LOW);
      delay(d);
    }
  }
}
