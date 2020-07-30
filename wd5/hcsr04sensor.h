#include "pinChangeInt.h"
#include "pins.h"

#ifndef HCSR04_SENSOR_H
#define HCSR04_SENSOR_H

#define TIME_MIN 50

namespace WD5 {
  volatile unsigned long _measureRightPrevTime  = 0;
  volatile char          _measureRightFlag      = 0;
  unsigned long          _distanceRightPrevTime = 0;
  double                 HCSR04distanceRight    = 0;

  volatile unsigned long _measureLeftPrevTime   = 0;
  volatile char          _measureLeftFlag       = 0;
  unsigned long          _distanceLeftPrevTime  = 0;
  double                 HCSR04distanceLeft     = 0;
  
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
   * void _measureRightDistance()
   */
  void _measureDistanceRight() {
    if (_measureRightFlag == 0)
    {
      _measureRightPrevTime = micros();
      attachPinChangeInterrupt(PIN_ECHO_RIGHT, _measureDistanceRight, FALLING);
      _measureRightFlag = 1;
    }
    else if (_measureRightFlag == 1)
    {
      HCSR04distanceRight = (micros() - _measureRightPrevTime) * 0.017;
      _measureRightFlag = 2;
    }
  }

  /**
   * void _measureDistanceLeft()
   */
  void _measureDistanceLeft() {
    if (_measureLeftFlag == 0)
    {
      _measureLeftPrevTime = micros();
      attachPinChangeInterrupt(PIN_ECHO_LEFT, _measureDistanceLeft, FALLING);
      _measureLeftFlag = 1;
    }
    else if (_measureLeftFlag == 1)
    {
      HCSR04distanceLeft = (micros() - _measureLeftPrevTime) * 0.017;
      _measureLeftFlag = 2;
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
    if (millis() - _distancePrevTime < TIME_MIN) return;

    _distancePrevTime = millis();

    _measureFlag = 0;
    attachPinChangeInterrupt(PIN_ECHO_CENTER, _measureDistance, RISING);

    _sendPulse(PIN_TRIGGER_CENTER);
  }

  /**
   * void getDistanceRight()
   * 
   * Calcula la distancia a la derecha.
   * 
   */
  void getDistanceRight() {
    if (millis() - _distanceRightPrevTime < TIME_MIN) return;

    _distanceRightPrevTime = millis();

    _measureRightFlag = 0;
    attachPinChangeInterrupt(PIN_ECHO_RIGHT, _measureDistanceRight, RISING);

    _sendPulse(PIN_TRIGGER_RIGHT);
  }

  /**
   * void getDistanceLeft()
   * 
   * Calcula la distancia al frente.
   * 
   */
  void getDistanceLeft() {
    if (millis() - _distanceLeftPrevTime < TIME_MIN) return;

    _distanceLeftPrevTime = millis();

    _measureLeftFlag = 0;
    attachPinChangeInterrupt(PIN_ECHO_LEFT, _measureDistanceLeft, RISING);

    _sendPulse(PIN_TRIGGER_LEFT);
  }
}

#endif
