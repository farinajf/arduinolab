#include "atom0.h"

namespace ATOM0 {
  /****************************************************************
   * String _motionMode2char() const
   ****************************************************************/
  String ATOM0::_motionMode2char() const {
    switch (_motionMode)
    {
      case START:      return "START";
      case STOP:       return "STOP";
      case ALERT:      return "ALERT";
      case FORWARD:    return "FORWARD";
      case BACKWARD:   return "BACKWARD";
      case TURN_LEFT:  return "TURN_LEFT";
      case TURN_RIGHT: return "TURN_RIGHT";
    }
  }

  /****************************************************************
   * void _setAlert(const bool x)
   ****************************************************************/
  void  ATOM0::_setAlert(const bool x) {
    _alert = x;

    digitalWrite(PIN_LED_ALERT, (_alert == true) ? HIGH : LOW);
  }

  /****************************************************************
   * void _forward() const
   ****************************************************************/
  void ATOM0::_forward() const {
    _rightEngine.forward(_forwardSpeed);
    _leftEngine.forward (_forwardSpeed);
  }

  /****************************************************************
   * void _backward() const
   ****************************************************************/
  void ATOM0::_backward() const {
    _rightEngine.backward(_backwardSpeed);
    _leftEngine.backward (_backwardSpeed);
  }

  /****************************************************************
   * void _turnRight() const
   ****************************************************************/
  void ATOM0::_turnRight() const {
    _rightEngine.backward(_turnSpeed);
    _leftEngine.forward  (_turnSpeed);
  }

  /****************************************************************
   * void _turnLeft() const
   ****************************************************************/
  void ATOM0::_turnLeft() const {
    _rightEngine.forward(_turnSpeed);
    _leftEngine.backward(_turnSpeed);
  }

  /****************************************************************
   * void _stopCar() const
   ****************************************************************/
  void ATOM0::_stopCar() const {
    _rightEngine.stop();
    _leftEngine.stop ();
  }

  /****************************************************************
   * void _setSpeed()
   ****************************************************************/
  void ATOM0::_setSpeed() {
    if (DEBUG == true)
    {
      _forwardSpeed  = 0;
      _backwardSpeed = 0;
      _turnSpeed     = 0;
      return;
    }

    //if (_motionMode == FORWARD) _forwardSpeed = (_sensors.getDistanceForward() > DISTANCE_MIN_FAST) ? FORWARD_SPEED_FAST : FORWARD_SPEEP_SLOW;
    _forwardSpeed = 0;
  }

  /****************************************************************
   * MotionModeEnum _setMotionModeLateral()
   * 
   * - TURN_RIGHT
   * - TURN_LEFT
   * - BACKWARD
   *  
   ****************************************************************/
  MotionModeEnum ATOM0::_setMotionModeLateral() {
    //0.- Stop
    _stopCar();

    //1.- Right or Left is OK
    if (_sensors.isIRRightOK() == true) return _motionMode = TURN_RIGHT;
    if (_sensors.isIRLeftOK()  == true) return _motionMode = TURN_LEFT;

    //2.- Backward
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
  MotionModeEnum ATOM0::_setMotionModeInAlert() {
    //1.- Get DISTANCE
    _sensors.distanceCalculate();

    //2.- All is OK
    if ((_sensors.isIROK() == true) && (_sensors.isDistanceOK() == true))
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
   * MotionModeEnum _setMotionMode()
   * 
   * Sets the motion state of the car based on the information of
   * sensors:
   * - ALERT
   * - FORWARD
   * 
   ****************************************************************/
  MotionModeEnum ATOM0::_setMotionMode() {
    //1.- Get information from sensors
    _sensors.checkIRObstacle();

    //2.- Alert Mode
    if (_alert == true) return _setMotionModeInAlert();

    //3.- IR NOT OK
    if (_sensors.isIROK() == false)
    {
      _setAlert(true);
      return _motionMode = ALERT;
    }

    //4.- Get DISTANCE
    _sensors.distanceCalculate();

    //5.- Distance NOT OK
    if (_sensors.isDistanceOK() == false)
    {
      _setAlert(true);
      return _motionMode = ALERT;
    }

    //6.- All is OK
    return _motionMode = FORWARD;
  }

  /****************************************************************
   * void init()
   ****************************************************************/
  void ATOM0::init() {
    _motionMode = START;

    _rightEngine.init();
    _leftEngine.init();
    _sensors.init();

    pinMode(PIN_LED_ALERT, OUTPUT);
  }

  /****************************************************************
   * void drive()
   * 
   * Rotate the engines based on the motion state of the car.
   * 
   ****************************************************************/
  void ATOM0::drive() {
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
      default:         _turnsCounter = 0; _backwardCounter = 0; break;
    }

    //4.- DEBUG
    if ((DEBUG == true) && ((millis() - _printPrevTime) > 500))
    {
          _printPrevTime = millis();
          
          Serial.print("Motion mode: ");  Serial.println(_motionMode2char());
          Serial.print("Center: "); Serial.print(_sensors.getDistance()); Serial.print("cm. ");
          Serial.println();
    }
  }
}
