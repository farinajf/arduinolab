#include "pins.h"
#include "tankGlobals.h"
#include "l298nEngine.h"
#include "tankLeds.h"

#ifndef TANK_DRIVER_H
#define TANK_DRIVER_H

namespace TANK02
{
  class TankDriver
  {
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
       * 
       ****************************************************************/
      void _frontObstacle(int d, TankLeds leds) {
        switch (_obstacleAvoidanceFlag)
        {
          case 0:
              if (d < DISTANCE_MAX || d > DISTANCE_SUPER_MAX)
              {
                _obstacleAvoidanceFlag = 1;
                _motionMode            = STANDBY;
                leds.switchOnCenter();
              }
              else
              {
                _motionMode = FORWARD; //FORWARD
                leds.switchOff();
              }
              return;

          case 1:
              if (d >= DISTANCE_MAX && d <= DISTANCE_SUPER_MAX)
              {
                _obstacleAvoidanceFlag = 0;
                _motionMode = FORWARD; //FORWARD
                leds.switchOff();
              }
              else if (d >= DISTANCE_SUPER_MIN && d <= DISTANCE_MIN)
              {
                _motionMode = BACKWARD; //BACKWARD
                leds.switchOn();
              }
              else
              {
                if (_turnCount >= 0)
                {
                  _motionMode = TURNRIGHT; //TURNRIGHT
                  leds.switchOnRight();
                  _turnCount++;
                }
                else
                {
                  _motionMode = TURNLEFT; //TURNLEFT
                  leds.switchOnLeft();
                  _turnCount--;
                }
              }
              return;

          default: return;
        }
      }

      /****************************************************************
       * 
       ****************************************************************/
      void _lateralObstacle(int d, TankLeds leds, bool iol, bool ior) {
        //1.- Si hay objeto a ambos lados
        if (iol && ior)
        {
          if (d >= DISTANCE_MIN &&  d <= DISTANCE_MAX)
          {
            if (_turnCount >= 0)
            {
              _motionMode = TURNRIGHT;
              leds.switchOnRight();
              _turnCount++;
            }
            else
            {
              _motionMode = TURNLEFT;
              leds.switchOnLeft();
              _turnCount--;
            }
          }
          else
          {
            _motionMode = BACKWARD;
            leds.switchOn();
          }
        }
        //2.- Si hay objeto a la izquierda
        else if (iol && !ior)
        {
          _motionMode = TURNRIGHT;
          leds.switchOnRight();
          _turnCount++;
        }
        //3.- Si hay objeto a la derecha
        else if (!iol && ior)
        {
          _motionMode = TURNLEFT;
          leds.switchOnLeft();
          _turnCount--;
        }
        return;
      }

    public:
      TankDriver() : _rightEngine(PIN_EN_D, PIN_IN1_D, PIN_IN2_D),
                     _leftEngine (PIN_EN_I, PIN_IN1_I, PIN_IN2_I),
                     _forwardSpeed (0),
                     _backwardSpeed(0),
                     _turnSpeed    (0)
                     {}

      void setForwardSpeed (int x) {_forwardSpeed  = x;}
      void setBackwardSpeed(int x) {_backwardSpeed = x;}
      void setTurnSpeed    (int x) {_turnSpeed     = x;}
      
      /****************************************************************
       * 
       ****************************************************************/
      void init() {
        _motionMode = START;
      }

      /****************************************************************
       * 
       ****************************************************************/
      void forward() {
        _rightEngine.forward(_forwardSpeed);
        _leftEngine.forward (_forwardSpeed);
      }

      /****************************************************************
       * 
       ****************************************************************/
      void backward() {
        _rightEngine.backward(_backwardSpeed);
        _leftEngine.backward (_backwardSpeed);
      }

      /****************************************************************
       * 
       ****************************************************************/
      void turnLeft() {
        _rightEngine.forward(_turnSpeed);
        _leftEngine.backward(_turnSpeed);
      }

      /****************************************************************
       * 
       ****************************************************************/
      void turnRight() {
        _rightEngine.backward(_turnSpeed);
        _leftEngine.forward  (_turnSpeed);
      }

      /****************************************************************
       * 
       ****************************************************************/
      void stopCar() {
        _rightEngine.stop();
        _leftEngine.stop ();
      }

      /****************************************************************
       * 
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
       * 
       ****************************************************************/
      void obstacleAvoidanceMode(int d, TankLeds leds, bool iol, bool ior) {
        //Serial.print(d); Serial.print(" "); Serial.print(iol); Serial.print(" "); Serial.println(ior); 

        if (iol || ior) _lateralObstacle(d, leds, iol, ior);
        else            _frontObstacle  (d, leds);
      }
  };
}
#endif
