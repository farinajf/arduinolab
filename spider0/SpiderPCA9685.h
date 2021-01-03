#ifndef SPIDER_PCA9685_H
#define SPIDER_PCA9685_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "SpiderLeg.h"

namespace SPIDER {
  enum Leg_t {
    LEG_1,
    LEG_2,
    LEG_3
  };

  /**
   * 
   */
  class SpiderPCA9685 {
    private:
      const Adafruit_PWMServoDriver _driver;
      const SpiderLeg               _pata1;   //Delantera
      const SpiderLeg               _pata2;   //Media
      const SpiderLeg               _pata3;   //Trasera
      const uint8_t                 _fo = 50; // Frecuencia PWM de 50Hz o T=20ms

    public:
      SpiderPCA9685(const uint8_t addr,
                    const uint8_t pata1_Addr       [3],
                    const uint8_t pata2_Addr       [3],
                    const uint8_t pata3_Addr       [3],
                    const int     pata1_Position_0 [3],
                    const int     pata2_Position_0 [3],
                    const int     pata3_Position_0 [3],
                    const int     pata1_Position_90[3],
                    const int     pata2_Position_90[3],
                    const int     pata3_Position_90[3]);

      void init();
      void move(const int pata1_Angles[3], const int pata2_Angles[3], const int pata3_Angles[3]) const;
      void move(const Leg_t leg, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const;
  };
}

#endif
