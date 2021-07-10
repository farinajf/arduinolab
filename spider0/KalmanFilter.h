#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/
// https://github.com/TKJElectronics/KalmanFilter/blob/a09adafbcd06510c44805f1b3ee5042f9482cc16/examples/MPU6050/MPU6050.ino

namespace SPIDER {
  /**
   * x[k] = F*x[k-1] + B*u[k] + v1[k]
   * 
   * Estado:      x[k] = | _angle | 
   *                     | _bias  |
   *                     
   * Observacion: z[k] = |newAngle|
   * Input:       u[k] = |newAngularRate |
   * 
   * F = |1 -dt|    B = | dt|   H = |1 0|
   *     |0   1]        |  0|
   * 
   * v1[k] - N(0, Q1)
   * Q1 = |Q1_angle          0|
   *      |       0    Q1_bias|
   * 
   * 
   * 
   * http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/
   * 
   ****************************************************************/
  class KalmanFilter {
    private:
      float _angle = 0.0f;
      float _bias  = 0.0f;
      float _P[2][2];

    public:
      KalmanFilter();
      
      float getAngle() const {return this->_angle;}
      float getBias()  const {return this->_bias;}
      
      void  setAngle(float x) {this->_angle = x;}
      
      float filter(double newAngle, double newRate, float dt);
      float filter(double newAngle, double newRate, float dt, float Q1_angle, float Q1_bias, float Q2);
  };
}

#endif
