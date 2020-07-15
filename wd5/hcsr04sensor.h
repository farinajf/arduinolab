#include "pinChangeInt.h"
#include "pins.h"

#ifndef HCSR04_SENSOR_H
#define HCSR04_SENSOR_H

#define TIME_MIN 50

namespace WD5
{
  volatile unsigned long _measurePrevTime       = 0;
  volatile char          _measureFlag           = 0;
  unsigned long          _distancePrevTime      = 0;
  double                 HCSR04distance         = 0;

  ////////////////////////////////////////////////////////////////////
  //Private
  ////////////////////////////////////////////////////////////////////
  /**
   * void _measureDistance()
   */
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

  /**
   * void _sendPulse(int pinTrigger)
   * 
   * Se envía una señal (pulso alto de 5 V) de al menos 10 us por el pin TRIGGER del modulo HC-SR04.
   * Se excita el transductor emisor 8 veces, generando así un tren de 8 pulsos ultrasónicos a 40 KHz.
   * 
   * Se establece el pin ECHO del módulo de ultrasonidos en un nivel alto (5V),
   * y se pondrá en un nivel bajo (0V) cuando se reciba el echo.
   */
  void _sendPulse(int pinTrigger) {
    digitalWrite     (pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite     (pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite     (pinTrigger, LOW);
  }

  ////////////////////////////////////////////////////////////////////
  // Public
  ////////////////////////////////////////////////////////////////////
  /**
   * void ultrasonicInit()
   */
  void ultrasonicInit() {
    pinMode(PIN_TRIGGER_CENTER, OUTPUT);
    pinMode(PIN_ECHO_CENTER,    INPUT);

    pinMode(PIN_TRIGGER_RIGHT,  OUTPUT);
    pinMode(PIN_ECHO_RIGHT,     INPUT);

    pinMode(PIN_TRIGGER_LEFT,   OUTPUT);
    pinMode(PIN_ECHO_LEFT,      INPUT);
  }

  /**
   * void getDistance()
   * 
   * Calcula la distancia a la izquierda.
   * 
   */
  void getDistance() {
    if (millis() - _distancePrevTime < 50) return;

    _distancePrevTime = millis();

    _measureFlag = 0;
    attachPinChangeInterrupt(PIN_ECHO_CENTER, _measureDistance, RISING);

    _sendPulse(PIN_TRIGGER_CENTER);
  }
}

#endif
