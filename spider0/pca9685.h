#ifndef PCA9685_H
#define PCA9685_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "spiderLeg.h"

/**
 * 
 */
namespace SPIDER {

  enum LEG_T {
    LEG_FRONT,
    LEG_MIDDLE,
    LEG_BACK
  };
  
  class PCA9685 {
    private:
      const Adafruit_PWMServoDriver _driver;
      const SpiderLeg               _pataDelantera;
      const SpiderLeg               _pataMedia;
      const SpiderLeg               _pataTrasera;
      const uint8_t                 _fo = 50; // Frecuencia PWM de 50Hz o T=20ms

    public:
      PCA9685(const uint8_t addr,
              const uint8_t pataDelanteraAddr       [3],
              const uint8_t pataMediaAddr           [3],
              const uint8_t pataTraseraAddr         [3],
              const int     pataDelanteraPosition_0 [3],
              const int     pataMediaPosition_0     [3],
              const int     pataTraseraPosition_0   [3],
              const int     pataDelanteraPosition_90[3],
              const int     pataMediaPosition_90    [3],
              const int     pataTraseraPosition_90  [3]);

      void init();

      void move(const int pataDelanteraAngles[3], const int pataMediaAngles[3], const int pataTraseraAngles[3]);
      void leg (const LEG_T leg, const short coxaDelta, const short femurDelta, const short tibiaDelta) const;
  };
}
#endif
