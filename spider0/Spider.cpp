#include "Spider.h"

namespace SPIDER {
  /****************************************************************
   * void _showInfo()
   * 
   ****************************************************************/
  void Spider0::_showInfo() const {
    Serial.print("Temperatura: "); Serial.print(_sensors.getMPUTemperatura()); Serial.println();

    Serial.print("AnguloX: "); Serial.print(_sensors.getMPUAngleX()); Serial.println();
    Serial.print("AnguloY: "); Serial.print(_sensors.getMPUAngleY()); Serial.println();
  }
  
  /****************************************************************
   * void _up(LegGroup_t group, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const
   ****************************************************************/
  void Spider0::_up(LegGroup_t group, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const {
    Serial.println("Spider0._up()");

    switch (group)
    {
      case GROUP_LEG_1:
          _motor.move(LEG_RIGHT_1, deltaCoxa, deltaFemur, deltaTibia); delay(500);
          _motor.move(LEG_LEFT_2,  deltaCoxa, deltaFemur, deltaTibia); delay(500);
          _motor.move(LEG_RIGHT_3, deltaCoxa, deltaFemur, deltaTibia); delay(500);
          return;

      case GROUP_LEG_2:
          _motor.move(LEG_LEFT_1,  deltaCoxa, deltaFemur, deltaTibia); delay(500);
          _motor.move(LEG_RIGHT_2, deltaCoxa, deltaFemur, deltaTibia); delay(500);
          _motor.move(LEG_LEFT_3,  deltaCoxa, deltaFemur, deltaTibia); delay(500);
          return;
    }
  }

  /****************************************************************
   * void _setDriveMode()
   ****************************************************************/
  /*
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
  */

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
  /*
  void Spider0::_driveOld() {
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
  */

  /****************************************************************
   * void _drive()
   ****************************************************************/
  void Spider0::_drive() {
    const short coxa  = 0;
    const short femur = 60;
    const short tibia = 45;

    //this->_up(GROUP_LEG_1, coxa, femur, tibia);
    this->_reposo();
    //this->_up(GROUP_LEG_2, coxa, femur, tibia);
    this->_reposo();
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

    //2.-
    _showInfo();

    //3.- Check battery
    if (_sensors.isBatteryOK() == true) _drive();
    else delay(10000);

    //4.- End
    delay(200);
  }
}
