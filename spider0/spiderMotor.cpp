#include "spiderMotor.h"

namespace SPIDER {
  
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  SpiderMotor::SpiderMotor(const uint8_t addrPCA9685Izquierda,
                           const uint8_t pataIzquierdaDelanteraAddr       [3],
                           const uint8_t pataIzquierdaMediaAddr           [3],
                           const uint8_t pataIzquierdaTraseraAddr         [3],
                           const int     pataIzquierdaDelanteraPosition_0 [3],
                           const int     pataIzquierdaMediaPosition_0     [3],
                           const int     pataIzquierdaTraseraPosition_0   [3],
                           const int     pataIzquierdaDelanteraPosition_90[3],
                           const int     pataIzquierdaMediaPosition_90    [3],
                           const int     pataIzquierdaTraseraPosition_90  [3],
                           const uint8_t addrPCA9685Derecha,
                           const uint8_t pataDerechaDelanteraAddr         [3],
                           const uint8_t pataDerechaMediaAddr             [3],
                           const uint8_t pataDerechaTraseraAddr           [3],
                           const int     pataDerechaDelanteraPosition_0   [3],
                           const int     pataDerechaMediaPosition_0       [3],
                           const int     pataDerechaTraseraPosition_0     [3],
                           const int     pataDerechaDelanteraPosition_90  [3],
                           const int     pataDerechaMediaPosition_90      [3],
                           const int     pataDerechaTraseraPosition_90    [3]) : _leftMotor (addrPCA9685Izquierda,
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
   * void move() const
   ****************************************************************/
  void SpiderMotor::move() const {
    //TODO
  }

  /****************************************************************
   * void move(const int pataIzqDelanteraAngles[3],
   *           const int pataIzqMediaAngles    [3],
   *           const int pataIzqTraseraAngles  [3],
   *           const int pataDerDelanteraAngles[3],
   *           const int pataDerMediaAngles    [3],
   *           const int pataDerTraseraAngles [3]) const
   *           
   ****************************************************************/
  void SpiderMotor::move(const int pataIzqDelanteraAngles[3],
                         const int pataIzqMediaAngles    [3],
                         const int pataIzqTraseraAngles  [3],
                         const int pataDerDelanteraAngles[3],
                         const int pataDerMediaAngles    [3],
                         const int pataDerTraseraAngles [3]) const {
    _rightMotor.move(pataDerDelanteraAngles, pataDerMediaAngles, pataDerTraseraAngles);
    _leftMotor.move (pataIzqDelanteraAngles, pataIzqMediaAngles, pataIzqTraseraAngles);
  }
}
