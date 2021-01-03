#ifndef SPIDER_MOTOR_H
#define SPIDER_MOTOR_H

#include "SpiderPCA9685.h"

namespace SPIDER {
  enum SpiderLeg_t {
    LEG_RIGHT_1,
    LEG_RIGHT_2,
    LEG_RIGHT_3,
    LEG_LEFT_1,
    LEG_LEFT_2,
    LEG_LEFT_3
  };

  /**
   * 
   */
  class SpiderMotor {
    private:
      const SpiderPCA9685 _rightMotor;
      const SpiderPCA9685 _leftMotor;

    public:
      SpiderMotor();

      void init();
      void reposo() const;
      void move  (const SpiderLeg_t leg, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const;
  };
}
#endif
