#include "Spider.h"

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
const uint8_t pataDerechaDelanteraAddr       [3] = {  0,   1,   2};
const uint8_t pataDerechaMediaAddr           [3] = {  4,   5,   6};
const uint8_t pataDerechaTraseraAddr         [3] = {  8,   9,  10};
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
  Spider0::Spider0() : _motor(addrPCA9685Izquierda,
                              pataIzquierdaDelanteraAddr,
                              pataIzquierdaMediaAddr,
                              pataIzquierdaTraseraAddr,
                              pataIzquierdaDelanteraPosition_0,
                              pataIzquierdaMediaPosition_0,
                              pataIzquierdaTraseraPosition_0,
                              pataIzquierdaDelanteraPosition_90,
                              pataIzquierdaMediaPosition_90,
                              pataIzquierdaTraseraPosition_90,
                              addrPCA9685Derecha,
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
  void Spider0::init() {
    _motor.init();
  }

  /****************************************************************
   * void move() const
   ****************************************************************/
  void Spider0::move() const {
    _motor.move();
  }

  /****************************************************************
   * void move(const int pataIzqDelanteraAngles[3],
   *           const int pataIzqMediaAngles[3],
   *           const int pataIzqTraseraAngles[3],
   *           const int pataDerDelanteraAngles[3],
   *           const int pataDerMediaAngles[3],
   *           const int pataDerTraseraAngles[3]) const
   *           
   ****************************************************************/
  void Spider0::move(const int pataIzqDelanteraAngles[3],
                     const int pataIzqMediaAngles    [3],
                     const int pataIzqTraseraAngles  [3],
                     const int pataDerDelanteraAngles[3],
                     const int pataDerMediaAngles    [3],
                     const int pataDerTraseraAngles  [3]) const {
    _motor.move(pataIzqDelanteraAngles, pataIzqMediaAngles, pataIzqTraseraAngles, pataDerDelanteraAngles, pataDerMediaAngles, pataDerTraseraAngles);
  }
}
