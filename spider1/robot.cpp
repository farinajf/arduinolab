#include "robot.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Robot::Robot() : _leg1(-RobotShape::X0,  RobotShape::Y0),
                   _leg2(-RobotShape::X1,  0.0),
                   _leg3(-RobotShape::X0, -RobotShape::Y0),
                   _leg4( RobotShape::X0,  RobotShape::Y0),
                   _leg5( RobotShape::X1,  0.0),
                   _leg6( RobotShape::X0, -RobotShape::Y0) {}


  /****************************************************************
   * void init()
   * 
   ****************************************************************/
  void Robot::init() {
    _dataFormatVersion = EEPROM.read(EepromAddresses::dataFormatVersion);

    switch (_dataFormatVersion)
    {
      case 20:
          _productVersion = 2;
          RobotLegItem::FIRST_ROTATE_DELAY = 0;
          _power.init(EXTERNAL, 2.0 / (2.0 + 6.2), true);
          break;
      default:
          _productVersion = 1;
          RobotLegItem::FIRST_ROTATE_DELAY = 50;
          _power.init(EXTERNAL, 10.0 / (10.0 + 10.0), false);
          break;
    }

    _leg1.init(LEG1_COXA, LEG1_FEMUR, LEG1_TIBIA);
    _leg2.init(LEG2_COXA, LEG2_FEMUR, LEG2_TIBIA);
    _leg3.init(LEG3_COXA, LEG3_FEMUR, LEG3_TIBIA);
    _leg4.init(LEG4_COXA, LEG4_FEMUR, LEG4_TIBIA);
    _leg5.init(LEG5_COXA, LEG5_FEMUR, LEG5_TIBIA);
    _leg6.init(LEG6_COXA, LEG6_FEMUR, LEG6_TIBIA);

    this -> _moveToDirectly(BOOT_POINTS);
  }

  /****************************************************************
   * void bootState()
   * 
   ****************************************************************/
  void Robot::bootState() {
    //Serial.println("Robot::bootState()");
    
    this -> _setOffsetEnable(true);
    this -> _setStepDistance(RobotLeg::DEFAULT_STEP_DISTANCE);

    this -> _moveTo(BOOT_POINTS);
    this -> _waitUntilFree();

    _state = RobotState::BOOT;
  }

  /****************************************************************
   * void calibrateState()
   * 
   ****************************************************************/
  void Robot::calibrateState() {
    //Serial.println("Robot::calibrateState()");
    
    _state = RobotState::CALIBRATE;
    
    this -> _setOffsetEnable(false);
    this -> _setStepDistance(RobotLeg::DEFAULT_STEP_DISTANCE);

    this -> _moveTo(CALIBRATE_STATE_POINTS);
    this -> _waitUntilFree();
  }
  
  /****************************************************************
   * void installState()
   * 
   ****************************************************************/
  void Robot::installState() {
    //Serial.println("Robot::installState()");
    
    _state = RobotState::INSTALL;

    this -> _setOffsetEnable(false);
    this -> _setStepDistance(RobotLeg::DEFAULT_STEP_DISTANCE);

    _leg1.rotarServos(90, 90, 90);
    _leg2.rotarServos(90, 90, 90);
    _leg3.rotarServos(90, 90, 90);
    _leg4.rotarServos(90, 90, 90);
    _leg5.rotarServos(90, 90, 90);
    _leg6.rotarServos(90, 90, 90);

    this -> _waitUntilFree();
  }

  /****************************************************************
   * void update()
   * 
   ****************************************************************/
  void Robot::update() {
    this -> _updateAction();
    this -> _power.update();
  }

  


  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * void _moveTo(RobotLegsPoints p)
   * 
   ****************************************************************/
  void Robot::_moveTo(RobotLegsPoints p) {
    _leg1.moveTo(p._leg1);
    _leg2.moveTo(p._leg2);
    _leg3.moveTo(p._leg3);
    _leg4.moveTo(p._leg4);
    _leg5.moveTo(p._leg5);
    _leg6.moveTo(p._leg6);
  }
  
  /****************************************************************
   * void _moveToDirectly(RobotLegsPoints p)
   * 
   ****************************************************************/
  void Robot::_moveToDirectly(RobotLegsPoints p) {
    _leg1.moveToDirectly(p._leg1);
    _leg2.moveToDirectly(p._leg2);
    _leg3.moveToDirectly(p._leg3);
    _leg4.moveToDirectly(p._leg4);
    _leg5.moveToDirectly(p._leg5);
    _leg6.moveToDirectly(p._leg6);
  }


  /****************************************************************
   * void _setOffsetEnable (bool x)
   * 
   ****************************************************************/
  void Robot::_setOffsetEnable(bool x) {
    _leg1.setOffsetEnable(x);
    _leg2.setOffsetEnable(x);
    _leg3.setOffsetEnable(x);
    _leg4.setOffsetEnable(x);
    _leg5.setOffsetEnable(x);
    _leg6.setOffsetEnable(x);
  }


  /****************************************************************
   * void _setStepDistance (float x)
   * 
   ****************************************************************/
  void Robot::_setStepDistance(float x) {
    _leg1.setStepDistance(x);
    _leg2.setStepDistance(x);
    _leg3.setStepDistance(x);
    _leg4.setStepDistance(x);
    _leg5.setStepDistance(x);
    _leg6.setStepDistance(x);
  }

  /****************************************************************
   * void _updateAction()
   * 
   ****************************************************************/
  void Robot::_updateAction() {
    _leg1.updateLegAction(_speedMultiple);
    _leg2.updateLegAction(_speedMultiple);
    _leg3.updateLegAction(_speedMultiple);
    _leg4.updateLegAction(_speedMultiple);
    _leg5.updateLegAction(_speedMultiple);
    _leg6.updateLegAction(_speedMultiple);
  } 
  
  /****************************************************************
   * void _waitUntilFree() const
   * 
   ****************************************************************/
  void Robot::_waitUntilFree() const {
    while(_leg1.isBusy() || _leg2.isBusy() || _leg3.isBusy() || _leg4.isBusy() || _leg5.isBusy() || _leg6.isBusy());
  }
}
