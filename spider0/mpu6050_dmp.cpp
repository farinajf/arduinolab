#include "mpu6050_dmp.h"

namespace SPIDER {
  /****************************************************************
   * Constructor()
   * 
   ****************************************************************/
  MPU6050_DMP::MPU6050_DMP() : _mpu(_mpuAddress) {}

  /****************************************************************
   * void _setOffsets(int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz)
   ****************************************************************/
  void MPU6050_DMP::_setOffset() {
    _mpu.setXAccelOffset(_ax_offset);
    _mpu.setYAccelOffset(_ay_offset);
    _mpu.setZAccelOffset(_az_offset);

    _mpu.setXGyroOffset(_gx_offset);
    _mpu.setYGyroOffset(_gy_offset);
    _mpu.setZGyroOffset(_gz_offset);
  }

  /****************************************************************
   * void init()
   ****************************************************************/
  void MPU6050_DMP::init() {
    Wire.begin();

    //1.- COMMENT NEXT LINE IF YOU ARE USING ARDUINO DUE
    TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz). Leonardo measured 250kHz.

    //2.- Initialize device
    _mpu.initialize();

    //3.- Test connection
    Serial.println(_mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));

    //4.- Start
    delay(300);

    //5.- Reset offsets
    this->_setOffset();
  }

  /****************************************************************
   * float getTemperatura()
   ****************************************************************/
  float MPU6050_DMP::getTemperatura() {
    return (((float) _mpu.getTemperature()) / 340.0f) + 36.53f;
  }
}
