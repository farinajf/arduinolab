#ifndef SENSORS_H
#define SENSORS_H

#include "voltage.h"
#include "mpu6050KF.h"

namespace SPIDER {
  class Sensors {
    private:
      MPU6050_KF _mpu;
      Voltage    _voltage;

    public:
      Sensors(): _voltage() {}

      void   init();
      void   calculate();
      float  getMPUTemperatura() const {return _mpu.getTemperatura();}
      double getMPUAngleX()      const {return _mpu.getAngleX();}
      double getMPUAngleY()      const {return _mpu.getAngleY();}

      bool isBatteryOK() const;
  };
}
#endif
