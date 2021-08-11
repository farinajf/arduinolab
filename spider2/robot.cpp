#include "robot.h"

namespace SPIDER {

  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Robot::Robot() : _rightDriver(ADDR_PCA9685_RIGHT),
                   _leftDriver (ADDR_PCA9685_LEFT),
                   _leg1(LEG1_ADDR, LEG_POSITION_0, LEG_POSITION_90, -X0,  Y0,  LEG1_MIN_ANGLE_90, LEG1_MAX_ANGLE_90, LEG1_ZERO_ANGLE_90, LEG_1_3_JOIN_DIR),
                   _leg2(LEG2_ADDR, LEG_POSITION_0, LEG_POSITION_90, -X0,  0.0, LEG2_MIN_ANGLE_90, LEG2_MAX_ANGLE_90, LEG2_ZERO_ANGLE_90, LEG_1_3_JOIN_DIR),
                   _leg3(LEG3_ADDR, LEG_POSITION_0, LEG_POSITION_90, -X0, -Y0,  LEG3_MIN_ANGLE_90, LEG3_MAX_ANGLE_90, LEG3_ZERO_ANGLE_90, LEG_1_3_JOIN_DIR),
                   _leg4(LEG4_ADDR, LEG_POSITION_0, LEG_POSITION_90,  X0,  Y0,  LEG4_MIN_ANGLE_90, LEG4_MAX_ANGLE_90, LEG4_ZERO_ANGLE_90, LEG_4_6_JOIN_DIR),
                   _leg5(LEG5_ADDR, LEG_POSITION_0, LEG_POSITION_90,  X0,  0.0, LEG5_MIN_ANGLE_90, LEG5_MAX_ANGLE_90, LEG5_ZERO_ANGLE_90, LEG_4_6_JOIN_DIR),
                   _leg6(LEG6_ADDR, LEG_POSITION_0, LEG_POSITION_90,  X0, -Y0,  LEG6_MIN_ANGLE_90, LEG6_MAX_ANGLE_90, LEG6_ZERO_ANGLE_90, LEG_4_6_JOIN_DIR) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void Robot::init() {
    //1.- Drivers
    _rightDriver.init();
    _leftDriver.init();

    //2.- Legs
    _leg1.setDriver(&_leftDriver);
    _leg2.setDriver(&_leftDriver);
    _leg3.setDriver(&_leftDriver);
    _leg4.setDriver(&_rightDriver);
    _leg5.setDriver(&_rightDriver);
    _leg6.setDriver(&_rightDriver);
    
    //2.- Legs
    _leg1.init();
    _leg2.init();
    _leg3.init();
    _leg4.init();
    _leg5.init();
    _leg6.init();

    //3.- Move to Initial Points
    this -> _moveToDirectly(&_BOOT_POINTS);
  }

  /****************************************************************
   * void bootState()
   ****************************************************************/
  void Robot::bootState() {
    this -> moveTo(_BOOT_POINTS);
    this -> waitUntilFree();

    _state = RobotState::BOOT;
  }

  /****************************************************************
   * bool checkPoints (RobotLegsPoints &p)
   * 
   ****************************************************************/
  bool Robot::checkPoints(RobotLegsPoints &p) {
    return (_leg1.checkPoint(p._leg1) &&
            _leg2.checkPoint(p._leg2) &&
            _leg3.checkPoint(p._leg3) &&
            _leg4.checkPoint(p._leg4) &&
            _leg5.checkPoint(p._leg5) &&
            _leg6.checkPoint(p._leg6)) ? true : false;
  }

  /****************************************************************
   * void getPointsNow(RobotLegsPoints &p)
   * 
   ****************************************************************/
  void Robot::getPointsNow(RobotLegsPoints &p) {
    p._leg1 = _leg1.getPointNow();
    p._leg2 = _leg2.getPointNow();
    p._leg3 = _leg3.getPointNow();
    p._leg4 = _leg4.getPointNow();
    p._leg5 = _leg5.getPointNow();
    p._leg6 = _leg6.getPointNow();
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
   * void setSpeed(short speed)
   ****************************************************************/
  void Robot::setSpeed(short speed) {
    this -> setSpeed(speed, speed, speed, speed, speed, speed);
  }

  /****************************************************************
   * void setSpeed(short s1, short s2, short s3, short s4, short s5, short s6)
   ****************************************************************/
  void Robot::setSpeed(short s1, short s2, short s3, short s4, short s5, short s6) {
    _leg1.setStepDistance(s1);
    _leg2.setStepDistance(s2);
    _leg3.setStepDistance(s3);
    _leg4.setStepDistance(s4);
    _leg5.setStepDistance(s5);
    _leg6.setStepDistance(s6);
  }

  /****************************************************************
   * void update()
   ****************************************************************/
  void Robot::update() {
    _updateAction();
  }

  /****************************************************************
   * void waitUntilFree()
   ****************************************************************/
  void Robot::waitUntilFree() {
    while (_leg1.isBusy() || _leg2.isBusy() || _leg3.isBusy() || _leg4.isBusy() || _leg5.isBusy() || _leg6.isBusy());
  }




  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * void _moveToDirectly(RobotLegsPoints *p)
   * 
   ****************************************************************/
  void Robot::_moveToDirectly(RobotLegsPoints *p) {
    _leg1.moveToDirectly(p -> _leg1);
    _leg2.moveToDirectly(p -> _leg2);
    _leg3.moveToDirectly(p -> _leg3);
    _leg4.moveToDirectly(p -> _leg4);
    _leg5.moveToDirectly(p -> _leg5);
    _leg6.moveToDirectly(p -> _leg6);
  }

  /****************************************************************
   * void _updateAction()
   * 
   ****************************************************************/
  void Robot::_updateAction() {
    _updateAction(_leg1);
    _updateAction(_leg2);
    _updateAction(_leg3);
    _updateAction(_leg4);
    _updateAction(_leg5);
    _updateAction(_leg6);
  }

  /****************************************************************
   * void _updateAction(RobotLeg &leg)
   * 
   ****************************************************************/
  void Robot::_updateAction(RobotLeg &leg) {
    float distance  = Point::getDistance(leg.getPointGoal(), leg.getPointNow());
    
    float xDistance = leg.getPointGoal()._x - leg.getPointNow()._x;
    float yDistance = leg.getPointGoal()._y - leg.getPointNow()._y;
    float zDistance = leg.getPointGoal()._z - leg.getPointNow()._z;

    float factor = (distance > ROBOT_LEG_NEGLIGIBLE_DISTANCE) ? ((float) leg.getStepDistance()) * ((float) _speedMultiple) / distance : 1.0;

    float xStep = xDistance * factor;
    float yStep = yDistance * factor;
    float zStep = zDistance * factor;

    Point pointGoal = Point(leg.getPointNow()._x + xStep, leg.getPointNow()._y + yStep, leg.getPointNow()._z + zStep);

    if ((distance >= leg.getStepDistance() * _speedMultiple) && (distance >= ROBOT_LEG_NEGLIGIBLE_DISTANCE))
    {
      leg.setBusy(true);
      leg.moveToDirectly(pointGoal);
    }
    else if (leg.isBusy() == true)
    {
      leg.setBusy(false);
      leg.moveToDirectly(pointGoal);
    }
  }
}
