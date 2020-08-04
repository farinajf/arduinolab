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
      bool            _alert         = false;
      int             _forwardSpeed;    //velocidad es 100x(_velocidad/255)%
      int             _backwardSpeed;
      int             _turnSpeed;
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
       * MotionModeEnum _getFlipMode(Sensors sensors)
       * 
       * return:
       * - FLIP_LEFT
       * - FLIP_RIGHT
       * 
       ****************************************************************/
      MotionModeEnum _getFlipMode(Sensors sensors) {
        return _motionMode = (sensors.getSensorDistanceLeft() > sensors.getSensorDistanceRight()) ? FLIP_LEFT : FLIP_RIGHT;
      }

      /****************************************************************
       * MotionModeEnum _setMotionModeInAlert()
       * 
       * @deprecated
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
          if ((sensors.isLeftOK() == true) && (_turnsCounter < 0)) return _motionMode = TURN_LEFT;
  
          //3.2.- Derecha OK
          if ((sensors.isRightOK() == true) && (_turnsCounter > 0)) return _motionMode = TURN_RIGHT;

          //3.3.- Giros alternados
          if ((_turnsCounter < 0) && (sensors.getSensorDistanceRight() > sensors.getSensorDistanceLeft()))  return _motionMode = BACKWARD;
          if ((_turnsCounter > 0) && (sensors.getSensorDistanceLeft()  > sensors.getSensorDistanceRight())) return _motionMode = BACKWARD;

          //3.4.- Mejor opcion
          return _motionMode = (sensors.getSensorDistanceLeft() > sensors.getSensorDistanceRight()) ? TURN_LEFT : TURN_RIGHT;
        }

        //4.- Izquierda FAIL && Derecha FAIL && Forward FAIL
        if (sensors.isForwardOK() == false) return _motionMode = BACKWARD;

        //5-. Fin
        return _motionMode = _getFlipMode(sensors);
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

        //2.- Colission
        if (sensors.alertColission() == true) return _motionMode = BACKWARD;

        //3.- Lateral OK
        if (sensors.isLateralOK() == true)
        {
          //3.1.- Seguir girando a derechas
          if (_turnsCounter > 0) return _motionMode = TURN_RIGHT;

          //3.2.- Seguir girando a izquierdas
          if (_turnsCounter < 0) return _motionMode = TURN_LEFT;

          //3.3.- Seleccionar sentido de giro
          if (_turnsCounter == 0) return _motionMode = (sensors.getSensorDistanceLeft() > sensors.getSensorDistanceRight()) ? TURN_LEFT : TURN_RIGHT;
        }

        //4.- Lateral Derecha OK
        if (sensors.isLateralRightOK() == true)
        {
          if ((sensors.isDistanceRightOK() == true) && (_turnsCounter >= 0)) return _motionMode = TURN_RIGHT;

          return _motionMode = BACKWARD;
        }

        //5.- Lateral Izquierda OK
        if (sensors.isLateralLeftOK() == true)
        {
          if ((sensors.isDistanceLeftOK() == true) && (_turnsCounter <= 0)) return _motionMode = TURN_LEFT;

          return _motionMode = BACKWARD;
        }

        //6.- Lateral Derecha & Izquierda FAIL
        if (sensors.isDistanceRightOK() == false) return _motionMode = BACKWARD;
        if (sensors.isDistanceLeftOK()  == false) return _motionMode = BACKWARD;
        if (sensors.isForwardOK()       == false) return _motionMode = BACKWARD;
        if (_backwardCounter            > 0)      return _motionMode = BACKWARD;

        return _motionMode = FORWARD;
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
        //1.- Comprobamos bateria
        if (sensors.isBatteryOK() == false) return _motionMode = STOP;

        //2.- Estamos modo alerta
        if (_alert == true)
        {
          //2.1.- Modo alerta
          _setMotionModeInAlert2(sensors);

          //2.2.- Varios ciclos en modo BACKWARD => FLIP MODE
          if ((_backwardCounter > 0) && (_motionMode != BACKWARD)) _motionMode = _getFlipMode(sensors);

          //2.3.- OTHER CASE
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
       * void flipRight()
       ****************************************************************/
      void flipRight() {
        turnRight();

        delay(500);
      }

      /****************************************************************
       * void flipLeft()
       ****************************************************************/
      void flipLeft() {
        turnLeft();

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
          case STOP:       _turnsCounter = 0; _backwardCounter = 0; stopCar();   break;
          case ALERT:      _turnsCounter = 0; _backwardCounter = 0; stopCar();   break;
          case FORWARD:    _turnsCounter = 0; _backwardCounter = 0; forward();   break;
          case BACKWARD:   _turnsCounter = 0; _backwardCounter++;   backward();  break;
          case TURN_LEFT:  _turnsCounter--;   _backwardCounter = 0; turnLeft();  break;
          case TURN_RIGHT: _turnsCounter++;   _backwardCounter = 0; turnRight(); break;
          case FLIP_LEFT:  _turnsCounter = 0; _backwardCounter = 0; flipLeft();  break;
          case FLIP_RIGHT: _turnsCounter = 0; _backwardCounter = 0; flipRight(); break;
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
      MotionModeEnum setMotionMode(Sensors sensors) {
        //1.- Si esta parado nos vamos...
        if (_isStopped() == true) return;

        //2.- Obtenemos el estado en funcion de la info de los sensores
        _setMotionMode(sensors);

        if ((DEBUG == true) && (millis() - _printPrevTime) > 500)
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
