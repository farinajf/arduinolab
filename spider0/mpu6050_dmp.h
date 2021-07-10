#ifndef MPU6050_DMP_H
#define MPU6050_DMP_H

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

namespace SPIDER {
  class MPU6050_DMP {
    private:
      const int   _mpuAddress = 0x68; // Puede ser 0x68 0 0x69
      
      MPU6050     _mpu;     // default I2C address is 0x68. Specific I2C addresses may be passed as a parameter here. (AD0 low = 0x68, AD0 high = 0x69)
      int16_t     _ax_offset  =  1230;
      int16_t     _ay_offset  =  -769;
      int16_t     _az_offset  =  1791;
      int16_t     _gx_offset  =   250;
      int16_t     _gy_offset  =   108;
      int16_t     _gz_offset  =    20;

      void  _setOffset();

    public:
      MPU6050_DMP();

      void init();
      void calibrar();

      /****************************************************************
       * void calculate()
       * 
       * Aceleracion en unidades de metros/s².
       * Velocidad angular: º/s
       * 
       ****************************************************************/
      void  calcular(double *ax, double *ay, double *az, double *gx, double *gy, double *gz);
      float getTemperatura();
  };
}
#endif
