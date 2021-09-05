/**
 * SPIDER 0
 */
#ifndef ARDUINO_AVR_MEGA2560
#error Wrong board. Please choose "Arduino/Genuino Mega or Mega 2560"
#endif

#include "spider.h"


SPIDER::Spider0 _spider;
bool            _DEBUG = false;
long            _t0    = millis();
bool            _done  = false;
int             _count = 0;

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
  }
}






/**
 * 
 */
void _do() {

  if ((millis() % 5000) != 0) return;

  if (_count > 0) return;

  _count++;

  _spider.crawlForward();
}
