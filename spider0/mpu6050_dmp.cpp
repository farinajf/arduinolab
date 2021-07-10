#include "mpu6050_dmp.h"

namespace SPIDER {
  /****************************************************************
   * Constructor()
   * 
   ****************************************************************/
  MPU6050_DMP::MPU6050_DMP() : _mpu(_mpuAddress) {}

  /****************************************************************
   * float _sign(float x)
   ****************************************************************/
  float MPU6050_DMP::_sign(float x) {
    return (x < 0.0) ? -1.0f : 1.0f;
  }
  
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
   * void _meansensors(float *mean_ax, float *mean_ay, float *mean_az, float *mean_gx, float *mean_gy, float *mean_gz)
   * 
   ****************************************************************/
  void MPU6050_DMP::_meansensors(float *mean_ax, float *mean_ay, float *mean_az, float *mean_gx, float *mean_gy, float *mean_gz) {
    int16_t ax, ay, az, gx, gy, gz;
    float   buff_ax = 0.0;
    float   buff_ay = 0.0;
    float   buff_az = 0.0;
    float   buff_gx = 0.0;
    float   buff_gy = 0.0;
    float   buff_gz = 0.0;
    int     N       = 1000;

    //1.- Primeras 100 medidas descartadas
    for (int i = 0; i < 100; i++)
    {
      _mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
          
      delay(5); //Needed so we don't get repeated measures
    }

    //2.- Calculamos 1000 medidas
    for (int i = 0; i < N; i++)
    {
      _mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

      buff_ax += ax;
      buff_ay += ay;
      buff_az += az;

      buff_gx += gx;
      buff_gy += gy;
      buff_gz += gz;

      delay(5); //Needed so we don't get repeated measures
    }

    //3.- Calculamos el valor medio sobre 1000 medidas
    *mean_ax = buff_ax / N;
    *mean_ay = buff_ay / N;
    *mean_az = buff_az / N;

    *mean_gx = buff_gx / N;
    *mean_gy = buff_gy / N;
    *mean_gz = buff_gz / N;
  }

  /****************************************************************
   * float _ajusteOffset(int16_t o, int16_t *o_old, float target, float y, float y_old, float paso)
   * 
   * new_offset = offset + paso * (target - y) * sign(y - y_old)/sign(offset - offset_old)
   * 
   ****************************************************************/
  float MPU6050_DMP::_ajusteOffset(int16_t o, int16_t *o_old, float target, float y, float y_old, float paso) {
    float signo = _sign(y - y_old) / _sign((float) (o - *o_old));

    float result = ((float) o) + paso * (target - y) * signo;
    *o_old = o;
    
    return result;
  }

  /****************************************************************
   * void _calibration()
   * 
   ****************************************************************/
  void MPU6050_DMP::_calibration() {
    int16_t ax_offset_old = _ax_offset;
    int16_t ay_offset_old = _ay_offset;
    int16_t az_offset_old = _az_offset;
    int16_t gx_offset_old = _gx_offset;
    int16_t gy_offset_old = _gy_offset;
    int16_t gz_offset_old = _gz_offset;
    int16_t aux;
    float   a_paso        = 0.1;
    float   g_paso        = 0.5;
    float   mean_ax_old   = 0.0f;
    float   mean_ay_old   = 0.0f;
    float   mean_az_old   = 0.0f;
    float   mean_gx_old   = 0.0f;
    float   mean_gy_old   = 0.0f;
    float   mean_gz_old   = 0.0f;
    float   mean_ax       = 0.0f;
    float   mean_ay       = 0.0f;
    float   mean_az       = 0.0f;
    float   mean_gx       = 0.0f;
    float   mean_gy       = 0.0f;
    float   mean_gz       = 0.0f;
    int     finish        = 0;
    int     n             = 0;
    
    Serial.println("\nLeyendo sensores la primera vez...");

    _meansensors(&mean_ax, &mean_ay, &mean_az, &mean_gx, &mean_gy, &mean_gz);

    mean_ax_old = mean_ax;
    mean_ay_old = mean_ay;
    mean_az_old = mean_az;
    mean_gx_old = mean_gx;
    mean_gy_old = mean_gy;
    mean_gz_old = mean_gz;
    
    _ax_offset = _ajusteOffset(_ax_offset, &ax_offset_old,     0.0f, mean_ax, mean_ax_old, a_paso);
    _ay_offset = _ajusteOffset(_ay_offset, &ay_offset_old,     0.0f, mean_ay, mean_ay_old, a_paso);
    _az_offset = _ajusteOffset(_az_offset, &az_offset_old, 16384.0f, mean_az, mean_az_old, a_paso);
    _gx_offset = _ajusteOffset(_gx_offset, &gx_offset_old,     0.0f, mean_gx, mean_gx_old, g_paso);
    _gy_offset = _ajusteOffset(_gy_offset, &gy_offset_old,     0.0f, mean_gy, mean_gy_old, g_paso);
    _gz_offset = _ajusteOffset(_gz_offset, &gz_offset_old,     0.0f, mean_gz, mean_gz_old, g_paso);
    
    delay(100);

    while ((finish < 6) && (n++ <= 20))
    {
      finish = 0;

      //1.- Set offset
      this->_setOffset();

      //2.- Recalculate error
      mean_ax_old = mean_ax;
      mean_ay_old = mean_ay;
      mean_az_old = mean_az;
      mean_gx_old = mean_gx;
      mean_gy_old = mean_gy;
      mean_gz_old = mean_gz;
      
      this->_meansensors(&mean_ax, &mean_ay, &mean_az, &mean_gx, &mean_gy, &mean_gz);

      Serial.println("");
      Serial.print(mean_ax);
      Serial.print("(");Serial.print(_ax_offset);Serial.print(")");
      Serial.print(" \t");
      Serial.print(mean_ay);
      Serial.print("(");Serial.print(_ay_offset);Serial.print(")");
      Serial.print(" \t");
      Serial.print(16384 - mean_az);
      Serial.print("(");Serial.print(_az_offset);Serial.print(")");
      Serial.print(" \t");
      Serial.print(mean_gx);
      Serial.print("(");Serial.print(_gx_offset);Serial.print(")");
      Serial.print(" \t");
      Serial.print(mean_gy);
      Serial.print("(");Serial.print(_gy_offset);Serial.print(")");
      Serial.print(" \t");
      Serial.print(mean_gz);
      Serial.print("(");Serial.print(_gz_offset);Serial.print(")");
      Serial.print(" \t | ");
      Serial.print(a_paso, 5);
      Serial.print(" \t");
      Serial.print(g_paso, 5);
      Serial.print(" \t|");
      Serial.println((_mpu.getTemperature()/340) + 36.53);

      if (abs(mean_ax)         <= _A_ERROR[0]) finish++;
      if (abs(mean_ay)         <= _A_ERROR[1]) finish++;
      if (abs(16384 - mean_az) <= _A_ERROR[2]) finish++;
      if (abs(mean_gx)         <= _G_ERROR[0]) finish++;
      if (abs(mean_gy)         <= _G_ERROR[1]) finish++;
      if (abs(mean_gz)         <= _G_ERROR[2]) finish++;

      _ax_offset = _ajusteOffset(_ax_offset, &ax_offset_old,     0.0f, mean_ax, mean_ax_old, a_paso);
      _ay_offset = _ajusteOffset(_ay_offset, &ay_offset_old,     0.0f, mean_ay, mean_ay_old, a_paso);
      _az_offset = _ajusteOffset(_az_offset, &az_offset_old, 16384.0f, mean_az, mean_az_old, a_paso);
      _gx_offset = _ajusteOffset(_gx_offset, &gx_offset_old,     0.0f, mean_gx, mean_gx_old, g_paso);
      _gy_offset = _ajusteOffset(_gy_offset, &gy_offset_old,     0.0f, mean_gy, mean_gy_old, g_paso);
      _gz_offset = _ajusteOffset(_gz_offset, &gz_offset_old,     0.0f, mean_gz, mean_gz_old, g_paso);

      a_paso = (a_paso > 0.001) ? a_paso * 0.9 : a_paso;
      g_paso = (g_paso > 0.01)  ? g_paso * 0.9 : g_paso;
    }
  }

