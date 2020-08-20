#include "pins.h"
#include "atom0globals.h"
#include "l298nEngine.h"

#ifndef ATOM0CAR_H
#define ATOM0CAR_H

namespace ATOM0 {

  class ATOM0CAR {
    private:
      unsigned long   _printPrevTime   = 0;
      MotionModeEnum  _motionMode;
      L298NEngine     _rightEngine;
      L298NEngine     _leftEngine;
      bool            _alert           = false;
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
        }
      }

      /****************************************************************
       * void _setAlert(bool x)
       * 
       ****************************************************************/
      void _setAlert(const bool x) {
        _alert = x;

        digitalWrite(PIN_LED_ALERT, (_alert == true) ? HIGH : LOW);
      }

      /****************************************************************
       * MotionModeEnum _setMotionModeInAlert()
       * 
       ****************************************************************/
      MotionModeEnum _setMotionModeInAlert(const Sensors sensors) {
        //1.- Todo OK
        if (sensors.isOK() == true)
        {
          _setAlert(false);
          return _motionMode = FORWARD;
        }

        //2.- Colission
        if (sensors.alertColission() == true) return _motionMode = BACKWARD;

        //3.- Izquierda OK
        if ((sensors.isLeftOK() == true) && (_turnsCounter == 0)) return _motionMode = TURN_LEFT;
  
        //4.- Derecha OK
        if ((sensors.isRightOK() == true) && (_turnsCounter == 0)) return _motionMode = TURN_RIGHT;

        //5.- Ya esta girando a Izquierda
        if (_turnsCounter < 0) return _motionMode = TURN_LEFT;
  
        //6.- Ya esta girando a Derecha
        if (_turnsCounter > 0) return _motionMode = TURN_RIGHT;

        //6.- Lateral Derecha & Izquierda FAIL
        if (sensors.isForwardOK()       == false) return _motionMode = BACKWARD;
        if (_backwardCounter            > 0)      return _motionMode = BACKWARD;

        //7-. Fin
        return _motionMode = FORWARD;
      }

      /****************************************************************
       * MotionModeEnum _setMotionMode()
       * 
       ****************************************************************/
      MotionModeEnum _setMotionMode(const Sensors sensors) {
        //1.- Estamos modo alerta
        if (_alert == true) return _setMotionModeInAlert(sensors);
        
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
       * void _stopCar()
       ****************************************************************/
      void _stopCar() {
        _rightEngine.stop();
        _leftEngine.stop ();
      }
      
    public:
      ATOM0CAR() : _rightEngine(PIN_EN_D, PIN_IN1_D, PIN_IN2_D),
                   _leftEngine (PIN_EN_I, PIN_IN1_I, PIN_IN2_I)
                   {}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _motionMode = START;

        _rightEngine.init();
        _leftEngine.init();

        pinMode(PIN_LED_ALERT, OUTPUT);
      }

      /****************************************************************
       * void drive()
       * 
       * Rotate the engines based on the motion state of the car.
       * 
       ****************************************************************/
      void drive() {
        switch(_motionMode)
        {
          case STOP:       _turnsCounter = 0; _backwardCounter = 0; _stopCar();   break;
          case ALERT:      _turnsCounter = 0; _backwardCounter = 0; _stopCar();   break;
          case FORWARD:    _turnsCounter = 0; _backwardCounter = 0; _forward();   break;
          case BACKWARD:   _turnsCounter = 0; _backwardCounter++;   _backward();  break;
          case TURN_LEFT:  _turnsCounter--;   _backwardCounter = 0; _turnLeft();  break;
          case TURN_RIGHT: _turnsCounter++;   _backwardCounter = 0; _turnRight(); break;
          //case FLIP_LEFT:  _turnsCounter = 0; _backwardCounter = 0; flipLeft();  break;
          //case FLIP_RIGHT: _turnsCounter = 0; _backwardCounter = 0; flipRight(); break;
          case START:      _turnsCounter = 0; _backwardCounter = 0; break;
          default:         _turnsCounter = 0; _backwardCounter = 0; break;
        }
      }

      /****************************************************************
       * void obstacleAvoidanceMode()
       * 
       * Gets the motion state of the car based on the information of
       * sensors.
       * 
       ****************************************************************/
      MotionModeEnum setMotionMode(const Sensors sensors) {
        //1.- Si esta parado nos vamos...
        if (_isStopped() == true) return;

        //2.- Obtenemos el estado en funcion de la info de los sensores
        _setMotionMode(sensors);
        
        if ((DEBUG == true) && ((millis() - _printPrevTime) > 500))
        {
          _printPrevTime = millis();
          
          Serial.print("Motion mode: ");  Serial.println(_motionMode2char());
          Serial.print("Center: "); Serial.print(sensors.getSensorDistance()); Serial.print("cm. ");
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
