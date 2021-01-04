#include "Spider.h"

namespace SPIDER {
  /****************************************************************
   * void _up() const
   ****************************************************************/
  void Spider0::_up() const {
    Serial.println("Spider0._up()");

    switch (_driveMode)
    {
      case DRIVE_GROUP_LEG_1:
          _motor.move(LEG_RIGHT_1, 0, 5, 5);
          _motor.move(LEG_LEFT_2,  0, 5, 5);
          _motor.move(LEG_RIGHT_3, 0, 5, 5);
          return;

      case DRIVE_GROUP_LEG_2:
          _motor.move(LEG_LEFT_1,  0, 5, 5);
          _motor.move(LEG_RIGHT_2, 0, 5, 5);
          _motor.move(LEG_LEFT_3,  0, 5, 5);
          return;
    }
  }

  /****************************************************************
   * void _down() const
   ****************************************************************/
  void Spider0::_down() const {
    Serial.println("Spider0._down()");

    switch (_driveMode)
    {
      case DRIVE_GROUP_LEG_1:
          _motor.move(LEG_RIGHT_1, 0, -5, -5);
          _motor.move(LEG_LEFT_2,  0, -5, -5);
          _motor.move(LEG_RIGHT_3, 0, -5, -5);
          return;

      case DRIVE_GROUP_LEG_2:
          _motor.move(LEG_LEFT_1,  0, -5, -5);
          _motor.move(LEG_RIGHT_2, 0, -5, -5);
          _motor.move(LEG_LEFT_3,  0, -5, -5);
          return;
    }
  }

  /****************************************************************
   * void _left() const
   ****************************************************************/
  void Spider0::_left() const {
    Serial.println("Spider0._left()");

    switch (_driveMode)
    {
      case DRIVE_GROUP_LEG_1:
          _motor.move(LEG_RIGHT_1, -5, 0, 0);
          _motor.move(LEG_LEFT_2,  -5, 0, 0);
          _motor.move(LEG_RIGHT_3, -5, 0, 0);
          return;

      case DRIVE_GROUP_LEG_2:
          _motor.move(LEG_LEFT_1,  -5, 0, 0);
          _motor.move(LEG_RIGHT_2, -5, 0, 0);
          _motor.move(LEG_LEFT_3,  -5, 0, 0);
          return;
    }
  }

  /****************************************************************
   * void _right() const
   ****************************************************************/
  void Spider0::_right() const {
    Serial.println("Spider0._right()");

    switch (_driveMode)
    {
      case DRIVE_GROUP_LEG_1:
          _motor.move(LEG_RIGHT_1, 5, 0, 0);
          _motor.move(LEG_LEFT_2,  5, 0, 0);
          _motor.move(LEG_RIGHT_3, 5, 0, 0);
          return;

      case DRIVE_GROUP_LEG_2:
          _motor.move(LEG_LEFT_1,  5, 0, 0);
          _motor.move(LEG_RIGHT_2, 5, 0, 0);
          _motor.move(LEG_LEFT_3,  5, 0, 0);
          return;
    }
  }

  /****************************************************************
   * void _setDriveMode()
   ****************************************************************/
  void Spider0::_setDriveMode() {
    while (true)
    {
      switch (_ir.receive())
      {
        case IR_T_1:      _driveMode = DRIVE_GROUP_LEG_1; Serial.println("Seleccionada G-1"); return;
        case IR_T_2:      _driveMode = DRIVE_GROUP_LEG_2; Serial.println("Seleccionada G-2"); return;
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
