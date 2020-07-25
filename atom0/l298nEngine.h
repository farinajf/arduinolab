#ifndef L298N_ENGINE_H
#define L298N_ENGINE_H

namespace ATOM0 {
  class L298NEngine {
    private:
      const int _pinEnable;
      const int _pinIN1;
      const int _pinIN2;
    
    public:
      /**
       * 
       */
      L298NEngine(const int pinEnable, const int pinIN1, const int pinIN2) :
        _pinEnable(pinEnable),
        _pinIN1   (pinIN1),
        _pinIN2   (pinIN2)
      {}

      /**
       * 
       */
      void init() {
        pinMode(_pinEnable, 0);
        pinMode(_pinIN1,    LOW);
        pinMode(_pinIN2,    LOW);
      }

      /**
       * 
       */
      void forward(int velocidad) const {
        //toString(velocidad);
        analogWrite (_pinEnable, velocidad);
        digitalWrite(_pinIN1,    HIGH);
        digitalWrite(_pinIN2,    LOW);
      }

      /**
       * 
       */
      void backward(int velocidad) const {
        //toString(velocidad);
        analogWrite (_pinEnable, velocidad);
        digitalWrite(_pinIN1,    LOW);
        digitalWrite(_pinIN2,    HIGH);
      }

      /**
       * Detiene el motor.
       */
      void stop() const {
        analogWrite (_pinEnable, 0);
        digitalWrite(_pinIN1,    LOW);
        digitalWrite(_pinIN2,    LOW);
      }

      void toString(int velocidad) {
        Serial.print("PIN enable: "); Serial.print(_pinEnable);
        Serial.print(" PIN 1:     "); Serial.print(_pinIN1);
        Serial.print(" PIN 2:     "); Serial.print(_pinIN2);
        Serial.print(" velocidad: "); Serial.print(velocidad);
        Serial.println();
      }
  };
}
#endif
