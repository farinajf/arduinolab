#ifndef SENSORS_H
#define SENSORS_H

#include "voltage.h"

namespace SPIDER {
  class Sensors {
    private:
      Voltage _voltage;

    public:
      Sensors(): _voltage() {}

      void init();
      void calculate();

      bool isBatteryOK() const;
  };
}
#endif
