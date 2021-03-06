#include "SpiderLeg.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  SpiderLeg::SpiderLeg(const uint8_t addrPata[3], const int position_0[3], const int position_90[3]) : _coxa (addrPata[0], position_0[0], position_90[0]),
                                                                                                       _femur(addrPata[1], position_0[1], position_90[1]),
                                                                                                       _tibia(addrPata[2], position_0[2], position_90[2]) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void SpiderLeg::init() {
    _coxa.init ();
    _femur.init();
    _tibia.init();
  }

  /****************************************************************
   * void setServoAngles(const Adafruit_PWMServoDriver driver, const int angles[3])
   * 
   * Establece el nuevo angulo para los servos de cada parte.
   * 
   ****************************************************************/
  void SpiderLeg::setServoAngles(const Adafruit_PWMServoDriver *driver, const int angles[3]) const{
    _coxa.setAngle (driver, angles[0]);
    _femur.setAngle(driver, angles[1]);
    _tibia.setAngle(driver, angles[2]);
  }

  /****************************************************************
   * void setDeltaServoAngles(const Adafruit_PWMServoDriver *driver, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const
   * 
   * Desplazamiento del angulo para los servos de cada parte.
   * 
   * coxaAngle:  valor del angulo para la coxa en grados: 0º - 180º
   * femurAngle: valor del angulo para el femur en grados: 0º - 180º
   * tibiaAngle: valor del angulo para la tibia en grados: 0º - 180º
   * 
   ****************************************************************/
  void SpiderLeg::setDeltaServoAngles(const Adafruit_PWMServoDriver *driver, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const {
    _coxa.setDeltaAngle (driver, deltaCoxa);
    _femur.setDeltaAngle(driver, deltaFemur);
    _tibia.setDeltaAngle(driver, deltaTibia);
  }
}
