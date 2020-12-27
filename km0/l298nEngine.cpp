#include <Arduino.h>
#include "l298nEngine.h"

namespace KM0CAR {
  /****************************************************************
   * void init()
   ****************************************************************/
  void L298NEngine::init() {
    pinMode(_pinEnable, OUTPUT);
    pinMode(_pinIN1,    OUTPUT);
    pinMode(_pinIN2,    OUTPUT);
  }

  /****************************************************************
   * void forward(int velocidad)
   ****************************************************************/
  void L298NEngine::forward(int velocidad) const {
    //toString(velocidad);
    analogWrite (_pinEnable, velocidad);
    digitalWrite(_pinIN1,    LOW);
    digitalWrite(_pinIN2,    HIGH);
  }

  /****************************************************************
   * void backward(int velocidad)
   ****************************************************************/
  void L298NEngine::backward(int velocidad) const {
    //toString(velocidad);
    analogWrite (_pinEnable, velocidad);
    digitalWrite(_pinIN1,    HIGH);
    digitalWrite(_pinIN2,    LOW);
  }

  /****************************************************************
   * void stop()
   ****************************************************************/
  void L298NEngine::stop() const {
    analogWrite (_pinEnable, 0);
    digitalWrite(_pinIN1,    LOW);
    digitalWrite(_pinIN2,    LOW);
  }

  /****************************************************************
   * void toString(int velocidad)
   ****************************************************************/
  void L298NEngine::toString(int velocidad) {
    Serial.print("PIN enable: "); Serial.print(_pinEnable);
    Serial.print(" PIN 1:     "); Serial.print(_pinIN1);
    Serial.print(" PIN 2:     "); Serial.print(_pinIN2);
    Serial.print(" velocidad: "); Serial.print(velocidad);
    Serial.println();
  }
}
