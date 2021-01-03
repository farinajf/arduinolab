#include "SpiderPCA9685.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  SpiderPCA9685::SpiderPCA9685(const uint8_t addr,
                               const uint8_t pata1_Addr       [3],
                               const uint8_t pata2_Addr       [3],
                               const uint8_t pata3_Addr       [3],
                               const int     pata1_Position_0 [3],
                               const int     pata2_Position_0 [3],
                               const int     pata3_Position_0 [3],
                               const int     pata1_Position_90[3],
                               const int     pata2_Position_90[3],
                               const int     pata3_Position_90[3]) : _driver(addr),
                                                                     _pata1 (pata1_Addr, pata1_Position_0, pata1_Position_90),
                                                                     _pata2 (pata2_Addr, pata2_Position_0, pata2_Position_90),
                                                                     _pata3 (pata3_Addr, pata3_Position_0, pata3_Position_90) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void SpiderPCA9685::init() {
    _driver.begin();
    _driver.setPWMFreq(_fo);

    _pata1.init();
    _pata2.init();
    _pata3.init();
  }

  /****************************************************************
   * 
   * move(const int pata1_Angles[3], const int pata2_Angles[3], const int pata3_Angles[3]) const
   * 
   * Establece los angulos, en grados (0º - 180º), para cada parte de
   * cada una de las patas.
   * 
   ****************************************************************/
  void SpiderPCA9685::move(const int pata1_Angles[3], const int pata2_Angles[3], const int pata3_Angles[3]) const {
    _pata1.setServoAngles(&_driver, pata1_Angles);
    _pata2.setServoAngles(&_driver, pata2_Angles);
    _pata3.setServoAngles(&_driver, pata3_Angles);
  }

  /****************************************************************
   * 
   * void move(const Leg_t leg, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const
   * 
   ****************************************************************/
  void SpiderPCA9685::move(const Leg_t leg, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const {
    switch (leg)
    {
      case LEG_1: _pata1.setDeltaServoAngles(&_driver, deltaCoxa, deltaFemur, deltaTibia); return;
      case LEG_2: _pata2.setDeltaServoAngles(&_driver, deltaCoxa, deltaFemur, deltaTibia); return;
      case LEG_3: _pata3.setDeltaServoAngles(&_driver, deltaCoxa, deltaFemur, deltaTibia); return;
    }
  }
}
