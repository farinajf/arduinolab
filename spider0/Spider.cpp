#include "Spider.h"

namespace SPIDER {
  /****************************************************************
   * SpiderLeg_t _getLeg() const
   ****************************************************************/
  SpiderLeg_t Spider0::_getLeg() const {
    switch(_driveMode)
    {
      case DRIVE_LEG_RIGHT_1: return LEG_RIGHT_1;
      case DRIVE_LEG_RIGHT_2: return LEG_RIGHT_2;
      case DRIVE_LEG_RIGHT_3: return LEG_RIGHT_3;
      case DRIVE_LEG_LEFT_1:  return LEG_LEFT_1;
      case DRIVE_LEG_LEFT_2:  return LEG_LEFT_2;
      case DRIVE_LEG_LEFT_3:  return LEG_LEFT_3;
    }
  }

  /****************************************************************
   * void _up() const
   ****************************************************************/
  void Spider0::_up() const {
    Serial.println("Spider0._up()");

    _motor.move(_getLeg(), 0, 5, 5);
  }

  /****************************************************************
   * void _down() const
   ****************************************************************/
  void Spider0::_down() const {
    Serial.println("Spider0._down()");

    _motor.move(_getLeg(), 0, -5, -5);
  }

  /****************************************************************
   * void _left() const
   ****************************************************************/
  void Spider0::_left() const {
    Serial.println("Spider0._left()");

    _motor.move(_getLeg(), -5, 0, 0);
  }

  /****************************************************************
   * void _right() const
   ****************************************************************/
  void Spider0::_right() const {
    Serial.println("Spider0._right()");

    _motor.move(_getLeg(),  5, 0, 0);
  }

  /****************************************************************
   * void _setDriveMode()
   ****************************************************************/
  void Spider0::_setDriveMode() {
    while (true)
    {
      switch (_ir.receive())
      {
        case IR_T_1:      _driveMode = DRIVE_LEG_RIGHT_1; Serial.println("Seleccionada pata R-1"); return;
        case IR_T_2:      _driveMode = DRIVE_LEG_RIGHT_2; Serial.println("Seleccionada pata R-2"); return;
        case IR_T_3:      _driveMode = DRIVE_LEG_RIGHT_3; Serial.println("Seleccionada pata R-3"); return;
        case IR_T_4:      _driveMode = DRIVE_LEG_LEFT_1;  Serial.println("Seleccionada pata L-1"); return;
        case IR_T_5:      _driveMode = DRIVE_LEG_LEFT_2;  Serial.println("Seleccionada pata L-2"); return;
        case IR_T_6:      _driveMode = DRIVE_LEG_LEFT_3;  Serial.println("Seleccionada pata L-3"); return;
        case IR_ASTERISK: _driveMode = DRIVE_NONE;        Serial.println("Cancelado!!");           return;
      }
    }
  }

  /****************************************************************
   * void _reposo() const
   ****************************************************************/
  void Spider0::_reposo() const {
    Serial.println("Spider0._reposo()");

    _motor.reposo();
  }

  /****************************************************************
   * void _drive()
   ****************************************************************/
  void Spider0::_drive() {
    switch (_ir.receive())
    {
      case IR_HASH:  _setDriveMode(); break;
      case IR_OK:    _reposo();       break;
      case IR_UP:    _up();           break;
      case IR_DOWN:  _down();         break;
      case IR_LEFT:  _left();         break;
      case IR_RIGHT: _right();        break;
      default:       return;
    }
  }

  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Spider0::Spider0() : _motor(), _sensors() {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void Spider0::init() {
    _ir.init();
    _motor.init();
    _sensors.init();

    _reposo();
  }

  /****************************************************************
   * void drive()
   ****************************************************************/
  void Spider0::drive() {
    //1.- Get information from sensors
    _sensors.calculate();

    //2.- Check battery
    if (_sensors.isBatteryOK() == true) _drive();
    else delay(10000);

    //3.- End
    delay(200);
  }
}
