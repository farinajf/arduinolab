#include "globals.h"
#include "pins.h"
#include "l298nEngine.h"
#include "ultrasonic.h"

#ifndef ROVER4_H
#define ROVER4_H

#define DEBUG true

namespace ROVER4
{
  class Rover4 {
    private:
      MOTION_MODE_ENUM _motionMode;
      L298NEngine      _rightEngine;
      L298NEngine      _leftEngine;

      bool _isStopped() const {return _motionMode == STOP;}
      bool _isTurning() const {return (_motionMode == TURNLEFT) || (_motionMode == TURNRIGHT);}

      /**
       * 
       */
      void _stop () {
        _rightEngine.stop();
        _leftEngine.stop ();
      }

      /**
       * Print distance values.
       */
      void _printDistance(double dl, double d, double dr) const {
        if (DEBUG == false) return;
        
        Serial.print("Izquierda: ");  Serial.print(dl);
        Serial.print("   Centro: ");  Serial.print(d);
        Serial.print("   Derecha: "); Serial.print(dr);
        Serial.println();
      }


      /**
       * POSITION_OBSTACLE_ENUM _localizarObjeto()
       * 
       * Calcula la posicion de un objeto cercano:
       * - FRONT RIGHT
       * - FRONT LEFT
       * - RIGHT
       * - LEFT
       */
      POSITION_OBSTACLE_ENUM _localizarObjeto() {
        double d;
        double dr;
        double dl;

        //1.- Comprobamos al frente
        if ((d = getDistanceFront()) <= DISTANCE_MIN)
        {
          _stop();

          dr = getDistanceRight();
          dl = getDistanceLeft();

          _printDistance(dl, d, dr);

          return (dl < dr) ? FRONT_LEFT : FRONT_RIGHT;
        }

        //2.- Comprobamos a la izquierda
        dl = getDistanceLeft();

        //3.- Comprobamos a la derecha
        dr = getDistanceRight();

        _printDistance(dl, d, dr);

        //4.- Devolvemos el resultado
        return ((dl > DISTANCE_MIN_LATERAL) && (dr > DISTANCE_MIN_LATERAL)) ? NONE : (dl < dr) ? LEFT : RIGHT;
      }
      
    public:
      Rover4() : _rightEngine(PIN_IN1_D, PIN_IN2_D),
                 _leftEngine (PIN_IN1_I, PIN_IN2_I)
                 {}

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
        _motionMode = FORWARD;
        
        _rightEngine.forward();
        _leftEngine.forward();
      }

      /****************************************************************
       * void turnLeft()
       ****************************************************************/
      void turnLeft() {
        _motionMode = TURNLEFT;
        
        _rightEngine.forward();
        _leftEngine.backward();
      }

      /****************************************************************
       * void turnRight()
       ****************************************************************/
      void turnRight() {
        _motionMode = TURNRIGHT;
        
        _rightEngine.backward();
        _leftEngine.forward();
      }

      /****************************************************************
       * void backwardThenLeft()
       ****************************************************************/
      void backwardThenLeft() {
        _rightEngine.backward();
        _leftEngine.backward();
        
        _motionMode = BACKWARD_LEFT;
      }

      /****************************************************************
       * void backwardThenRight()
       ****************************************************************/
      void backwardThenRight() {
        _rightEngine.backward();
        _leftEngine.backward();
        
        _motionMode = BACKWARD_RIGHT;
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
        //1.- Si esta parado nos vamos...
        if (_isStopped() == true) return;

        //2.-
        if (_isTurning() == true)
        {
          delay(50);
        }

        //2.- Calcular la posicion de un objeto en la trayectoria de colision
        POSITION_OBSTACLE_ENUM position = _localizarObjeto();
        switch (position)
        {
          case RIGHT:       turnLeft();          return;
          case LEFT:        turnRight();         return;
          case FRONT_LEFT:  backwardThenRight(); return;
          case FRONT_RIGHT: backwardThenLeft();  return;

          default:
            switch (_motionMode)
            {
              case BACKWARD_RIGHT: turnRight(); return;
              case BACKWARD_LEFT:  turnLeft();  return;
              default:             forward();   return;
            }
        }
      }
  };
}

#endif
