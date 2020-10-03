#ifndef SPIDERLEG_H
#define SPIDERLEG_H

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "spiderLegItem.h"

namespace SPIDER {
  class SpiderLeg {
    private:
      const SpiderLegItem _coxa;
      const SpiderLegItem _femur;
      const SpiderLegItem _tibia;
      
    public:
      SpiderLeg(const uint8_t addrPata[3], const int position_0[3], const int position_90[3]);

      void init();

      void setServoAngles(const Adafruit_PWMServoDriver driver, const int angles[3]);
      void setServoAngles(const Adafruit_PWMServoDriver driver, const int coxaAngle, const int femurAngle, const int tibiaAngle);
  };
}
#endif
