#include "pins.h"
#include "wd5globals.h"
#include "l298nEngine.h"

#ifndef WD5_CAR_H
#define WD5_CAR_H

namespace WD5 {
  class WD5CAR {
    private:
      unsigned long   _printPrevTime = 0;
      MotionModeEnum  _motionMode    = START;
      L298NEngine     _rightEngine;
      L298NEngine     _leftEngine;
      bool            _alert    = false;
      bool            _backward = false;
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
          case ALERT_FLIP: return "ALERT_FLIP";
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
      void _setAlert(bool x) {
        _alert        = x;
        _turnsInAlert = 0;
      }

      /****************************************************************
       * MotionModeEnum _setMotionModeInAlert()
       * 
       ****************************************************************/
      MotionModeEnum _setMotionModeInAlert(Sensors sensors) {
        //1.- Todo OK
        if (sensors.isOK() == true)
        {
          _setAlert(false);
          return _motionMode = FORWARD;
        }

        //2.- Colission
        if (sensors.alertColission() == true) return _motionMode = BACKWARD;

        //3.- Izquierda o Derecha OK
        if ((sensors.isLeftOK() == true) || (sensors.isRightOK() == true))
        {
          //3.1- Izquierda OK
          if ((sensors.isLeftOK() == true) && (_turnsInAlert < 0)) return _motionMode = TURN_LEFT;
  
          //3.2.- Derecha OK
          if ((sensors.isRightOK() == true) && (_turnsInAlert > 0)) return _motionMode = TURN_RIGHT;

          //3.3.- Giros alternados
          if ((_turnsInAlert < 0) && (sensors.getSensorDistanceRight() > sensors.getSensorDistanceLeft()))  return _motionMode = BACKWARD;
          if ((_turnsInAlert > 0) && (sensors.getSensorDistanceLeft()  > sensors.getSensorDistanceRight())) return _motionMode = BACKWARD;

          //3.4.- Mejor opcion
          _motionMode = (sensors.getSensorDistanceLeft() > sensors.getSensorDistanceRight()) ? TURN_LEFT : TURN_RIGHT;
          return _motionMode;
        }

        //4.- Izquierda FAIL && Derecha FAIL && Forward FAIL
        if (sensors.isForwardOK() == false) return _motionMode = BACKWARD;

        //5-. Fin
        return _motionMode = ALERT_FLIP;
      }

      /****************************************************************
       * MotionModeEnum _setMotionModeInAlert2()
       * 
       ****************************************************************/
      MotionModeEnum _setMotionModeInAlert2(Sensors sensors) {
        //1.- Todo OK
        if (sensors.isOK() == true)
        {
          _setAlert(false);

          return _motionMode = FORWARD;
        }

        //2.- Colission
        if (sensors.alertColission() == true) return _motionMode = BACKWARD;

        //3.- Lateral OK
        if (sensors.isLateralOK() == true)
        {
          //3.1.- Seguir girando a derechas
          if (_turnsInAlert > 0) return _motionMode = TURN_RIGHT;

          //3.2.- Seguir girando a izquierdas
          if (_turnsInAlert < 0) return _motionMode = TURN_LEFT;

          //3.3.- Seleccionar sentido de giro
          if (_turnsInAlert == 0) return _motionMode = (sensors.getSensorDistanceLeft() > sensors.getSensorDistanceRight()) ? TURN_LEFT : TURN_RIGHT;
        }

        //4.- Lateral Derecha OK
        if (sensors.isLateralRightOK() == true)
        {
          if ((sensors.isDistanceRightOK() == true) && (_turnsInAlert >= 0)) return _motionMode = TURN_RIGHT;

          return _motionMode = BACKWARD;
        }

        //5.- Lateral Izquierda OK
        if (sensors.isLateralLeftOK() == true)
        {
          if ((sensors.isDistanceLeftOK() == true) && (_turnsInAlert <= 0)) return _motionMode = TURN_LEFT;

          return _motionMode = BACKWARD;
        }

        //6.- Lateral Derecha & Izquierda FAIL
        if (sensors.isDistanceRightOK() == false) return _motionMode = BACKWARD;
        if (sensors.isDistanceLeftOK()  == false) return _motionMode = BACKWARD;
        if (sensors.isForwardOK()       == false) return _motionMode = BACKWARD;
        if (_backward                   == true)  return _motionMode = BACKWARD;

        return _motionMode = FORWARD;
      }

      /****************************************************************
       * MotionModeEnum _setMotionMode()
       * 
       ****************************************************************/
      MotionModeEnum _setMotionMode(Sensors sensors) {
        //1.- Comprobamos bateria
        if (sensors.isBatteryOK() == false) return _motionMode = STOP;

        //2.- Estamos modo alerta
        if (_alert == true)
        {
          _setMotionModeInAlert2(sensors);
          
          if ((_backward == true) && (_motionMode != BACKWARD)) return _motionMode = ALERT_FLIP;

          return _motionMode;
        }

        //3.- Todo es OK
        if (sensors.isOK() == true) return _motionMode = FORWARD;

        //4.- Entramos en modo alerta
        _setAlert(true);

        //5.- Fin
        return _motionMode = ALERT;
      }
      
    public:
      WD5CAR() : _rightEngine  (PIN_EN_D, PIN_IN1_D, PIN_IN2_D),
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
        _backward = true;
        
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
       * void flip()
       ****************************************************************/
      void flip() {
        _backward = false;
        
        _rightEngine.backward(_turnSpeed);
        _leftEngine.forward  (_turnSpeed);

        delay(500);
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
          case ALERT:      stopCar();   _turnsInAlert = 0; break;
          case FORWARD:    forward();   _turnsInAlert = 0; break;
          case BACKWARD:   backward();  _turnsInAlert = 0; break;
          case TURN_LEFT:  turnLeft();  _turnsInAlert--;   break;
          case TURN_RIGHT: turnRight(); _turnsInAlert++;   break;
          case ALERT_FLIP: flip();      _turnsInAlert = 0; break;
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
        _setMotionMode(sensors);

        if ((DEBUG == true) && ((millis() - _printPrevTime) > 500))
        {
          _printPrevTime = millis();
          
          Serial.print("Motion mode: ");  Serial.println(_motionMode2char());
          Serial.print("Left: ");   Serial.print(sensors.getSensorDistanceLeft());  Serial.print("cm. ");
          Serial.print("Center: "); Serial.print(sensors.getSensorDistance());      Serial.print("cm. ");
          Serial.print("Right: ");  Serial.print(sensors.getSensorDistanceRight()); Serial.print("cm. ");
          Serial.println();
          Serial.println();
        }

        //4.- Fin.
        return _motionMode;
      }
  };
}
#endif
