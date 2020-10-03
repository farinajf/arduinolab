#ifndef SPIDER_MOTOR_H
#define SPIDER_MOTOR_H

#include "pca9685.h"

namespace SPIDER {
  class SpiderMotor {
    private:
      const PCA9685 _rightMotor;
      const PCA9685 _leftMotor;

    public:
      SpiderMotor(const uint8_t addrPCA9685Izquierda,
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
                  const int     pataDerechaTraseraPosition_90    [3]);
      void init();

      void move() const;
      void move(const int pataIzqDelanteraAngles[3],
                const int pataIzqMediaAngles    [3],
                const int pataIzqTraseraAngles  [3],
                const int pataDerDelanteraAngles[3],
                const int pataDerMediaAngles    [3],
                const int pataDerTraseraAngles [3]) const;
  };
}

#endif
