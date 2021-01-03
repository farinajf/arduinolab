#ifndef SPIDER_LEG_H
#define SPIDER_LEG_H

#include <Adafruit_PWMServoDriver.h>
#include "SpiderLegItem.h"

namespace SPIDER {
  class SpiderLeg {
    private:
      const SpiderLegItem _coxa;
      const SpiderLegItem _femur;
      const SpiderLegItem _tibia;

    public:
      SpiderLeg(const uint8_t addrPata[3], const int position_0[3], const int position_90[3]);

      void init();
      void setServoAngles     (const Adafruit_PWMServoDriver *driver, const int angles[3]) const;
      void setDeltaServoAngles(const Adafruit_PWMServoDriver *driver, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const;
  };
}

#endif
