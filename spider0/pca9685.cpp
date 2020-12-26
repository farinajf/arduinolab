#include "pca9685.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  PCA9685::PCA9685(const uint8_t addr,
                   const uint8_t pataDelanteraAddr       [3],
                   const uint8_t pataMediaAddr           [3],
                   const uint8_t pataTraseraAddr         [3],
                   const int     pataDelanteraPosition_0 [3],
                   const int     pataMediaPosition_0     [3],
                   const int     pataTraseraPosition_0   [3],
                   const int     pataDelanteraPosition_90[3],
                   const int     pataMediaPosition_90    [3],
                   const int     pataTraseraPosition_90  [3]) : _driver       (addr),
                                                                _pataDelantera(pataDelanteraAddr, pataDelanteraPosition_0, pataDelanteraPosition_90),
                                                                _pataMedia    (pataMediaAddr,     pataMediaPosition_0,     pataMediaPosition_90),
                                                                _pataTrasera  (pataTraseraAddr,   pataTraseraPosition_0,   pataTraseraPosition_90) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void PCA9685::init() {
    _driver.begin();
    _driver.setPWMFreq(_fo);

    _pataDelantera.init();
    _pataMedia.init();
    _pataTrasera.init();

    Serial.print("PCA9685.init("); Serial.print(_driver.getPWM(0)); Serial.println(")");
  }

  /****************************************************************
   * 
   * leg(const short leg, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const
   * 
   * Establece los angulos, en grados (0º - 180º), para cada parte de
   * cada una de las patas.
   * 
   ****************************************************************/
  void PCA9685::move(const int pataDelanteraAngles[3], const int pataMediaAngles[3], const int pataTraseraAngles[3]) {
    _pataDelantera.setServoAngles(&_driver, pataDelanteraAngles);
    _pataMedia.setServoAngles    (&_driver, pataMediaAngles);
    _pataTrasera.setServoAngles  (&_driver, pataTraseraAngles);
  }

  /****************************************************************
   * 
   * void leg(const LEG_T leg, const short coxaDelta, const short femurDelta, const short tibiaDelta) const
   * 
   ****************************************************************/
  void PCA9685::leg(const LEG_T leg, const short coxaDelta, const short femurDelta, const short tibiaDelta) const {
    switch (leg)
    {
      case LEG_FRONT:  _pataDelantera.setDeltaServoAngles(&_driver, coxaDelta, femurDelta, tibiaDelta); return;
      case LEG_MIDDLE: _pataMedia.setDeltaServoAngles    (&_driver, coxaDelta, femurDelta, tibiaDelta); return;
      case LEG_BACK:   _pataTrasera.setDeltaServoAngles  (&_driver, coxaDelta, femurDelta, tibiaDelta); return;
    }
  }
}
