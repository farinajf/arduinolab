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
  float Point::getDistance(Point p1, Point p2) {
    float dx = p1._x - p2._x;
    float dy = p1._y - p2._y;
    float dz = p1._z - p2._z;

    float d2 = dx*dx + dy*dy + dz*dz;

    return (d2 < FLOAT_PRECISSION) ? 0.0 : sqrt(d2);
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
   * float getAngulo(float anguloServo) const
   * 
   * Convierte un servo-angulo en un angulo
   * 
   ****************************************************************/
  float RobotLegItem::getAngulo(float anguloServo) const {
    return (_params._sumaResta ? 1 : -1) * (anguloServo - _params._anguloZero);
  }
  

  /****************************************************************
   * void rotateToDirectly(float angulo)
   * 
   * Convierto el angulo natural en un anglulo del servo.
   * 
   ****************************************************************/
  void RobotLegItem::rotateToDirectly(float angulo) {
//Serial.print("RobotLegItem::rotateToDirectly("); Serial.print(angulo); Serial.println(")");
    
    if (this -> _checkAngle(angulo) == false) return;

    float anguloServo = this -> _getServoAngle(angulo);

    while (anguloServo >= 360) anguloServo -= 360;
    while (anguloServo <    0) anguloServo += 360;

    if (anguloServo > 180) return;

//Serial.print("anguloServo(2): "); Serial.println(anguloServo);

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




  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * bool _checkAngle(float angulo)
   * 
   ****************************************************************/
  bool RobotLegItem::_checkAngle(float angulo) {
    while (angulo > _params._anguloMax) angulo -= 360;
    while (angulo < _params._anguloMin) angulo += 360;

    return ((angulo >= _params._anguloMin) && (angulo <= _params._anguloMax)) ? true : false;
  }

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
