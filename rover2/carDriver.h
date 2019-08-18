#include "l298nEngine.h"

#ifndef CAR_DRIVER_H
#define CAR_DRIVER_H

namespace ROVER2
{
  class CarDriver
  {
    private:
      L298NEngine _engineR;
      L298NEngine _engineL;
      const short _speedR;
      const short _speedL;
      const short _speedTurn;
    
    public:
      CarDriver(const short pinEN_A, const short pinIN1_A, const short pinIN2_A, const short speedA,
                const short pinEN_B, const short pinIN1_B, const short pinIN2_B, const short speedB) :
                _engineR(pinEN_A, pinIN1_A, pinIN2_A),
                _speedR (speedA),
                _engineL(pinEN_B, pinIN1_B, pinIN2_B),
                _speedL (speedB),
                _speedTurn(150)
                {}
      
      /**
       * void init()
       */
      void init() {
        _engineR.init();
        _engineL.init();
      }
      
      /**
       * void forward()
       */
      void forward() {
        _engineR.setSpeed(_speedR);
        _engineL.setSpeed(_speedL);
      }
      
      /**
       * void backward()
       */
      void backward() {
        _engineR.setSpeed(-1 * _speedTurn);
        _engineL.setSpeed(-1 * _speedTurn);
      }
      
      /**
       * void left()
       */
      void left() {
        _engineR.setSpeed(_speedTurn);
        _engineL.setSpeed(-1 * _speedTurn);
      }
      
      /**
       * void right()
       */
      void right() {
        _engineR.setSpeed(-1 * _speedTurn);
        _engineL.setSpeed(_speedTurn);
      }
      
      /**
       * void stop()
       */
      void stop() {
        _engineR.stop();
        _engineL.stop();
      }
  };
}

#endif
