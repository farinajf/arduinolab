#include "servoDriver.h"

namespace SPIDER {

  /****************************************************************
   * 
   * Constructor(const uint8_t addr)
   * 
   ****************************************************************/
  ServoDriver::ServoDriver(const uint8_t addr) : _driver(addr) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void ServoDriver::init() {
    _driver.begin();
    _driver.setPWMFreq(_fo);
  }

  /****************************************************************
   * void rotateTo(uint8_t addr, short servoAngle, short position_0, short position_90)
   * 
   ****************************************************************/
  void ServoDriver::rotateTo(uint8_t addr, short servoAngle, short position_0, short position_90) {
    const uint16_t duty = _getDuty(servoAngle, position_0, position_90);
    
    _driver.setPWM(addr, 0, duty);
  }






  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * uint16_t _getDuty(short servoAngle, short position_0, short position_90)
   * 
   ****************************************************************/
  uint16_t ServoDriver::_getDuty(short servoAngle, short position_0, short position_90) {
    const int result = map((int) servoAngle, 0, 90, (int) position_0, (int) position_90);
    
    return (uint16_t) result;
  }
}
