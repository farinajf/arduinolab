#if defined(ARDUINO_AVR_MEGA2560)

#include "robotLegItem.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Point::Point() {}

  Point::Point(float x, float y, float z) : _x(x), _y(y), _z(z) {}

  Point::Point(Point p, float x, float y, float z) : _x(p._x + x), _y(p._y + y), _z(p._z + z) {}

  /****************************************************************
   * static float getDistance(Point p1, Point p2)
   ****************************************************************/
  static float Point::getDistance(Point p1, Point p2) {
    float dx = p1._x - p2._x;
    float dy = p1._y - p2._y;
    float dz = p1._z - p2._z;

    float d2 = dx*dx + dy*dy + dz*dz;

    return (d2 < FLOAT_PRECISSION) ? 0.0 : sqrt(d2);
  }

  /****************************************************************
   * float norma2()
   * 
   * result = sqrt(x*x + y*y + z*z)
   * 
   ****************************************************************/
  float Point::norma2() {
    float result = _x*_x + _y*_y + _z*_z;

    return sqrt(result);
  }






  
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  RobotLegItem::RobotLegItem() {}

  int RobotLegItem::FIRST_ROTATE_DELAY = 0;

  /****************************************************************
   * void init(const RobotLegItemParam &params)
   * 
   ****************************************************************/
  void RobotLegItem::init(const RobotLegItemParam params) {
    _params._servoPin      = params._servoPin;
    _params._anguloZero    = params._anguloZero;
    _params._anguloMin     = params._anguloMin;
    _params._anguloMax     = params._anguloMax;
    _params._sumaResta     = params._sumaResta;
    _params._offsetAddress = params._offsetAddress;

    int offsetInt = EEPROM.read(_params._offsetAddress) * 256 + EEPROM.read(_params._offsetAddress + 1);
    offsetInt = offsetInt / 2 * ((offsetInt % 2) ? 1 : -1);

    this -> _offset   = ((float) offsetInt) * 0.01;
  }

  /****************************************************************
   * bool checkAngle(float angulo)
   * 
   ****************************************************************/
  bool RobotLegItem::checkAngle(float angulo) {
    while (angulo > _params._anguloMax) angulo -= 360;
    while (angulo < _params._anguloMin) angulo += 360;

    return ((angulo >= _params._anguloMin) && (angulo <= _params._anguloMax)) ? true : false;
  }


  /****************************************************************
   * float getAngle(float anguloServo)
   * 
   * Convierte un servo-angulo en un angulo
   * 
   ****************************************************************/
  float RobotLegItem::getAngle(float anguloServo) {
    return (_offsetEnable) ? (_params._sumaResta ? 1 : -1) * (anguloServo - _params._anguloZero) - _offset :
                             (_params._sumaResta ? 1 : -1) * (anguloServo - _params._anguloZero);
  }
  

  /****************************************************************
   * void rotate(float angulo)
   * 
   * Convierto el angulo natural en un anglulo del servo.
   * 
   ****************************************************************/
  void RobotLegItem::rotate(float angulo) {
    
    if (this -> checkAngle(angulo) == false) return;

    float anguloServo = this -> _getServoAngle(angulo);

    while (anguloServo >= 360) anguloServo -= 360;
    while (anguloServo <    0) anguloServo += 360;

    if (anguloServo > 180) return;

    if (_firstRotate == true)
    {
      _firstRotate = false;
      _servo.attach(_params._servoPin);
      _servo.write (anguloServo);
      delay(FIRST_ROTATE_DELAY);
    }
    else
    {
      _servo.write(anguloServo);
    }

    _angulo      = angulo;
    _anguloServo = anguloServo;
  }

  /****************************************************************
   * void setOffset(float offset)
   * 
   ****************************************************************/
  void RobotLegItem::setOffset(float offset) {
    while (offset >  180) offset -= 360;
    while (offset < -180) offset += 360;

    int offsetInt = offset * 100;
    offsetInt = abs(offsetInt) * 2 + ((offset > 0) ? 1 : 0);

    if (offsetInt < 0 || offsetInt > 65535) return;

    EEPROM.write(_params._offsetAddress,     offsetInt / 256);
    EEPROM.write(_params._offsetAddress + 1, offsetInt % 256);

    _offset = offset;
  }




  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * float _getServoAngle(float angulo)
   * 
   * Convierte un angulo en un servo-angulo
   * 
   ****************************************************************/
  float RobotLegItem::_getServoAngle(float angulo) {
    return (_offsetEnable) ? _params._anguloZero + (_params._sumaResta ? 1 : -1) * (angulo + _offset) :
                             _params._anguloZero + (_params._sumaResta ? 1 : -1) * angulo;
  }
}

#endif
