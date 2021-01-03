#include "voltage.h"

namespace SPIDER {
  /****************************************************************
   * void _batteryLow()
   ****************************************************************/
  void Voltage::_batteryLow() {
    _voltageHigh = false;

    _high(RED_LED_PIN);
    _low (GREEN_LED_PIN);
  }

  /****************************************************************
   * void _batteryOK()
   ****************************************************************/
  void Voltage::_batteryOK() {
    _voltageHigh = true;

    _low (RED_LED_PIN);
    _high(GREEN_LED_PIN);
  }

  /****************************************************************
   * void init()
   ****************************************************************/
  void Voltage::init() {
    pinMode(VOL_MEASURE_PIN, INPUT);
    pinMode(RED_LED_PIN,     OUTPUT);
    pinMode(GREEN_LED_PIN,   OUTPUT);

    _low(RED_LED_PIN);
    _low(GREEN_LED_PIN);
  }

  /****************************************************************
   * void calculate()
   ****************************************************************/
  void Voltage::calculate() {
    if (millis() - _measureTime <= 1000) return;

    _measureTime = millis();

    int voltage = analogRead(VOL_MEASURE_PIN);

    if (voltage < VOLTAGE_UMBRAL) _batteryLow();
    else                          _batteryOK();
  }

  /****************************************************************
   * bool isVoltageHigh() const
   ****************************************************************/
  bool Voltage::isVoltageHigh() const {
    return _voltageHigh;
  }
}
