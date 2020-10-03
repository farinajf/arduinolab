#ifndef SENSORS_H
#define SENSORS_H

#include "voltage.h"

/**
 * 
 */
namespace SPIDER {
  class Sensors {
    private:
      Voltage _voltage;

    public:
      Sensors() {}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _voltage.init();
      }

      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        _voltage.calculate();
      }

      /****************************************************************
       * boolean isBatteryOK()
       ****************************************************************/
      boolean isBatteryOK() const {
        return _voltage.isVoltageHigh();
      }
  };
}

#endif