  /****************************************************************
   * void calibrar()
   ****************************************************************/
  void MPU6050_DMP::calibrar() {
    float mean_ax = 0.0f;
    float mean_ay = 0.0f;
    float mean_az = 0.0f;
    float mean_gx = 0.0f;
    float mean_gy = 0.0f;
    float mean_gz = 0.0f;

    //1.- Calibrate
    _calibration();
    delay(1000);

    //2.- Calculate error
    _meansensors(&mean_ax, &mean_ay, &mean_az, &mean_gx, &mean_gy, &mean_gz);

    Serial.println("\nFINISHED!");
    Serial.print("\nSensor readings with offsets:\t");
    Serial.print(mean_ax); 
    Serial.print("\t");
    Serial.print(mean_ay); 
    Serial.print("\t");
    Serial.print(mean_az); 
    Serial.print("\t");
    Serial.print(mean_gx); 
    Serial.print("\t");
    Serial.print(mean_gy); 
    Serial.print("\t");
    Serial.println(mean_gz);
    Serial.print("Your offsets:\t");
    Serial.print(_ax_offset); 
    Serial.print("\t");
    Serial.print(_ay_offset); 
    Serial.print("\t");
    Serial.print(_az_offset); 
    Serial.print("\t");
    Serial.print(_gx_offset); 
    Serial.print("\t");
    Serial.print(_gy_offset); 
    Serial.print("\t");
    Serial.println(_gz_offset); 

    Serial.println("\nData is printed as: acelX acelY acelZ giroX giroY giroZ");
    Serial.println("Check that your sensor readings are close to 0 0 16384 0 0 0");
    Serial.println("If calibration was succesful write down your offsets so you can set them in your projects using something similar to mpu.setXAccelOffset(youroffset)");
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
   * void calculate()
   * 
   * Aceleracion en unidades de metros/s².
   * Velocidad angular: º/s
   * 
   ****************************************************************/
  void MPU6050_DMP::calculate(double *ax, double *ay, double *az, double *gx, double *gy, double *gz) {
    int16_t ax_aux, ay_aux, az_aux, gx_aux, gy_aux, gz_aux;

    _mpu.getMotion6(&ax_aux, &ay_aux, &az_aux, &gx_aux, &gy_aux, &gz_aux);

    *ax = ax_aux * _ACC_SCALE;
    *ay = ay_aux * _ACC_SCALE;
    *az = az_aux * _ACC_SCALE;
    *gx = gx_aux * _GYRO_SCALE;
    *gy = gy_aux * _GYRO_SCALE;
    *gz = gz_aux * _GYRO_SCALE;
  }

  /****************************************************************
   * float getTemperatura()
   ****************************************************************/
  float MPU6050_DMP::getTemperatura() {
    return (((float) _mpu.getTemperature()) / 340.0f) + 36.53f;
  }
}
