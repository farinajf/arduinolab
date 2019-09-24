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
      CarDriver(const int pinEN_A, const int pinIN1_A, const int pinIN2_A, const short speedA,
                const int pinEN_B, const int pinIN1_B, const int pinIN2_B, const short speedB, const short speedTurn) :
                _engineR  (pinEN_A, pinIN1_A, pinIN2_A, 'R'),
                _speedR   (speedA),
                _engineL  (pinEN_B, pinIN1_B, pinIN2_B, 'L'),
                _speedL   (speedB),
                _speedTurn(speedTurn)
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
        Serial.println("Fordward...");
      }
      
      /**
       * void backward()
       */
      void backward() {
        _engineR.setSpeed(-1 * _speedR);
        _engineL.setSpeed(-1 * _speedL);
        Serial.println("Backward...");
      }
      
      /**
       * void left()
       */
      void left() {
        _engineR.setSpeed(_speedTurn);
        _engineL.setSpeed(-1 * _speedTurn);
        Serial.println("Left...");
      }
      
      /**
       * void right()
       */
      void right() {
        _engineR.setSpeed(-1 * _speedTurn);
        _engineL.setSpeed(_speedTurn);
        Serial.println("Right...");
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
