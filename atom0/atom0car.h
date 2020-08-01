#include "pins.h"
#include "atom0globals.h"
#include "l298nEngine.h"

#ifndef ATOM0CAR_H
#define ATOM0CAR_H

namespace ATOM0 {

  class ATOM0CAR {
    private:
      unsigned long   _printPrevTime = 0;
      MotionModeEnum  _motionMode;
      L298NEngine     _rightEngine;
      L298NEngine     _leftEngine;
      bool            _alert = false;
      int             _forwardSpeed;    //velocidad es 100x(_velocidad/255)%
      int             _backwardSpeed;
      int             _turnSpeed;
      int             _turnsInAlert  = 0;

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
       * MotionModeEnum _setMotionModeInAlert()
       * 
       ****************************************************************/
      MotionModeEnum _setMotionModeInAlert(Sensors sensors) {
        //1.- Todo OK
        if (sensors.isOK() == true)
        {
          _alert = false;
          return _motionMode = FORWARD;
        }

        //2.- Colission
        if (sensors.alertColission() == true) return _motionMode = BACKWARD;

        //3.- Izquierda OK
        if ((sensors.isLeftOK() == true) && (_turnsInAlert <= 0)) return _motionMode = TURN_LEFT;
  
        //4.- Derecha OK
        if ((sensors.isRightOK() == true) && (_turnsInAlert >= 0)) return _motionMode = TURN_RIGHT;

        //5.- Izquierda OK
        if (_turnsInAlert < 0) return _motionMode = TURN_LEFT;
  
        //6.- Derecha OK
        if (_turnsInAlert > 0) return _motionMode = TURN_RIGHT;

        //7-. Fin
        return _motionMode = BACKWARD;
      }

      /****************************************************************
       * MotionModeEnum _setMotionMode()
       * 
       ****************************************************************/
      MotionModeEnum _setMotionMode(Sensors sensors) {
        //1.- Todo es OK
        if (sensors.isOK() == true) return _motionMode = FORWARD;

        //2.- Entramos en modo alerta
        _alert = true;

        //3.- Fin
        return _motionMode = ALERT;
      }
      
    public:
      ATOM0CAR() : _rightEngine  (PIN_EN_D, PIN_IN1_D, PIN_IN2_D),
                   _leftEngine   (PIN_EN_I, PIN_IN1_I, PIN_IN2_I),
                   _forwardSpeed (FORWARD_SPEED),
                   _backwardSpeed(BACKWARD_SPEED),
                   _turnSpeed    (TURN_SPEED)
                   {}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _motionMode = START;

        _rightEngine.init();
        _leftEngine.init();
      }

      /****************************************************************
       * void forward()
       ****************************************************************/
      void forward() {
        _rightEngine.forward(_forwardSpeed);
        _leftEngine.forward (_forwardSpeed);
      }

      /****************************************************************
       * void backward()
       ****************************************************************/
      void backward() {
        _rightEngine.backward(_backwardSpeed);
        _leftEngine.backward (_backwardSpeed);
      }

      /****************************************************************
       * void turnLeft()
       ****************************************************************/
      void turnLeft() {
        _rightEngine.forward(_turnSpeed);
        _leftEngine.backward(_turnSpeed);
      }

      /****************************************************************
       * void turnRight()
       ****************************************************************/
      void turnRight() {
        _rightEngine.backward(_turnSpeed);
        _leftEngine.forward  (_turnSpeed);
      }

      /****************************************************************
       * void stopCar()
       ****************************************************************/
      void stopCar() {
        _rightEngine.stop();
        _leftEngine.stop ();
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
          case STOP:       stopCar();   _turnsInAlert = 0; break;
          case ALERT:      stopCar();   break;
          case FORWARD:    forward();   _turnsInAlert = 0; break;
          case BACKWARD:   backward();  break;
          case TURN_LEFT:  turnLeft();  _turnsInAlert--;  break;
          case TURN_RIGHT: turnRight(); _turnsInAlert++;  break;
          case START:      break;
          default:         break;
        }
      }

      /****************************************************************
       * void obstacleAvoidanceMode()
       * 
       * Gets the motion state of the car based on the information of
       * sensors.
       * 
       ****************************************************************/
      MotionModeEnum setMotionMode(Sensors sensors) {
        //1.- Si esta parado nos vamos...
        if (_isStopped() == true) return;

        //2.- Obtenemos el estado en funcion de la info de los sensores
        if (_alert == false) _setMotionMode       (sensors);
        else                 _setMotionModeInAlert(sensors);
        
        if ((DEBUG == true) && ((millis() - _printPrevTime) > 500))
        {
          _printPrevTime = millis();
          
          Serial.print("Motion mode: ");  Serial.println(_motionMode2char());
          Serial.print("Center: "); Serial.print(sensors.getSensorDistance());      Serial.print("cm. ");
          Serial.println();
          Serial.println();
        }

        //3.- Fin.
        return _motionMode;
      }
  };
}
#endif
