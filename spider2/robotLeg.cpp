#include "robotLeg.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  RobotLeg::RobotLeg(float x0, float y0) : _x0(x0), _y0(y0) {}


  /****************************************************************
   * void init(const RobotLegItemParam &coxa, const RobotLegItemParam &femur, const RobotLegItemParam &tibia)
   * 
   ****************************************************************/
  void RobotLeg::init(const RobotLegItemParam &coxa,const  RobotLegItemParam &femur, const RobotLegItemParam &tibia) {
    //1.- Coxa, femur y tibia
    _coxa.init (coxa);
    _femur.init(femur);
    _tibia.init(tibia);
  }

  /****************************************************************
   * void getAngles(Point destino, float &alpha, float &beta, float &gamma)
   * 
   * Cinematica inversa:
   *      (alpha, beta, gamma) = H(destino)
   * 
   ****************************************************************/
  void RobotLeg::getAngles(Point destino, float &alpha, float &beta, float &gamma) {
    this -> _getAngles(destino._x, destino._y, destino._z, alpha, beta, gamma);
  }


  /****************************************************************
   * bool checkPoint(Point p)
   * 
   ****************************************************************/
  bool RobotLeg::checkPoint(Point p) {
    Point newPoint;
    float alpha;
    float beta;
    float gamma;

    //1.- Calcular coordenadas angulares
    this -> getAngles(p, alpha, beta, gamma);

    //2.- Comprobar coordenadas angulares
    if (this -> _checkAngles(alpha, beta, gamma) == false) return false;

    //3.- Calcular nueva posicion
    this -> _getPoint(alpha, beta, gamma, newPoint);

    //4.- Devolver resultado
    float result = Point::getDistance(p, newPoint);
    if (result < NEGLIGIBLE_DISTANCE) return true;

    return false;
  }
  

  /****************************************************************
   * void move(Point destino)
   * 
   ****************************************************************/
  void RobotLeg::move(Point destino) {
    _posicionFinal = destino;
    _busy          = true;
  }

  /****************************************************************
   * void moveDirectly(Point destino)
   * 
   * Mueve directamente la pata a esa posicion.
   * 
   ****************************************************************/
  void RobotLeg::moveDirectly(Point destino) {
    float alpha = 0.0;
    float beta  = 0.0;
    float gamma = 0.0;

    //1.- Calcular los angulos para las rotaciones
    this -> getAngles(destino, alpha, beta, gamma);

    //2.- Rotar los servos
    this -> _rotate(alpha, beta, gamma);
  }

  /****************************************************************
   * void shift(Point delta)
   * 
   ****************************************************************/
  void RobotLeg::shift(Point delta) {
    delta = Point(_posicionFinal._x + delta._x,
                  _posicionFinal._y + delta._y,
                  _posicionFinal._z + delta._z);
    
    this -> move(delta);
  }
  

  /****************************************************************
   * void setServos(float alpha, float beta, float gamma)
   * 
   ****************************************************************/
  void RobotLeg::setServos(float servoAlpha, float servoBeta, float servoGamma) {
    //1.- Convertir el angulo del servo en coordenadas angulares
    float alpha = _coxa.getAngle (servoAlpha);
    float beta  = _femur.getAngle(servoBeta);
    float gamma = _tibia.getAngle(servoGamma);

    //2.- Calcular la posicion
    Point destino;
    this -> _getPoint(alpha, beta, gamma, destino);

    //3.- Mover la pata a esa posición
    this -> move(destino);
  }
  

  /****************************************************************
   * void setOffsetEnable(bool x)
   * 
   ****************************************************************/
  void RobotLeg::setOffsetEnable(bool x) {
    _coxa.setOffsetEnable (x);
    _femur.setOffsetEnable(x);
    _tibia.setOffsetEnable(x);
  }
  

  /****************************************************************
   * void update(float speedMultiple)
   * 
   * Actualizar posicion:
   *         _posicionActual   ==>  _posicionFinal
   * 
   ****************************************************************/
  void RobotLeg::update(float speedMultiple) {
    float distance = Point::getDistance(_posicionFinal, _posicionActual);

    float xDist = _posicionFinal._x - _posicionActual._x;
    float yDist = _posicionFinal._y - _posicionActual._y;
    float zDist = _posicionFinal._z - _posicionActual._z;

    float factor = distance / (_stepDistance * speedMultiple);

    float xStep = xDist / factor;
    float yStep = yDist / factor;
    float zStep = zDist / factor;

    Point destino = Point(_posicionActual, xStep, yStep, zStep);

    //Si hay multiples pasos
    if ((distance >= (_stepDistance * speedMultiple)) && (distance >= NEGLIGIBLE_DISTANCE))
    {
      this -> moveDirectly(destino);
      _busy = true;
    }
    else if (_busy == true)
    {
      this -> moveDirectly(_posicionFinal);
      _busy = false;
    }
  }





  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/


  /****************************************************************
   * void _getAngles(float x, float y, float z, float &alpha, float &beta, float &gamma)
   * 
   * Cinematica inversa:
   *      (alpha, beta, gamma) = H(x, y, z)
   * 
   ****************************************************************/
  void RobotLeg::_getAngles(float x, float y, float z, float &alpha, float &beta, float &gamma) {
    float dx = x - _x0;
    float dy = y - _y0;
    float u  = sqrt(dx*dx + dy*dy);
    
    //1.- Angulo COXA
    alpha = atan2(dy, dx);

    //2.- Angulo FEMUR
    float d       = u - RobotShape::L_COXA;
    float im2     = d*d + z*z;
    float im      = sqrt(im2);
    float epsilon = asin(z / im);

    beta = acos((im2 + RobotShape::L_FEMUR * RobotShape::L_FEMUR - RobotShape::L_TIBIA * RobotShape::L_TIBIA) / (2 * im * RobotShape::L_FEMUR)) + epsilon;

    //3.- Angulo TIBIA
    gamma = acos((RobotShape::L_FEMUR * RobotShape::L_FEMUR + RobotShape::L_TIBIA * RobotShape::L_TIBIA - im2) / (2 * RobotShape::L_FEMUR * RobotShape::L_TIBIA));

    //4.- Pasar de radianes a grados
    alpha *= 180/PI;
    beta  *= 180/PI;
    gamma *= 180/PI;
  }

  
  /****************************************************************
   * void _getPoint(float alpha, float beta, float gamma, Point &p)
   * 
   ****************************************************************/
  void RobotLeg::_getPoint(float alpha, float beta, float gamma, Point &p) {
    this -> _getPoint(alpha, beta, gamma, p._x, p._y, p._z);
  }


  /****************************************************************
   * void _getPoint(float alpha, float beta, float gamma, volatile float &x, volatile float &y, volatile float &z)
   * 
   * (x, y, z) = F(alpha, beta, gamma)
   * 
   ****************************************************************/
  void RobotLeg::_getPoint(float alpha, float beta, float gamma, volatile float &x, volatile float &y, volatile float &z) {
    // 1.- Pasar a radianes
    alpha = alpha * PI / 180;
    beta  = beta  * PI / 180;
    gamma = gamma * PI / 180;

    //2.- Calcular distancia IM2
    float im2     = RobotShape::L_FEMUR * RobotShape::L_FEMUR + RobotShape::L_TIBIA * RobotShape::L_TIBIA - 2 * RobotShape::L_FEMUR * RobotShape::L_TIBIA * cos(gamma);
    float im      = sqrt(im2);

    //3.- Angulo epsilon (Th de los cosenos) -> EPSILON = BETA - acos(..)
    float epsilon = beta - acos((RobotShape::L_FEMUR*RobotShape::L_FEMUR + im2 - RobotShape::L_TIBIA*RobotShape::L_TIBIA) / (2 * RobotShape::L_FEMUR * im));

    //4.- u: Proyeccion de la pata sobre el plano X-Y
    float u = RobotShape::L_COXA + im * cos(epsilon);

    //5.- Coordenadas finales de la pata
    x = _x0 + u * cos(alpha);
    y = _y0 + u * sin(alpha);
    z = 1.0 * im * sin(epsilon);
  }

  /****************************************************************
   * bool _checkAngles(float alpha, float beta, float gamma)
   * 
   ****************************************************************/
  bool RobotLeg::_checkAngles(float alpha, float beta, float gamma) {
    if (_coxa.checkAngle (alpha) == false) return false;
    if (_femur.checkAngle(beta)  == false) return false;
    if (_tibia.checkAngle(gamma) == false) return false;

    return true;
  }

  /****************************************************************
   * void _rotate(float alpha, float beta, float gamma)
   * 
   ****************************************************************/
  void RobotLeg::_rotate(float alpha, float beta, float gamma) {
    _tibia.rotate(gamma);
    _femur.rotate(beta);
    _coxa.rotate (alpha);

    Point p;

    this -> _getPoint(alpha, beta, gamma, p);

    _posicionActual = p;

    if (_firstMove == true)
    {
      _firstMove     = false;
      _posicionFinal = p;
    }
  }
}
