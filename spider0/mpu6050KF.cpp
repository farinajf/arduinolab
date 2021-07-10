#include "mpu6050KF.h"

namespace SPIDER {
  /****************************************************************
   * Constructor()
   * 
   ****************************************************************/
  MPU6050_KF::MPU6050_KF() : _mpu() {}

  /****************************************************************
   * void _calculate(double *ax, double *ay, double *az, double *gx, double *gy, double *gz, double *roll, double *pitch)
   * 
   ****************************************************************/
  void MPU6050_KF::_calculate(double *ax, double *ay, double *az, double *gx, double *gy, double *gz, double *roll, double *pitch) {
    _mpu.calculate(ax, ay, az, gx, gy, gz);

    // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
    // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
    // It is then converted from radians to degrees

#ifdef RESTRICT_PITCH // Eq. 25 and 26

    *roll  = atan2(*ay, *az) * RAD_TO_DEG;
    *pitch = atan (-*ax / sqrt((*ay)*(*ay) + (*az)*(*az))) * RAD_TO_DEG;

#else // Eq. 28 and 29

    *roll  = atan (*ay / sqrt((*ax)*(*ax) + (*az)*(*az))) * RAD_TO_DEG;
    *pitch = atan2(-*ax, *az) * RAD_TO_DEG;

#endif

    return;
  }

  /****************************************************************
   * void init()
   ****************************************************************/
  void MPU6050_KF::init() {
    double ax;
    double ay;
    double az;
    double gx;
    double gy;
    double gz;
    double roll;
    double pitch;
    
    _mpu.init();
    delay(100);

    if (MPU_CALIBRATION == true) _mpu.calibrar();
    delay(100);

    _calculate(&ax, &ay, &az, &gx, &gy, &gz, &roll, &pitch);

    _kalmanX.setAngle(roll); // Set starting angle
    _kalmanY.setAngle(pitch);

    _angleX = roll;
    _angleY = pitch;
    
    _timer = micros();
  }

  /****************************************************************
   * void calculate()
   ****************************************************************/
  void MPU6050_KF::calculate() {
    double ax;
    double ay;
    double az;
    double gx;
    double gy;
    double gz;
    double roll;
    double pitch;

    //1.- Obtenemos la nueva observacion
    _calculate(&ax, &ay, &az, &gx, &gy, &gz, &roll, &pitch);

    //2.- Calculamos dt
    double dt = (double) (micros() - _timer) / 1000000;
    _timer = micros();

    //3.-
#ifdef RESTRICT_PITCH

    // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
    if ((roll < -90 && _angleX > 90) || (roll > 90 && _angleX < -90))
    {
      _kalmanX.setAngle(roll);
      _angleX  = roll;
    }
    else _angleX = _kalmanX.filter(roll, gx, dt);

    if (abs(_angleX) > 90) gy = -gy; // Invert rate, so it fits the restriced accelerometer reading
    
    _angleY = _kalmanY.filter(pitch, gy, dt);

#else

    // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
    if ((pitch < -90 && _kalAngleY > 90) || (pitch > 90 && _kalAngleY < -90))
    {
      _kalmanY.setAngle(pitch);
      _kalAngleY  = pitch;
    }
    else _kalAngleY = _kalmanY.filter(pitch, gy, dt); // Calculate the angle using a Kalman filter

    if (abs(_kalAngleY) > 90) gx = -gx; // Invert rate, so it fits the restriced accelerometer reading
  
    _kalAngleX = _kalmanX.filter(roll, gx, dt); // Calculate the angle using a Kalman filter

#endif
  }
}
