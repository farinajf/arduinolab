#include "km0car.h"

namespace KM0CAR {
  /****************************************************************
   * void _forward() const
   ****************************************************************/
  void KM0CAR::_forward() const {
    _rightEngine.forward(_forwardSpeed);
    _leftEngine.forward (_forwardSpeed);

    _luces.switchOn();
  }

  /****************************************************************
   * void _backward() const
   ****************************************************************/
  void KM0CAR::_backward() const {
    _rightEngine.backward(_backwardSpeed);
    _leftEngine.backward (_backwardSpeed);

    _luces.switchOn();
    //_bocina.beep(100);
  }

  /****************************************************************
   * void _turnRight() const
   ****************************************************************/
  void KM0CAR::_turnRight() const {
    _rightEngine.backward(_turnSpeed);
    _leftEngine.forward  (_turnSpeed);

    _luces.switchRight();
  }

  /****************************************************************
   * void _turnLeft() const
   ****************************************************************/
  void KM0CAR::_turnLeft() const {
    _rightEngine.forward(_turnSpeed);
    _leftEngine.backward(_turnSpeed);

    _luces.switchLeft();
  }

  /****************************************************************
   * void _flipRight() const
   ****************************************************************/
  void KM0CAR::_flipRight() const {
    _turnRight();

    delay(500);
  }

  /****************************************************************
   * void _flipLeft() const
   ****************************************************************/
  void KM0CAR::_flipLeft() const {
    _turnLeft();

    delay(500);
  }

  /****************************************************************
   * void _stopCar() const
   ****************************************************************/
  void KM0CAR::_stopCar() const {
    _rightEngine.stop();
    _leftEngine.stop ();

    _luces.switchOn();
    //_bocina.beep(2, 100);
  }

  /****************************************************************
   * void _setSpeed()
   ****************************************************************/
  void KM0CAR::_setSpeed() {
    if (DEBUG == true)
    {
      _forwardSpeed  = 0;
      _backwardSpeed = 0;
      _turnSpeed     = 0;
      return;
    }

    if (_motionMode == FORWARD) _forwardSpeed = (_sensors.getDistanceForward() > DISTANCE_MIN_FAST) ? FORWARD_SPEED_FAST : FORWARD_SPEEP_SLOW;
  }

  /****************************************************************
   * MotionModeEnum _setMotionModeLateral()
   * 
   * - TURN_RIGHT
   * - TURN_LEFT
   * - BACKWARD
   *  
   ****************************************************************/
  MotionModeEnum KM0CAR::_setMotionModeLateral() {
    //0.- Stop
    _stopCar();

    //1.- Get lateral distance
    _sensors.lateralDistance();

    //2.- Lateral is OK
    if (_sensors.isLateralOK() == true)
    {
      if      (_turnsCounter > 0) return _motionMode = TURN_RIGHT;
      else if (_turnsCounter < 0) return _motionMode = TURN_LEFT;

      return _motionMode = (_sensors.getDistanceLeft() > _sensors.getDistanceRight()) ? TURN_LEFT : TURN_RIGHT;
    }

    //3.- Right or Left is OK
    if ((_sensors.isIRRightOK() == true) && (_sensors.isDistanceRightOK() == true)) return _motionMode = TURN_RIGHT;
    if ((_sensors.isIRLeftOK()  == true) && (_sensors.isDistanceLeftOK()  == true)) return _motionMode = TURN_LEFT;

    //4.- Backward
    return _motionMode = BACKWARD;
  }

  /****************************************************************
   * MotionModeEnum _setMotionModeInAlert()
   * 
   * - BACKWARD
   * - TURN_RIGHT
   * - TURN_LEFT
   * - FORWARD
   *  
   ****************************************************************/
  MotionModeEnum KM0CAR::_setMotionModeInAlert() {
    //1.- Get DISTANCE
    _sensors.forwardDistance();

    //2.- All is OK
    if ((_sensors.isIROK() == true) && (_sensors.isDistanceForwardOK() == true))
    {
      _setAlert(false);

      return _motionMode = FORWARD;
    }

    //3.- Colission Alert
    if (_sensors.isAlertColission() == true) return _motionMode = BACKWARD;

    //4.- Is TURN RIGH OK
    if ((_turnsCounter > 0) && (_sensors.isIRRightOK() == true))  return _motionMode = TURN_RIGHT;

    //5.- Is TURN LEFT OK
    if ((_turnsCounter < 0) && (_sensors.isIRLeftOK() == true)) return _motionMode = TURN_LEFT;

    //6.- Get the direction of rotation
    _setMotionModeLateral();

    //7.- END
    return;
  }

  /****************************************************************
   * void _setMotionMode()
   * 
   * Sets the motion state of the car based on the information of
   * sensors:
   * - ALERT
   * - FORWARD
   * 
   ****************************************************************/
  void KM0CAR::_setMotionMode() {
    //1.- Get information from sensors
    _sensors.checkIRObstacle();

    //2.- Alert Mode
    if (_alert == true)
    {
      //1.1.- Alert Mode
      _setMotionModeInAlert();

      //1.2.- Varios ciclos en modo BACKWARD => FLIP MODE
      //if ((_backwardCounter > 0) && (_motionMode != BACKWARD)) _motionMode = _getFlipMode();

      //1.3.- OTHER CASE
      return;
    }

    //3.- IR NOT OK
    if (_sensors.isIROK() == false)
    {
      _setAlert(true);
      _motionMode = ALERT;

      return;
    }

    //4.- Get DISTANCE
    _sensors.forwardDistance();

    //5.- Distance NOT OK
    if (_sensors.isDistanceForwardOK() == false)
    {
      _setAlert(true);
      _motionMode = ALERT;

      return;
    }

    //6.- All is OK
    _motionMode = FORWARD;

    //7.- END
    return;
  }
  
  /****************************************************************
   * void init()
   ****************************************************************/
  void KM0CAR::init() {
    _motionMode = START;

    _rightEngine.init();
    _leftEngine.init();
    _bocina.init();
    _luces.init();
    _sensors.init();
  }

  /****************************************************************
   * void drive()
   * 
   * Rotate the engines based on the motion state of the car.
   * 
   ****************************************************************/
  void KM0CAR::drive() {
    //0.- If STOP then WAIT and RETURN
    if (_isStopped() == true)
    {
      delay(10000);
      return;
    }
    
    //1.- Get the state of motion of the car
    _setMotionMode();

    //2.- Speed
    _setSpeed();
    
    //3.- Rotate the engines based on the motion state of the car
    switch(_motionMode)
    {
      case START:      _turnsCounter = 0; _backwardCounter = 0; _stopCar();   break;
      case STOP:       _turnsCounter = 0; _backwardCounter = 0; _stopCar();   break;
      case ALERT:      _turnsCounter = 0; _backwardCounter = 0; _stopCar();   break;
      case FORWARD:    _turnsCounter = 0; _backwardCounter = 0; _forward();   break;
      case BACKWARD:   _turnsCounter = 0; _backwardCounter++;   _backward();  break;
      case TURN_LEFT:  _turnsCounter--;   _backwardCounter = 0; _turnLeft();  break;
      case TURN_RIGHT: _turnsCounter++;   _backwardCounter = 0; _turnRight(); break;
      case FLIP_LEFT:  _turnsCounter = 0; _backwardCounter = 0; _flipLeft();  break;
      case FLIP_RIGHT: _turnsCounter = 0; _backwardCounter = 0; _flipRight(); break;
      default:         _turnsCounter = 0; _backwardCounter = 0; _stopCar();   break;
    }
  }
}
