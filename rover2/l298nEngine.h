#ifndef L298N_ENGINE_H
#define L298N_ENGINE_H

namespace ROVER2
{
  class L298NEngine
  {
    private:
      const int  _pinEnable;
      const int  _pinIN1;
      const int  _pinIN2;
      short      _speed;
      const char _nombre;
      
      /**
       * void _forward()
       */
      void _forward() const {
        Serial.print("L298NEngine._forward(");Serial.print(_nombre);Serial.print("): ");Serial.println(_speed);
        analogWrite (_pinEnable, _speed);
        digitalWrite(_pinIN1,    HIGH);
        digitalWrite(_pinIN2,    LOW);
      }
      
      /**
       * void _backward()
       */
      void _backward() const {
        Serial.print("L298NEngine._backward(");Serial.print(_nombre);Serial.print("): ");Serial.println(_speed);
        analogWrite (_pinEnable, -1 * _speed);
        digitalWrite(_pinIN1,    LOW);
        digitalWrite(_pinIN2,    HIGH);
      }
      
      /**
       * void _stop()
       */
      void _stop() const {
        analogWrite (_pinEnable, 0);
        digitalWrite(_pinIN1,    LOW);
        digitalWrite(_pinIN2,    LOW);
      }
    
    public:
      L298NEngine(const int pinEnable, const int pinIN1, const int pinIN2, const char n) : _pinEnable(pinEnable), _pinIN1(pinIN1), _pinIN2(pinIN2), _speed(0), _nombre(n) {}
      
      /**
       * void init()
       */
      void init() {
        pinMode(_pinEnable, OUTPUT);
        pinMode(_pinIN1,    OUTPUT);
        pinMode(_pinIN2,    OUTPUT);
      }
      
      /**
       * void setSpeed(const short x)
       */
      void setSpeed(const short x) {
        _speed = x;
        
        if (_speed >= 0) _forward();
        else             _backward();
      }
      
      /**
       * void stop()
       */
      void stop() {
        _speed = 0;
        _stop();
      }
      
      /**
       * short getSpeed()
       */
      short getSpeed() const {return _speed;}
  };
}

#endif
