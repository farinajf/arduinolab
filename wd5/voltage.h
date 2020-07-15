#include "wd5globals.h"
#include "pins.h"

#ifndef WD5_VOLTAGE_H
#define WD5_VOLTAGE_H

namespace WD5
{
  class Voltage {
    private:
      const    float _multiplier  = (4.68 + 4.69) / 4.69;
      unsigned long  _measureTime = 0;
      bool           _voltageHigh = true;

      void _high(int pin) {digitalWrite(pin, HIGH);}
      void _low (int pin) {digitalWrite(pin, LOW);}

      /**
       * void _lowBattery()
       */
      void _batteryLow() {
        _voltageHigh = false;
        
        _high(LED_BUILTIN);
      }

      /**
       * void _lowBattery()
       */
      void _batteryOK() {
        _voltageHigh = true;
        
        _low(LED_BUILTIN);
      }

    public:
      boolean isVoltageHigh() const {return _voltageHigh;}
      
      /**
       * void init()
       */
      void init() {
        //analogReference(INTERNAL);

        pinMode(VOL_MEASURE_PIN, INPUT);
        pinMode(LED_BUILTIN,     OUTPUT);
        
        _low(LED_BUILTIN);
      }

      /**
       * void calculate()
       */
      void calculate() {
        if (millis() - _measureTime <= 1000) return;

        _measureTime = millis();

        double voltage = (analogRead(VOL_MEASURE_PIN) * 5.0 / 1024.0) * _multiplier;
        //Serial.print("voltage: "); Serial.println(voltage);

        if (voltage < VOLTAGE_UMBRAL) _batteryLow();
        else                          _batteryOK();
      }
  };
}
#endif
