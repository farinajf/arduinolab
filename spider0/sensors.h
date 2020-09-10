#include "voltage.h"

#ifndef SENSORS_H
#define SENSORS_H

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
  };
}

#endif
