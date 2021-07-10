#ifndef MPU6050_DMP_H
#define MPU6050_DMP_H

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

namespace SPIDER {
  class MPU6050_DMP {
    private:
      // ERROR MIN. CALIBRADO
      const float _A_ERROR[3] = {1076, -807, 1787}; //{560, 770, 1080};
      const float _G_ERROR[3] = {189,    68,  150}; //{200,  25,   90};
      // Factores de conversion
      const float _ACC_SCALE  = 2.0 * 9.81 / 32768.0; // => 1.0/1670.1 convierte la aceleración a metros/s²
      const float _GYRO_SCALE = 250.0 / 32768.0;      // => 1.0/131.0
      const int   _mpuAddress = 0x68;                 // Puede ser 0x68 0 0x69
      
      MPU6050     _mpu;     // default I2C address is 0x68. Specific I2C addresses may be passed as a parameter here. (AD0 low = 0x68, AD0 high = 0x69)
      int16_t     _ax_offset  =  1230;
      int16_t     _ay_offset  =  -769;
      int16_t     _az_offset  =  1791;
      int16_t     _gx_offset  =   250;
      int16_t     _gy_offset  =   108;
      int16_t     _gz_offset  =    20;

      float _sign(float x);
      float _ajusteOffset(int16_t o, int16_t *o_old, float target, float y, float y_old, float paso);
      void  _setOffset();
      void  _meansensors (float *mean_ax, float *mean_ay, float *mean_az, float *mean_gx, float *mean_gy, float *mean_gz);
      void  _calibration ();

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
      void  calculate(double *ax, double *ay, double *az, double *gx, double *gy, double *gz);
      float getTemperatura();
  };
}
#endif
