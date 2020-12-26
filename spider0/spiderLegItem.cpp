#include "spiderLegItem.h"

namespace SPIDER {

  /****************************************************************
   * uint16_t getDuty()
   ****************************************************************/
  uint16_t SpiderLegItem::_getDuty() const {
    const int result = map(_angle, 0, 90, _position_0, _position_90);
    
    return (uint16_t)result;
  }

  /****************************************************************
   * void init()
   ****************************************************************/
  void SpiderLegItem::init() {}

  /****************************************************************
   * void setAngle(const Adafruit_PWMServoDriver driver, const int angle)
   * 
   * angle: valor del angulo para este parte de la pata en grados: 0º - 180º
   * 
   ****************************************************************/
  void SpiderLegItem::setAngle(const Adafruit_PWMServoDriver *driver, const int angle) {
    _angle = angle;
    
    const uint16_t duty = _getDuty();

    Serial.print("setAngle(");Serial.print(_addr);Serial.print(",");Serial.print(duty);Serial.println(")");

    driver->setPWM(_addr, 0, duty);
  }

  /****************************************************************
   * void setDeltaAngle(const Adafruit_PWMServoDriver driver, const short delta)
   * 
   * delta: desplazamiento del angulo
   * 
   ****************************************************************/
  void SpiderLegItem::setDeltaAngle(const Adafruit_PWMServoDriver *driver, const short delta) {
    _angle += delta;
    
    const uint16_t duty = _getDuty();

    Serial.print("setAngle(");Serial.print(_addr);Serial.print(",");Serial.print(duty);Serial.println(")");

    driver->setPWM(_addr, 0, duty);
  }

  /****************************************************************
   * int getAngle()
   * 
   * Devuelve la posicion del Servo en grados: 0º - 180º
   * 
   ****************************************************************/
  int SpiderLegItem::getAngle() const {return _angle;}
}
