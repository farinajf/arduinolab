#ifndef L298N_ENGINE_H
#define L298N_ENGINE_H

namespace ROVER4
{
  class L298NEngine
  {
    private:
      const int _pinIN1;
      const int _pinIN2;
    
    public:
      /**
       * 
       */
      L298NEngine(const int pinIN1, const int pinIN2) :
        _pinIN1(pinIN1),
        _pinIN2(pinIN2)
      {}

      /**
       * 
       */
      void init() {
        pinMode(_pinIN1, OUTPUT);
        pinMode(_pinIN2, OUTPUT);
      }

      /**
       * 
       */
      void forward() const {
        digitalWrite(_pinIN1, LOW);
        digitalWrite(_pinIN2, HIGH);
      }

      /**
       * 
       */
      void backward() const {
        digitalWrite(_pinIN1, HIGH);
        digitalWrite(_pinIN2, LOW);
      }

      /**
       * Detiene el motor.
       */
      void stop() const {
        digitalWrite(_pinIN1, LOW);
        digitalWrite(_pinIN2, LOW);
      }
  };
}
#endif
