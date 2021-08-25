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
    _state = RobotState::BOOT;
    
    this -> _setOffsetEnable(true);
    this -> _setStepDistance(RobotLeg::DEFAULT_STEP_DISTANCE);

    this -> moveTo(BOOT_POINTS);
    this -> waitUntilFree();
  }

  /****************************************************************
   * void calibrateState()
   * 
   ****************************************************************/
  void Robot::calibrateState() {
    _state = RobotState::CALIBRATE;
    
    this -> _setOffsetEnable(false);
    this -> _setStepDistance(RobotLeg::DEFAULT_STEP_DISTANCE);

    this -> moveTo(CALIBRATE_STATE_POINTS);
    this -> waitUntilFree();
  }
  
  /****************************************************************
   * void installState()
   * 
   ****************************************************************/
  void Robot::installState() {
    _state = RobotState::INSTALL;

    this -> _setOffsetEnable(false);
    this -> _setStepDistance(RobotLeg::DEFAULT_STEP_DISTANCE);

    _leg1.rotarServos(90, 90, 90);
    _leg2.rotarServos(90, 90, 90);
    _leg3.rotarServos(90, 90, 90);
    _leg4.rotarServos(90, 90, 90);
    _leg5.rotarServos(90, 90, 90);
    _leg6.rotarServos(90, 90, 90);

    this -> waitUntilFree();
  }

  /****************************************************************
   * void calibrateServos()
   * 
   ****************************************************************/
  void Robot::calibrateServos() {
    //0.- Comprobar estado
    if (_state != RobotState::CALIBRATE) return;

    //1.- Calibrar cada pata
    this -> _calibrateLeg(_leg1, CALIBRATE_POINTS._leg1);
    this -> _calibrateLeg(_leg2, CALIBRATE_POINTS._leg2);
    this -> _calibrateLeg(_leg3, CALIBRATE_POINTS._leg3);
    this -> _calibrateLeg(_leg4, CALIBRATE_POINTS._leg4);
    this -> _calibrateLeg(_leg5, CALIBRATE_POINTS._leg5);
    this -> _calibrateLeg(_leg6, CALIBRATE_POINTS._leg6);

    //2.- Reestablecer OFFSET
    this -> _setOffsetEnable(true);
  }

  /****************************************************************
   * void calibrateVerify()
   * 
   ****************************************************************/
  void Robot::calibrateVerify() {
    _state = RobotState::CALIBRATE;

    this -> _setStepDistance(RobotLeg::DEFAULT_STEP_DISTANCE);
    this -> moveTo          (CALIBRATE_STATE_POINTS);
    this -> waitUntilFree();

    this -> _setOffsetEnable(true);
    this -> moveTo          (CALIBRATE_POINTS);
    this -> waitUntilFree();
  }

  /****************************************************************
   * bool checkPoints(RobotLegsPoints p)
   * 
   ****************************************************************/
  bool Robot::checkPoints(RobotLegsPoints p) {
    if (_leg1.checkPoint(p._leg1) == false) return false;
    if (_leg2.checkPoint(p._leg2) == false) return false;
    if (_leg3.checkPoint(p._leg3) == false) return false;
    if (_leg4.checkPoint(p._leg4) == false) return false;
    if (_leg5.checkPoint(p._leg5) == false) return false;
    if (_leg6.checkPoint(p._leg6) == false) return false;

    return true;
  }

  /****************************************************************
   * void getPointsNow(RobotLegsPoints &points)
   * 
   ****************************************************************/
  void Robot::getPointsNow(RobotLegsPoints &points) {
    points._leg1 = _leg1.getPosicionActual();
    points._leg2 = _leg2.getPosicionActual();
    points._leg3 = _leg3.getPosicionActual();
    points._leg4 = _leg4.getPosicionActual();
    points._leg5 = _leg5.getPosicionActual();
    points._leg6 = _leg6.getPosicionActual();
  }

  /****************************************************************
   * void moveTo(RobotLegsPoints p)
   * 
   ****************************************************************/
  void Robot::moveTo(RobotLegsPoints p) {
    _leg1.moveTo(p._leg1);
    _leg2.moveTo(p._leg2);
    _leg3.moveTo(p._leg3);
    _leg4.moveTo(p._leg4);
    _leg5.moveTo(p._leg5);
    _leg6.moveTo(p._leg6);
  }

  /****************************************************************
   * void moveTo(RobotLegsPoints p, float stepDistance)
   * 
   ****************************************************************/
  void Robot::moveTo(RobotLegsPoints p, float stepDistance) {
    //1.- Establecer la longitud del paso
    this -> _setStepDistance(stepDistance);

    //2.- Mover las patas a la nueva posicion
    this -> moveTo(p);
  }

  /****************************************************************
   * void setSpeedMultiple(float x)
   * 
   ****************************************************************/
  void Robot::setSpeedMultiple(float x) {
    _speedMultiple = constrain(x, 0.01, 1);
  }

  /****************************************************************
   * void setStepDistance(float x1, float x2, float x3, float x4, float x5, float x6)
   * 
   ****************************************************************/
  void Robot::setStepDistance(float x1, float x2, float x3, float x4, float x5, float x6) {
    _leg1.setStepDistance(x1);
    _leg2.setStepDistance(x2);
    _leg3.setStepDistance(x3);
    _leg4.setStepDistance(x4);
    _leg5.setStepDistance(x5);
    _leg6.setStepDistance(x6);
  }

  /****************************************************************
   * void update()
   * 
   ****************************************************************/
  void Robot::update() {
    this -> _updateAction();
    this -> _power.update();
  }

  /****************************************************************
   * void waitUntilFree() const
   * 
   ****************************************************************/
  void Robot::waitUntilFree() const {
    while(_leg1.isBusy() || _leg2.isBusy() || _leg3.isBusy() || _leg4.isBusy() || _leg5.isBusy() || _leg6.isBusy());
  }


  


  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * void _calibrateLeg(RobotLeg &leg, Point calibratePoint)
   * 
   ****************************************************************/
  void Robot::_calibrateLeg(RobotLeg &leg, Point calibratePoint) {
    float alpha;
    float beta;
    float gamma;

    leg.calculateAngle(calibratePoint, alpha, beta, gamma);

    leg.getCoxa().setOffset (leg.getCoxa().getAngulo()  - alpha);
    leg.getFemur().setOffset(leg.getFemur().getAngulo() - beta);
    leg.getTibia().setOffset(leg.getTibia().getAngulo() - gamma);
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
   * void setStepDistance (float x)
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
}
