#ifndef SPIDER_LEG_ITEM_H
#define SPIDER_LEG_ITEM_H

#include "globals.h"
#include <stdint.h>
#include <Adafruit_PWMServoDriver.h>

/**
 * Representa una parte de una extremidad controlada por un servo.
 */
namespace SPIDER {
  class SpiderLegItem {
    private:
      const uint8_t _addr;
      const int     _position_0;
      const int     _position_90;
      int           _angle;

      uint16_t _getDuty() const;

    public:
      SpiderLegItem(const uint8_t addr, const int position_0, const int position_90) : _addr       (addr),
                                                                                       _position_0 (position_0),
                                                                                       _position_90(position_90) {}

      void init();
      void setDeltaAngle(const Adafruit_PWMServoDriver *driver, const short delta);
      void setAngle     (const Adafruit_PWMServoDriver *driver, const int   angulo);
  };
}

#endif
