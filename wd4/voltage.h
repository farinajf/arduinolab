#ifndef WD4_VOLTAGE_H
#define WD4_VOLTAGE_H

namespace WD4
{
  class Voltage {
    private:
      const float   _multiplier     = (4.68 + 4.69) / 4.69;

      unsigned long _measureTime    = 0;
      bool          _lowVoltageFlag = false;

      void _high(int pin) {digitalWrite(pin, HIGH);}
      void _low (int pin) {digitalWrite(pin, LOW);}

      /**
       * void _lowBattery()
       */
      void _batteryLow() {
        //1.- Establecemos el flag a true
        _lowVoltageFlag = true;

        //2.- Encender el LED
        _high(LED_BUILTIN);
      }

      /**
       * void _lowBattery()
       */
      void _batteryOK() {
        //1.- Establecemos el flag a false
        _lowVoltageFlag = false;

        //2.- Apagar el LED
        _low(LED_BUILTIN);
      }

    public:
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
       * 
       */
      bool isVoltageLow() {
        if (millis() - _measureTime <= 1000) return _lowVoltageFlag;

        _measureTime = millis();

        double voltage = (analogRead(VOL_MEASURE_PIN) * 5.0 / 1024.0) * _multiplier;
        //Serial.print("voltage: "); Serial.println(voltage);

        if (voltage < VOLTAGE_UMBRAL) _batteryLow();
        else                          _batteryOK();

        return _lowVoltageFlag;
      }
  };
}
#endif
