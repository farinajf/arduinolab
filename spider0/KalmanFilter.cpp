#include "KalmanFilter.h"

namespace SPIDER {

  KalmanFilter::KalmanFilter() {
    this->_angle = 0.0f;
    this->_bias  = 0.0f;
    
    this->_P[0][0] = 0.0f;
    this->_P[0][1] = 0.0f;
    this->_P[1][0] = 0.0f;
    this->_P[1][1] = 0.0f;
  }
  
  /****************************************************************
   * void KalmanFilter(double newAngle, double newRate, float dt, float Q1_angle, float Q1_bias, float R)
   * 
   *    - newAngle: observacion en el instante k
   *    - newRate:  velocidad angular en el instane k
   *    - dt:       intervalo de tiempo entre medidas
   *    - Q1_angle: varianza del ruido asociado a la primera coordenada del vector estado.
   *    - Q1_bias:  varianza del ruido asociado a la segunda coordenada del vector estado.
   *    - Q2:       varianza del ruido en la observacion
   * 
   * Observacion: z[k] = |newAngle|
   * Input:       u[k] = |newRate |
   * 
   * F = |1 -dt|    B = | dt|   H = |1 0|
   *     |0   1]        |  0|
   * 
   * Q1 = |Q1_angle          0|
   *      |       0    Q1_bias|
   * 
   * 
   * 
   * http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/
   * 
   ****************************************************************/
  float KalmanFilter::filter(double newAngle, double newRate, float dt, float Q1_angle, float Q1_bias, float Q2) {
    //1.- x[k|k-1] = F*x[k-1|k-1] + B*u[k]
    this->_angle += dt*(newRate - this->_bias);
    this->_bias  += 0;

    //2.- State-error correlation matrix: P[k|k-1] = F*P[k-1|k-1]*F' + Q1[k]
    this->_P[0][0] += dt * (dt*_P[1][1] - _P[0][1] - _P[1][0] + Q1_angle);
    this->_P[0][1] -= dt * _P[1][1];
    this->_P[1][0] -= dt * _P[1][1];
    this->_P[1][1] += dt * Q1_bias;

    //3.- Innovation: y[k] = newAngle - H*x[k|k-1]
    double innovation = newAngle - this->_angle;

    //4.- Correlation matrix of innovation process: S[k] = H*P[k|k-1]*C' + Q2
    float S = _P[0][0] + Q2;

    //5.- Kalman gain: G = (P[k|k-1]*C')/s
    double G0 = _P[0][0] / S;
    double G1 = _P[1][0] / S;

    //6.- Actualizacion del estado con la nueva observacion
    this->_angle += G0 * innovation;
    this->_bias  += G1 * innovation;

    //7.- P[k|k] = (I - G*H)*P[k|k-1]
    float P00_aux = _P[0][0];
    float P01_aux = _P[0][1];

    this->_P[0][0] -= G0 * P00_aux;
    this->_P[0][1] -= G0 * P01_aux;
    this->_P[1][0] -= G1 * P00_aux;
    this->_P[1][1] -= G1 * P01_aux;

    return this->_angle;
  }

  /****************************************************************
   * void KalmanFilter(double newAngle, double newRate, float dt)
   * 
   ****************************************************************/
  float KalmanFilter::filter(double newAngle, double newRate, float dt) {
    return filter(newAngle, newRate, dt, 0.001, 0.003, 0.003);
  }
}
