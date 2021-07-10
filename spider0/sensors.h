#ifndef SENSORS_H
#define SENSORS_H

#include "voltage.h"
#include "mpu6050_dmp.h"

namespace SPIDER {
  class Sensors {
    private:
      MPU6050_DMP _mpu;
      Voltage     _voltage;

    public:
      Sensors(): _voltage() {}

      void  init();
      void  calculate();
      float getMPUTemperatura() {return _mpu.getTemperatura();}

      bool isBatteryOK() const;
  };
}
#endif
