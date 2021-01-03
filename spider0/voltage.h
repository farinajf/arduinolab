#ifndef VOLTAGE_H
#define VOLTAGE_H

#include "globals.h"

namespace SPIDER {
  class Voltage {
    private:
      unsigned long  _measureTime = 0;
      bool           _voltageHigh = true;

      void _high(const int pin) const {digitalWrite(pin, HIGH);}
      void _low (const int pin) const {digitalWrite(pin, LOW);}

      void _batteryLow();
      void _batteryOK();

    public:
      Voltage() {}

      void init();
      void calculate();

      bool isVoltageHigh() const;
  };
}
#endif
