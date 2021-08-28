/**
 * SPIDER 1
 */

#ifndef ARDUINO_AVR_MEGA2560
#error Wrong board. Please choose "Arduino/Genuino Mega or Mega 2560"
#endif

#include "spider.h"

SPIDER::Spider0 _spider;
bool            _DEBUG = false;
bool            _done  = false;
long            _t0    = millis();

/**
 * void setup()
 */
void setup() {
  if (_DEBUG) Serial.begin(9600);

  _spider.init(!_DEBUG);
}


/**
 * void loop()
 */
void loop() {
  _spider.update();

  if (_DEBUG)
  {
    _do();    
    _print();
  }
}

/**
 * 
 */
void _do() {
  if (_done == true) return;

  _done = true;
}

/**
 * 
 */
void _print() {
  if ((millis() - _t0) < 10000) return;

  _t0 = millis();
}
