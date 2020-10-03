/**
 * SPIDER 0
 */
#include "Spider.h"
#include "sensors.h"
#include "receptorIR.h"

SPIDER::ReceptorIR _ir;
SPIDER::Spider0 _spider;
SPIDER::Sensors _sensors;

const int pataIzqDelanteraAngles[3] = {90, 90, 90};
const int pataIzqMediaAngles    [3] = {90, 90, 90};
const int pataIzqTraseraAngles  [3] = {90, 90, 90};

const int pataDerDelanteraAngles[3] = {90, 90, 90};
const int pataDerMediaAngles    [3] = {90, 90, 90};
const int pataDerTraseraAngles  [3] = {90, 90, 90};


/**
 * void loop()
 */
void _do() {
  //_spider.move(pataIzqDelanteraAngles, pataIzqMediaAngles, pataIzqTraseraAngles, pataDerDelanteraAngles, pataDerMediaAngles, pataDerTraseraAngles);

  switch (_ir.receive())
  {
    default: return;
  }

  delay(200);
}

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  _sensors.init();
  _ir.init();
  _spider.init();
}

/**
 * void loop()
 */
void loop() {
  //1.- Get information from sensors
  _sensors.calculate();

  //2.- Check battery
  while (_sensors.isBatteryOK() == true)
  {
    _do();
    
  }
  
  //3.- Get the state of motion of the car
  delay(10000);
}
