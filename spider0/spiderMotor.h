#ifndef SPIDER_MOTOR_H
#define SPIDER_MOTOR_H

#include "pca9685.h"

namespace SPIDER {
  enum SPIDER_LEG_T {
    RIGHT_LEG_FRONT,
    RIGHT_LEG_MIDDLE,
    RIGHT_LEG_BACK,
    LEFT_LEG_FRONT,
    LEFT_LEG_MIDDLE,
    LEFT_LEG_BACK
  };
  
  class SpiderMotor {
    private:
      const PCA9685 _rightMotor;
      const PCA9685 _leftMotor;

    public:
      SpiderMotor();
      void init();

      void reposo() const;
      void leg(const SPIDER_LEG_T leg, const short coxaDelta, const short femurDelta, const short tibiaDelta) const;
  };
}

#endif
