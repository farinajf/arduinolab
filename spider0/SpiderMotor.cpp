#include "SpiderMotor.h"

// Patas lado IZQUIERDO
const uint8_t addrPCA9685Izquierda          = 0X40;
const uint8_t pataIzquierda1_Addr       [3] = {  0,   1,   2}; //Delantera
const uint8_t pataIzquierda2_Addr       [3] = {  4,   5,   6}; //Media
const uint8_t pataIzquierda3_Addr       [3] = {  8,   9,  10}; //Trasera
const int     pataIzquierda1_Position_0 [3] = {110, 110, 110};
const int     pataIzquierda2_Position_0 [3] = {106, 106, 106};
const int     pataIzquierda3_Position_0 [3] = {110, 110, 110};
const int     pataIzquierda1_Position_90[3] = {335, 335, 335};
const int     pataIzquierda2_Position_90[3] = {324, 324, 324};
const int     pataIzquierda3_Position_90[3] = {332, 332, 332};

// Patas lado DERECHO
const uint8_t addrPCA9685Derecha          = 0x41;
const uint8_t pataDerecha1_Addr       [3] = { 15,  14,  13};
const uint8_t pataDerecha2_Addr       [3] = { 11,  10,   9};
const uint8_t pataDerecha3_Addr       [3] = {  7,   6,   5};
const int     pataDerecha1_Position_0 [3] = {120, 120, 120};
const int     pataDerecha2_Position_0 [3] = {110, 110, 110};
const int     pataDerecha3_Position_0 [3] = {120, 120, 120};
const int     pataDerecha1_Position_90[3] = {335, 335, 335};
const int     pataDerecha2_Position_90[3] = {338, 338, 338};
const int     pataDerecha3_Position_90[3] = {360, 360, 360};

// Posicion inicial. Reposo
const int pataIzq1_Angles[3] = {90, 60, 60};
const int pataIzq2_Angles[3] = {90, 60, 90};
const int pataIzq3_Angles[3] = {90, 60, 90};

const int pataDer1_Angles[3] = {90, 120,  90};
const int pataDer2_Angles[3] = {90, 120,  90};
const int pataDer3_Angles[3] = {90, 120, 100};

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  SpiderMotor::SpiderMotor() : _leftMotor (addrPCA9685Izquierda,
                                           pataIzquierda1_Addr,
                                           pataIzquierda2_Addr,
                                           pataIzquierda3_Addr,
                                           pataIzquierda1_Position_0,
                                           pataIzquierda2_Position_0,
                                           pataIzquierda3_Position_0,
                                           pataIzquierda1_Position_90,
                                           pataIzquierda2_Position_90,
                                           pataIzquierda3_Position_90),
                               _rightMotor(addrPCA9685Derecha,
                                           pataDerecha1_Addr,
                                           pataDerecha2_Addr,
                                           pataDerecha3_Addr,
                                           pataDerecha1_Position_0,
                                           pataDerecha2_Position_0,
                                           pataDerecha3_Position_0,
                                           pataDerecha1_Position_90,
                                           pataDerecha2_Position_90,
                                           pataDerecha3_Position_90) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void SpiderMotor::init() {
    _rightMotor.init();
    _leftMotor.init();
  }

  /****************************************************************
   * void reposo() const
   *           
   ****************************************************************/
  void SpiderMotor::reposo() const {
    _rightMotor.move(pataDer1_Angles, pataDer2_Angles, pataDer3_Angles);
    _leftMotor.move (pataIzq1_Angles, pataIzq2_Angles, pataIzq3_Angles);
  }

  /****************************************************************
   * void move(const SpiderLeg_t leg, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const
   *           
   ****************************************************************/
  void SpiderMotor::move(const SpiderLeg_t leg, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const {
    switch (leg)
    {
      case LEG_RIGHT_1: _rightMotor.move(LEG_1, deltaCoxa, deltaFemur, deltaTibia); return;
      case LEG_RIGHT_2: _rightMotor.move(LEG_2, deltaCoxa, deltaFemur, deltaTibia); return;
      case LEG_RIGHT_3: _rightMotor.move(LEG_3, deltaCoxa, deltaFemur, deltaTibia); return;

      case LEG_LEFT_1:  _leftMotor.move (LEG_1, deltaCoxa, deltaFemur, deltaTibia); return;
      case LEG_LEFT_2:  _leftMotor.move (LEG_2, deltaCoxa, deltaFemur, deltaTibia); return;
      case LEG_LEFT_3:  _leftMotor.move (LEG_3, deltaCoxa, deltaFemur, deltaTibia); return;
    }
  }
}
