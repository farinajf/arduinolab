#include "Spider.h"

namespace SPIDER {
  /****************************************************************
   * void _setDriveMode()
   ****************************************************************/
  void Spider0::_setDriveMode() {
    while (true)
    {
      switch (_ir.receive())
      {
        case IR_T_1:      setDriveMode(DRIVE_MODE_LEG_MOVE_1); Serial.println("Seleccionada pata 1"); return;
        case IR_T_2:      setDriveMode(DRIVE_MODE_LEG_MOVE_2); Serial.println("Seleccionada pata 2"); return;
        case IR_T_3:      setDriveMode(DRIVE_MODE_LEG_MOVE_3); Serial.println("Seleccionada pata 3"); return;
        case IR_T_4:      setDriveMode(DRIVE_MODE_LEG_MOVE_4); Serial.println("Seleccionada pata 4"); return;
        case IR_T_5:      setDriveMode(DRIVE_MODE_LEG_MOVE_5); Serial.println("Seleccionada pata 5"); return;
        case IR_T_6:      setDriveMode(DRIVE_MODE_LEG_MOVE_6); Serial.println("Seleccionada pata 6"); return;
        case IR_ASTERISK: setDriveMode(DRIVE_MODE_NONE);       Serial.println("Cancelado!!");         return;
      }
    }
  }

  /****************************************************************
   * void _up()
   ****************************************************************/
  void Spider0::_up() {
    switch (_driveMode)
    {
      case DRIVE_MODE_LEG_MOVE_1: _motor.leg(RIGHT_LEG_FRONT,  0, 5, 5); break;
      case DRIVE_MODE_LEG_MOVE_2: _motor.leg(RIGHT_LEG_MIDDLE, 0, 5, 5); break;
      case DRIVE_MODE_LEG_MOVE_3: _motor.leg(RIGHT_LEG_BACK,   0, 5, 5); break;
      case DRIVE_MODE_LEG_MOVE_4: _motor.leg(LEFT_LEG_FRONT,   0, 5, 5); break;
      case DRIVE_MODE_LEG_MOVE_5: _motor.leg(LEFT_LEG_MIDDLE,  0, 5, 5); break;
      case DRIVE_MODE_LEG_MOVE_6: _motor.leg(LEFT_LEG_BACK,    0, 5, 5); break;
    }
  }

  /****************************************************************
   * void _down()
   ****************************************************************/
  void Spider0::_down() {
    switch (_driveMode)
    {
      case DRIVE_MODE_LEG_MOVE_1: _motor.leg(RIGHT_LEG_FRONT,  0, -5, -5); break;
      case DRIVE_MODE_LEG_MOVE_2: _motor.leg(RIGHT_LEG_MIDDLE, 0, -5, -5); break;
      case DRIVE_MODE_LEG_MOVE_3: _motor.leg(RIGHT_LEG_BACK,   0, -5, -5); break;
      case DRIVE_MODE_LEG_MOVE_4: _motor.leg(LEFT_LEG_FRONT,   0, -5, -5); break;
      case DRIVE_MODE_LEG_MOVE_5: _motor.leg(LEFT_LEG_MIDDLE,  0, -5, -5); break;
      case DRIVE_MODE_LEG_MOVE_6: _motor.leg(LEFT_LEG_BACK,    0, -5, -5); break;
    }
  }

  /****************************************************************
   * void _left()
   ****************************************************************/
  void Spider0::_left() {
    switch (_driveMode)
    {
      case DRIVE_MODE_LEG_MOVE_1: _motor.leg(RIGHT_LEG_FRONT,  -5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_2: _motor.leg(RIGHT_LEG_MIDDLE, -5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_3: _motor.leg(RIGHT_LEG_BACK,   -5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_4: _motor.leg(LEFT_LEG_FRONT,   -5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_5: _motor.leg(LEFT_LEG_MIDDLE,  -5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_6: _motor.leg(LEFT_LEG_BACK,    -5, 0, 0); break;
    }
  }

  /****************************************************************
   * void _right()
   ****************************************************************/
  void Spider0::_right() {
    switch (_driveMode)
    {
      case DRIVE_MODE_LEG_MOVE_1: _motor.leg(RIGHT_LEG_FRONT,  5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_2: _motor.leg(RIGHT_LEG_MIDDLE, 5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_3: _motor.leg(RIGHT_LEG_BACK,   5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_4: _motor.leg(LEFT_LEG_FRONT,   5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_5: _motor.leg(LEFT_LEG_MIDDLE,  5, 0, 0); break;
      case DRIVE_MODE_LEG_MOVE_6: _motor.leg(LEFT_LEG_BACK,    5, 0, 0); break;
    }
  }
  
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Spider0::Spider0() : _motor() {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void Spider0::init() {
    _ir.init();
    _motor.init();
  }

  /****************************************************************
   * void reposo() const
   ****************************************************************/
  void Spider0::reposo() const {
    _motor.reposo();
  }

  /****************************************************************
   * void drive()
   * 
   ****************************************************************/
  void Spider0::drive() {
    switch (_ir.receive())
    {
      case IR_OK:    reposo();        break;
      case IR_HASH:  _setDriveMode(); break;
      case IR_UP:    _up();           break;
      case IR_DOWN:  _down();         break;
      case IR_LEFT:  _left();         break;
      case IR_RIGHT: _right();        break;
      default:    return;
    }
  }
}
