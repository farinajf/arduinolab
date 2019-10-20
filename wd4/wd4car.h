#include "wd4Globals.h"
#include "pins.h"
#include "l298nEngine.h"
#include "wd4algorithm.h"

#ifndef WD4CAR_H
#define WD4CAR_H

namespace WD4
{
  class WD4Car {
    private:
      enum MOTION_MODE_ENUM _motionMode;
      L298NEngine           _rightEngine;
      L298NEngine           _leftEngine;
      long int              _turnCount = 0;
      int                   _forwardSpeed;    // velocidad es 100x(_velocidad/255)%
      int                   _backwardSpeed;
      int                   _turnSpeed;
      char                  _obstacleAvoidanceFlag = 0;


    // PUBLIC
    public:
      WD4Car() : _rightEngine(PIN_EN_D, PIN_IN1_D, PIN_IN2_D),
                 _leftEngine (PIN_EN_I, PIN_IN1_I, PIN_IN2_I),
                 _forwardSpeed (0),
                 _backwardSpeed(0),
                 _turnSpeed    (0)
                 {}

      void setForwardSpeed (int x) {_forwardSpeed  = (MODO_PRUEBAS) ? 0 : x;}
      void setBackwardSpeed(int x) {_backwardSpeed = (MODO_PRUEBAS) ? 0 : x;}
      void setTurnSpeed    (int x) {_turnSpeed     = (MODO_PRUEBAS) ? 0 : x;}

      /****************************************************************
       * void init()
       ****************************************************************/
      void init() {
        _motionMode = START;
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
        _motionMode = STOP;
        _rightEngine.stop();
        _leftEngine.stop ();
      }

      /****************************************************************
       * void drive()
       ****************************************************************/
      void drive() {
        switch(_motionMode)
        {
          case STANDBY:   stopCar();   break;
          case FORWARD:   forward();   break;
          case BACKWARD:  backward();  break;
          case TURNLEFT:  turnLeft();  break;
          case TURNRIGHT: turnRight(); break;
          case STOP:      stopCar();   break;
          case START:     break;
          default:        break;
        }
      }

      /****************************************************************
       * void obstacleAvoidanceMode(int  distance,
       *                            int  distanceLeft,
       *                            int  distanceRight,
       *                            bool isObjectLeft,
       *                            bool isObjectRight)
       * 
       ****************************************************************/
      void obstacleAvoidanceMode(int d, int dl, int dr, bool iol, bool ior) {
        MOTION_MODE_ENUM motionModeOld = _motionMode;

        //1.- Calculamos el modo
        _motionMode = getMotionMode(d, dl, dr, iol, ior);

        //2.- Giramos el coche
        if ((motionModeOld == BACKWARD) && (_motionMode == FORWARD))
        {
          turnRight();
          delay(1000);
          _motionMode = STANDBY;
        }
      }
  };
}
#endif
