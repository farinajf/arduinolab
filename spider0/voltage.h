#include "pins.h"
#include "globals.h"

#ifndef VOLTAGE_H
#define VOLTAGE_H

/**
 * 
 */
namespace SPIDER {
  class Voltage {
    private:
      unsigned long  _measureTime = 0;
      bool           _voltageHigh = true;
      
      void _high(int pin) {digitalWrite(pin, HIGH);}
      void _low (int pin) {digitalWrite(pin, LOW);}

      /****************************************************************
       * void _batteryLow()
       ****************************************************************/
      void _batteryLow() {
        _voltageHigh = false;
        
        _high(RED_LED_PIN);
        _low (GREEN_LED_PIN);
      }

      /****************************************************************
       * void _batteryOK()
       ****************************************************************/
      void _batteryOK() {
        _voltageHigh = true;
        
        _low (RED_LED_PIN);
        _high(GREEN_LED_PIN);
      }


    public:
      /****************************************************************
       * boolean isVoltageHigh()
       ****************************************************************/
      boolean isVoltageHigh() const {return _voltageHigh;}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        pinMode(VOL_MEASURE_PIN, INPUT);
        pinMode(RED_LED_PIN,     OUTPUT);
        pinMode(GREEN_LED_PIN,   OUTPUT);
        
        _low(RED_LED_PIN);
        _low(GREEN_LED_PIN);
      }

      /****************************************************************
       * void calculate()
       ****************************************************************/
      void calculate() {
        if (millis() - _measureTime <= 1000) return;

        _measureTime = millis();

        int voltage = analogRead(VOL_MEASURE_PIN);

        if (voltage < VOLTAGE_UMBRAL) _batteryLow();
        else                          _batteryOK();

        //Serial.print("Bateria: "); Serial.println(voltage);
      }
  };
}

#endif
