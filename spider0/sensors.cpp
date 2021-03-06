#include "sensors.h"

namespace SPIDER {
  /****************************************************************
   * void init()
   ****************************************************************/
  void Sensors::init() {
    _voltage.init();
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
