#ifndef KM0CAR_H
#define KM0CAR_H

#include "globals.h"
#include "l298nEngine.h"
#include "bocina.h"

namespace KM0CAR {
  class KM0CAR {
    private:
      unsigned long   _printPrevTime = 0;
      MotionModeEnum  _motionMode;
      L298NEngine     _rightEngine;
      L298NEngine     _leftEngine;
      Bocina          _bocina;
      bool            _alert = false;
      int             _forwardSpeed    = FORWARD_SPEED_FAST; //velocidad es 100x(_velocidad/255)%
      int             _backwardSpeed   = BACKWARD_SPEED;
      int             _turnSpeed       = TURN_SPEED;
      int             _turnsCounter    = 0;
      int             _backwardCounter = 0;

      bool _isStopped() const {return _motionMode == STOP;}

      /****************************************************************
       * char[] _motionMode2char()
       * 
       ****************************************************************/
      String _motionMode2char() {
        switch (_motionMode)
        {
          case START:      return "START";
          case STOP:       return "STOP";
          case ALERT:      return "ALERT";
          case FORWARD:    return "FORWARD";
          case BACKWARD:   return "BACKWARD";
          case TURN_LEFT:  return "TURN_LEFT";
          case TURN_RIGHT: return "TURN_RIGHT";
          case FLIP_LEFT:  return "FLIP_LEFT";
          case FLIP_RIGHT: return "FLIP_RIGHT";
        }
      }

      /****************************************************************
       * void _setAlert(bool x)
       * 
       ****************************************************************/
      void _setAlert(bool x) {
        _alert = x;
      }

      /****************************************************************
       * MotionModeEnum _setMotionModeInAlert2(Sensors sensors)
       * 
       * return:
       *  - FORWARD
       *  - BACKWARD
       *  - TURN_RIGHT
       *  - TURN_LEFT
       *  
       ****************************************************************/
      MotionModeEnum _setMotionModeInAlert2(Sensors sensors) {
        //1.- Todo OK
        if (sensors.isOK() == true)
        {
          _setAlert(false);

          return _motionMode = FORWARD;
        }

        //2- No se detecta superficie
        if (sensors.isTrackingLineOK() == false) return _motionMode = ALERT;

        //3.- Colission
        if (sensors.alertColission() == true) return _motionMode = BACKWARD;

        //4.- Lateral OK
        return _motionMode = ALERT;
      }

      /****************************************************************
       * MotionModeEnum _setMotionMode(Sensors sensors)
       * 
       * return:
       *  - STOP
       *  - FORWARD
       *  - ALERT
       *  - FLIP_LEFT
       *  - FLIP_RIGHT
       *  - _setMotionModeInAlert2()
       *  
       ****************************************************************/
      MotionModeEnum _setMotionMode(Sensors sensors) {
        //1.- Estamos modo alerta
        if (_alert == true)
        {
          //1.1.- Modo alerta
          _setMotionModeInAlert2(sensors);

          //1.2.- Varios ciclos en modo BACKWARD => FLIP MODE
          //if ((_backwardCounter > 0) && (_motionMode != BACKWARD)) _motionMode = _getFlipMode(sensors);

          //1.3.- OTHER CASE
          return _motionMode;
        }

        //2.- Todo es OK
        if (sensors.isOK() == true) return _motionMode = FORWARD;

        //3.- Entramos en modo alerta
        _setAlert(true);

        //4.- Fin
        return _motionMode = ALERT;
      }

      /****************************************************************
       * void _forward()
       ****************************************************************/
      void _forward() {
        _rightEngine.forward(_forwardSpeed);
        _leftEngine.forward (_forwardSpeed);
      }

      /****************************************************************
       * void _backward()
       ****************************************************************/
      void _backward() {
        _rightEngine.backward(_backwardSpeed);
        _leftEngine.backward (_backwardSpeed);

        _bocina.beep(100);
      }

      /****************************************************************
       * void _turnLeft()
       ****************************************************************/
      void _turnLeft() {
        _rightEngine.forward(_turnSpeed);
        _leftEngine.backward(_turnSpeed);
      }

      /****************************************************************
       * void _turnRight()
       ****************************************************************/
      void _turnRight() {
        _rightEngine.backward(_turnSpeed);
        _leftEngine.forward  (_turnSpeed);
      }

      /****************************************************************
       * void _flipRight()
       ****************************************************************/
      void _flipRight() {
        _turnRight();

        delay(500);
      }

      /****************************************************************
       * void _flipLeft()
       ****************************************************************/
      void _flipLeft() {
        _turnLeft();

        delay(500);
      }

      /****************************************************************
       * void _stopCar()
       ****************************************************************/
      void _stopCar() {
        _rightEngine.stop();
        _leftEngine.stop ();

        _bocina.beep(2, 100);
      }

    public:
      KM0CAR() : _rightEngine(PIN_EN_D, PIN_IN1_D, PIN_IN2_D),
                 _leftEngine (PIN_EN_I, PIN_IN1_I, PIN_IN2_I)
                 {}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _motionMode = START;

        _rightEngine.init();
        _leftEngine.init();
        _bocina.init();
      }
      
      /****************************************************************
       * void drive()
       * 
       * Rotate the engines based on the motion state of the car.
       * 
       ****************************************************************/
      void drive() {
        if (DEBUG == true)
        {
          _forwardSpeed  = 0;
          _backwardSpeed = 0;
          _turnSpeed     = 0;
        }
        
        switch(_motionMode)
        {
          case STOP:       _turnsCounter = 0; _backwardCounter = 0; _stopCar();   break;
          case ALERT:      _turnsCounter = 0; _backwardCounter = 0; _stopCar();   break;
          case FORWARD:    _turnsCounter = 0; _backwardCounter = 0; _forward();   break;
          case BACKWARD:   _turnsCounter = 0; _backwardCounter++;   _backward();  break;
          case TURN_LEFT:  _turnsCounter--;   _backwardCounter = 0; _turnLeft();  break;
          case TURN_RIGHT: _turnsCounter++;   _backwardCounter = 0; _turnRight(); break;
          case FLIP_LEFT:  _turnsCounter = 0; _backwardCounter = 0; _flipLeft();  break;
          case FLIP_RIGHT: _turnsCounter = 0; _backwardCounter = 0; _flipRight(); break;
          case START:      _turnsCounter = 0; _backwardCounter = 0; break;
          default:         _turnsCounter = 0; _backwardCounter = 0; break;
        }
      }
      
      /****************************************************************
       * MotionModeEnum setMotionMode(Sensors sensors)
       * 
       * Sets the motion state of the car based on the information of
       * sensors.
       * 
       ****************************************************************/
      MotionModeEnum setMotionMode(Sensors sensors) {
        //1.- Si esta parado nos vamos...
        if (_isStopped() == true) return;

        //2.- Obtenemos el estado en funcion de la info de los sensores
        _setMotionMode(sensors);

        if ((DEBUG == true) && (millis() - _printPrevTime) > 500)
        {
          _printPrevTime = millis();
          
          Serial.print("Motion mode: ");  Serial.println(_motionMode2char());
          Serial.print("Center: "); Serial.print(sensors.getSensorDistance()); Serial.print("cm. ");
          Serial.println();
          Serial.println();
        }

        //3.- Velocidad
        if (sensors.isOK() == true) _forwardSpeed = (sensors.getSensorDistance() > DISTANCE_MIN_FAST) ? FORWARD_SPEED_FAST : FORWARD_SPEEP_SLOW;

        //4.- Fin.
        return _motionMode;
      }
  };
}
#endif
