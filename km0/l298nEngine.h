#ifndef L298N_ENGINE_H
#define L298N_ENGINE_H

namespace KM0CAR {
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

      void init();
      void stop() const;
      void forward (int velocidad) const;
      void backward(int velocidad) const;
      void toString(int velocidad);
  };
}

#endif
