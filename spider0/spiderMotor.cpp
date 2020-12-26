#include "spiderMotor.h"

// Posicion inicial. Reposo
const int pataIzqDelanteraAngles[3] = {90, 60, 60};
const int pataIzqMediaAngles    [3] = {90, 60, 90};
const int pataIzqTraseraAngles  [3] = {90, 60, 90};

const int pataDerDelanteraAngles[3] = {90, 120,  90};
const int pataDerMediaAngles    [3] = {90, 120,  90};
const int pataDerTraseraAngles  [3] = {90, 120, 100};


// Patas lado IZQUIERDO
const uint8_t addrPCA9685Izquierda                 = 0X40;
const uint8_t pataIzquierdaDelanteraAddr       [3] = {  0,   1,   2};
const uint8_t pataIzquierdaMediaAddr           [3] = {  4,   5,   6};
const uint8_t pataIzquierdaTraseraAddr         [3] = {  8,   9,  10};
const int     pataIzquierdaDelanteraPosition_0 [3] = {110, 110, 110};
const int     pataIzquierdaMediaPosition_0     [3] = {106, 106, 106};
const int     pataIzquierdaTraseraPosition_0   [3] = {110, 110, 110};
const int     pataIzquierdaDelanteraPosition_90[3] = {335, 335, 335};
const int     pataIzquierdaMediaPosition_90    [3] = {324, 324, 324};
const int     pataIzquierdaTraseraPosition_90  [3] = {332, 332, 332};
      
// Patas lado DERECHO
const uint8_t addrPCA9685Derecha                 = 0x41;
const uint8_t pataDerechaDelanteraAddr       [3] = { 15,  14,  13};
const uint8_t pataDerechaMediaAddr           [3] = { 11,  10,   9};
const uint8_t pataDerechaTraseraAddr         [3] = {  7,   6,   5};
const int     pataDerechaDelanteraPosition_0 [3] = {120, 120, 120};
const int     pataDerechaMediaPosition_0     [3] = {110, 110, 110};
const int     pataDerechaTraseraPosition_0   [3] = {120, 120, 120};
const int     pataDerechaDelanteraPosition_90[3] = {335, 335, 335};
const int     pataDerechaMediaPosition_90    [3] = {338, 338, 338};
const int     pataDerechaTraseraPosition_90  [3] = {360, 360, 360};

namespace SPIDER {
  
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  SpiderMotor::SpiderMotor() : _leftMotor (addrPCA9685Izquierda,
                                           pataIzquierdaDelanteraAddr,
                                           pataIzquierdaMediaAddr,
                                           pataIzquierdaTraseraAddr,
                                           pataIzquierdaDelanteraPosition_0,
                                           pataIzquierdaMediaPosition_0,
                                           pataIzquierdaTraseraPosition_0,
                                           pataIzquierdaDelanteraPosition_90,
                                           pataIzquierdaMediaPosition_90,
                                           pataIzquierdaTraseraPosition_90),
                               _rightMotor(addrPCA9685Derecha,
                                           pataDerechaDelanteraAddr,
                                           pataDerechaMediaAddr,
                                           pataDerechaTraseraAddr,
                                           pataDerechaDelanteraPosition_0,
                                           pataDerechaMediaPosition_0,
                                           pataDerechaTraseraPosition_0,
                                           pataDerechaDelanteraPosition_90,
                                           pataDerechaMediaPosition_90,
                                           pataDerechaTraseraPosition_90) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void SpiderMotor::init() {
    _rightMotor.init();
    _leftMotor.init();
  }

  /****************************************************************
   * void leg(const SPIDER_LEG_T leg, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const
   *           
   ****************************************************************/
  void SpiderMotor::leg(const SPIDER_LEG_T leg, const short coxaDelta, const short femurDelta, const short tibiaDelta) const {
    switch (leg)
    {
      case RIGHT_LEG_FRONT:  _rightMotor.leg(LEG_FRONT,  coxaDelta, femurDelta, tibiaDelta); return;
      case RIGHT_LEG_MIDDLE: _rightMotor.leg(LEG_MIDDLE, coxaDelta, femurDelta, tibiaDelta); return;
      case RIGHT_LEG_BACK:   _rightMotor.leg(LEG_BACK,   coxaDelta, femurDelta, tibiaDelta); return;
      case LEFT_LEG_FRONT:   _leftMotor.leg (LEG_FRONT,  coxaDelta, femurDelta, tibiaDelta); return;
      case LEFT_LEG_MIDDLE:  _leftMotor.leg (LEG_MIDDLE, coxaDelta, femurDelta, tibiaDelta); return;
      case LEFT_LEG_BACK:    _leftMotor.leg (LEG_BACK,   coxaDelta, femurDelta, tibiaDelta); return;
    }
  }
  
  /****************************************************************
   * void reposo() const
   *           
   ****************************************************************/
  void SpiderMotor::reposo() const {
    _rightMotor.move(pataDerDelanteraAngles, pataDerMediaAngles, pataDerTraseraAngles);
    _leftMotor.move (pataIzqDelanteraAngles, pataIzqMediaAngles, pataIzqTraseraAngles);
  }
}
