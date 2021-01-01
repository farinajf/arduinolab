#include "pinChangeInt.h"
#include "ultrasonic.h"

namespace ATOM0 {
  volatile int           _PING_INTERVAL    =  50;
  volatile unsigned long _measurePrevTime  = 0;
  volatile char          _measureFlag      = 0;
  volatile double        HCSR04distance    = 0;
  unsigned long          _distancePrevTime = 0;

  /****************************************************************
   * void _measureDistance()
   ****************************************************************/
  void _measureDistance() {
    if (_measureFlag == 0)
    {
      _measurePrevTime = micros();
      attachPinChangeInterrupt(PIN_ECHO_CENTER, _measureDistance, FALLING);
      _measureFlag = 1;
    }
    else if (_measureFlag == 1)
    {
      HCSR04distance = (micros() - _measurePrevTime) * 0.017;
      _measureFlag = 2;
    }
  }

  /****************************************************************
   * void _sendPulse(int pinTrigger)
   * 
   * Se envía una señal (pulso alto de 5 V) de al menos 10 us por el pin TRIGGER del modulo HC-SR04.
   * Se excita el transductor emisor 8 veces, generando así un tren de 8 pulsos ultrasónicos a 40 KHz.
   * 
   * Se establece el pin ECHO del módulo de ultrasonidos en un nivel alto (5V),
   * y se pondrá en un nivel bajo (0V) cuando se reciba el echo.
   ****************************************************************/
  void _sendPulse(int pinTrigger) {
    digitalWrite     (pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite     (pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite     (pinTrigger, LOW);
  }

  /****************************************************************
   * void ultrasonicInit()
   ****************************************************************/
  void ultrasonicInit() {
    pinMode(PIN_TRIGGER_CENTER, OUTPUT);
    pinMode(PIN_ECHO_CENTER,    INPUT);
  }

  /****************************************************************
   * void ultrasonicCalculate()
   ****************************************************************/
  void ultrasonicCalculate() {
    if (millis() - _distancePrevTime < _PING_INTERVAL) return;

    _distancePrevTime = millis();

    _measureFlag = 0;
    attachPinChangeInterrupt(PIN_ECHO_CENTER, _measureDistance, RISING);

    _sendPulse(PIN_TRIGGER_CENTER);
  }
}
