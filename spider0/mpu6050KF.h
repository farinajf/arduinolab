#ifndef MPU6050_KF_H
#define MPU6050_KF_H

#include "globals.h"
#include "mpu6050_dmp.h"
#include "KalmanFilter.h"

#define RESTRICT_PITCH // Comment out to restrict roll to ±90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf

namespace SPIDER {
  class MPU6050_KF {
    private:
      KalmanFilter _kalmanX;
      KalmanFilter _kalmanY;
      MPU6050_DMP  _mpu;
      uint32_t     _timer;
      double       _angleX;
      double       _angleY;

      void _calculate(double *ax, double *ay, double *az, double *gx, double *gy, double *gz, double *roll, double *pitch);
      void _printData(double roll, double pitch);

    public:
      MPU6050_KF();

      void   init();
      void   calculate();
      float  getTemperatura() const {return _mpu.getTemperatura();}
      double getAngleX()      const {return _angleX;}
      double getAngleY()      const {return _angleY;}
  };
}

#endif
