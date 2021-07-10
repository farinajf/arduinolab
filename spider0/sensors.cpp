#include "sensors.h"

namespace SPIDER {
  /****************************************************************
   * void init()
   ****************************************************************/
  void Sensors::init() {
    _voltage.init();
    _mpu.init();
  }

  /****************************************************************
   * void calculate()
   ****************************************************************/
  void Sensors::calculate() {
    _voltage.calculate();
  }

  /****************************************************************
   * bool isBatteryOK() const
   ****************************************************************/
  bool Sensors::isBatteryOK() const {
    return _voltage.isVoltageHigh();
  }
}
