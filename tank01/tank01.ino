/**
 * 
 */
#include "pins.h"
#include "tankGlobals.h"
#include "tankSonar.h"
#include "l298nEngine.h"
#include "tankDriver.h"

TANK01::L298NEngine md(PIN_EN_D, PIN_IN1_D, PIN_IN2_D);
TANK01::L298NEngine mi(PIN_EN_I, PIN_IN1_I, PIN_IN2_I);
TANK01::TankDriver  td(md, mi);
TANK01::TankSonar   sonar;

/***************************************************************************************
 * Estado de movimiento del tanque
 * 
 **************************************************************************************/
void _drive() {
  switch(_MOTION_MODE_)
  {
    case FORWARD:
        td.forward();
        sonar.checkObstacleFront();
        break;

    case BACKWARD:  break;
    
    case TURNLEFT:
        Serial.println(">> TURNLEFT");
        td.izquierda();
        break;
        
    case TURNRIGHT:
        Serial.println(">> TURNLEFT");
        td.derecha();
        break;
    
    case STANDBY:
        Serial.println(">> STANDBY");
        td.parar();
        sonar.buscar();
        break;

    case STOP:
        td.parar();
        break;

    case START:
        delay(1000);
        _MOTION_MODE_ = STANDBY;
        break;

    default: break;
  }
}

/**
 * 
 */
void setup() {
  Serial.begin(9600);
  
  sonar.init();
  md.init   ();
  mi.init   ();
  td.init   ();

  _MOTION_MODE_ = START;
}

/**
 * 
 */
void loop() {
  _drive();

  Serial.print("Motion mode: "); Serial.println(_MOTION_MODE_);
  delay(100);
}
