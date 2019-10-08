#include "wd4Globals.h"
#include "pins.h"
#include "l298nEngine.h"

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

      /****************************************************************
       * void _frontObstacle(int distance)
       * 
       ****************************************************************/
      void _frontObstacle(int d) {
        switch (_obstacleAvoidanceFlag)
        {
          case 0:
              if (d < DISTANCE_MAX || d > DISTANCE_SUPER_MAX)
              {
                _obstacleAvoidanceFlag = 1;
                _motionMode            = STANDBY;
              }
              else
              {
                _motionMode = FORWARD; //FORWARD
              }
              return;

          case 1:
              if (d >= DISTANCE_MAX && d <= DISTANCE_SUPER_MAX)
              {
                _obstacleAvoidanceFlag = 0;
                _motionMode = FORWARD; //FORWARD
              }
              else if (d >= DISTANCE_SUPER_MIN && d <= DISTANCE_MIN)
              {
                _motionMode = BACKWARD; //BACKWARD
              }
              else
              {
                if (_turnCount >= 0)
                {
                  _motionMode = TURNRIGHT; //TURNRIGHT
                  _turnCount++;
                }
                else
                {
                  _motionMode = TURNLEFT; //TURNLEFT
                  _turnCount--;
                }
              }
              return;

          default: return;
        }
      }

      /****************************************************************
       * void _lateralObstacleIR(int d, bool iol, bool ior)
       * 
       ****************************************************************/
      void _lateralObstacleIR(int d, bool iol, bool ior) {
        //1.- Si hay objeto a ambos lados
        if (iol && ior)
        {
          _motionMode = BACKWARD;
        }
        //2.- Si hay objeto a la izquierda
        else if (iol && !ior)
        {
          _motionMode = TURNRIGHT;
          _turnCount++;
        }
        //3.- Si hay objeto a la derecha
        else if (!iol && ior)
        {
          _motionMode = TURNLEFT;
          _turnCount--;
        }

        //4.- Fin
        return;
      }

      /****************************************************************
       * void _lateralObstacle(int d, bool dl_low, bool dr_low)
       * 
       ****************************************************************/
      void _lateralObstacle(int d, bool dl_low, bool dr_low) {
        //1.- Si hay objeto a ambos lados
        if (dl_low && dr_low)
        {
          if (d >= DISTANCE_MIN &&  d <= DISTANCE_MAX)
          {
            if (_turnCount >= 0)
            {
              _motionMode = TURNRIGHT;
              _turnCount++;
            }
            else
            {
              _motionMode = TURNLEFT;
              _turnCount--;
            }
          }
          else
          {
            _motionMode = BACKWARD;
          }
        }
        //2.- Si hay objeto a la izquierda
        else if (dl_low && !dr_low)
        {
          _motionMode = TURNRIGHT;
          _turnCount++;
        }
        //3.- Si hay objeto a la derecha
        else if (!dl_low && dr_low)
        {
          _motionMode = TURNLEFT;
          _turnCount--;
        }

        //4.- Fin
        return;
      }

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
        bool dl_low = dl < DISTANCE_MIN_LATERAL;
        bool dr_low = dr < DISTANCE_MIN_LATERAL;
        
        if      (iol    || ior)    _lateralObstacleIR(d, iol,    ior);
        else if (dl_low || dr_low) _lateralObstacle  (d, dl_low, dr_low);
        else                       _frontObstacle    (d);
      }
  };
}
#endif
