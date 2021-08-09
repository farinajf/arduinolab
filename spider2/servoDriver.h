#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <Adafruit_PWMServoDriver.h>

namespace SPIDER {
  /**
   * 
   */
  class ServoDriver {
    private:
      const Adafruit_PWMServoDriver _driver;
      const uint8_t                 _addr;
      const uint8_t                 _fo = 50; // Frecuencia PWM de 50Hz o T=20ms

      /*********************************************************
       *                Metodos privados
       *********************************************************/
      uint16_t _getDuty(short servoAngle, short position_0, short position_90);

    public:
      ServoDriver(const uint8_t addr);

      void init();
      void rotateTo(uint8_t addr, short servoAngle, short position_0, short position_90);
  };
}

#endif
