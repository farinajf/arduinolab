#include "robotLeg.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  RobotLeg::RobotLeg(const uint8_t addr[3],
                     const short   position_0[3],
                     const short   position_90[3],
                     const float   x0,
                     const float   y0,
                     const short   minAngle[3],
                     const short   maxAngle[3],
                     const short   zeroAngle[3],
                     const bool    jointDir[3]) : _coxa (addr[0], position_0[0], position_90[0], minAngle[0], maxAngle[0], zeroAngle[0], jointDir[0]),
                                                  _femur(addr[1], position_0[1], position_90[1], minAngle[1], maxAngle[1], zeroAngle[1], jointDir[1]),
                                                  _tibia(addr[2], position_0[2], position_90[2], minAngle[2], maxAngle[2], zeroAngle[2], jointDir[2]),
                                                  _x0(x0),
                                                  _y0(y0) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void RobotLeg::init() {
    _coxa.init();
    _femur.init();
    _tibia.init();
  }

  /****************************************************************
   * void calculateAngle(Point &point, float &alpha, float &beta, float &gamma)
   * 
   ****************************************************************/
  void RobotLeg::calculateAngle(Point &point, float &alpha, float &beta, float &gamma) {
    this -> _calculateAngle(point._x, point._y, point._z, alpha, beta, gamma);
  }

  /****************************************************************
   * void checkPoint(Point &p)
   * 
   ****************************************************************/
  bool RobotLeg::checkPoint(Point &p) {
    Point pointNew;
    float alpha;
    float beta;
    float gamma;
    
    this -> calculateAngle(p, alpha, beta, gamma);
    
    if (this -> _checkAngle(alpha, beta, gamma) == true)
    {
      this -> _calculatePoint(alpha, beta, gamma, pointNew);
      if (Point::getDistance(p, pointNew) < ROBOT_LEG_NEGLIGIBLE_DISTANCE) return true;
    }

    return false;
  }

  /****************************************************************
   * void moveTo(Point p)
   ****************************************************************/
  void RobotLeg::moveTo(Point p) {
    _pointGoal = p;
    _isBusy    = true;
  }

  /****************************************************************
   * void moveToDirectly(Point p)
   ****************************************************************/
  void RobotLeg::moveToDirectly(Point p) {
    float alpha;
    float beta;
    float gamma;
    
    this -> calculateAngle(p, alpha, beta, gamma);
    
    this -> _rotateToDirectly(alpha, beta, gamma);
  }


  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/


  /****************************************************************
   * void _calculateAngle(float x, float y, float z, float &alpha, float &beta, float &gamma)
   * 
   * OJO: Punto(x, y, z) -> Angulos alpha, beta y gamma
   * 
   ****************************************************************/
  void RobotLeg::_calculateAngle(float x, float y, float z, float &alpha, float &beta, float &gamma) {
    float dx = x - _x0;
    float dy = y - _y0;
    float d  = sqrt(pow(dx, 2) + pow(dy, 2));

    //1.- Angulo COXA
    alpha = atan2(dy, dx);

    //2.- Angulo Femur
    float im2 = pow(z, 2) + pow(d - L_COXA, 2);
    float q1  = acos((L_FEMUR*L_FEMUR + im2 - L_TIBIA*L_TIBIA) / (2 * L_FEMUR * sqrt(im2)));
    float q2  = atan2(z, (d - L_COXA));

    beta = q1 + q2;

    //3.- Angulo Tibia
    gamma = acos((L_FEMUR*L_FEMUR + L_TIBIA*L_TIBIA - im2) / (2 * L_FEMUR * L_TIBIA));
    

    //4.- Radian -> Angle
    alpha *= 180/PI;
    beta  *= 180/PI;
    gamma *= 180/PI;
  }

  /****************************************************************
   * void _calculatePoint(float alpha, float beta, float gamma, Point &point)
   * 
   ****************************************************************/
  void RobotLeg::_calculatePoint(float alpha, float beta, float gamma, Point &point) {
    float x;
    float y;
    float z;
    
    this -> _calculatePoint(alpha, beta, gamma, x, y, z);

    point._x = x;
    point._y = y;
    point._z = z;
  }

  /****************************************************************
   * void _calculatePoint(float alpha, float beta, float gamma, float x, float y, float z)
   * 
   * OJO: Angulos -> Punto (x, y, z)
   * 
   ****************************************************************/
  void RobotLeg::_calculatePoint(float alpha, float beta, float gamma, float &x, float &y, float &z) {
    // grados -> radianes
    alpha = alpha * PI / 180;
    beta  = beta  * PI / 180;
    gamma = gamma * PI / 180;

    float im2     = L_TIBIA*L_TIBIA + L_FEMUR*L_FEMUR - 2*L_TIBIA*L_FEMUR*cos(gamma);
    float im      = sqrt(im2);
    float epsilon = acos((im2 + L_FEMUR*L_FEMUR - L_TIBIA*L_TIBIA) / (2*L_FEMUR*im)) - beta;

    
    float u = im * cos(epsilon) + L_COXA;
    float v = im * sin(epsilon);

    x = _x0 + u * cos(alpha);
    y = _y0 + u * sin(alpha);

    z = -v;
  }

  /****************************************************************
   * bool _checkAngle(float alpha, float beta, float gamma)
   * 
   ****************************************************************/
  bool RobotLeg::_checkAngle(float alpha, float beta, float gamma) {
    return (_coxa.checkJointAngle(alpha) && _femur.checkJointAngle(beta) &&_tibia.checkJointAngle(gamma)) ? true : false;
  }

  /****************************************************************
   * void _rotateToDirectly(float alpha, float beta, float gamma)
   * 
   ****************************************************************/
  void RobotLeg::_rotateToDirectly(float alpha, float beta, float gamma) {
    _tibia.rotateToDirectly(_driver, gamma);
    _femur.rotateToDirectly(_driver, beta);
    _coxa.rotateToDirectly (_driver, alpha);

    Point point;
    this -> _calculatePoint(alpha, beta, gamma, point);
    
    if (_firstMove == true)
    {
      _firstMove = false;
      _pointGoal = point;
    }

    _pointNow = point;
  }
}
