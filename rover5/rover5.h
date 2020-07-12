#include "rover5globals.h"
#include "pins.h"
#include "l298nEngine.h"
#include "sensors.h"

#ifndef ROVER5_H
#define ROVER5_H

#define DEBUG true

/**
 * 
 */
namespace ROVER5
{
  class Rover5 {
    private:
      AlertSensorEnum _alertSensor;
      MotionModeEnum  _motionMode;
      L298NEngine     _rightEngine;
      L298NEngine     _leftEngine;
      bool            _alert;
      int             _forwardSpeed; //velocidad es 100x(_velocidad/255)
      int             _backwardSpeed;
      int             _turnSpeed;

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

        //2.- Izquierda OK
        if (sensors.isLeftOK() == true) return _motionMode = TURN_LEFT;

        //3.- Derecha OK
        if (sensors.isRightOK() == true) return _motionMode = TURN_RIGHT;

        //4.- Izquierda FAIL && Derecha FAIL
        if ((sensors.isLeftOK() == false) && (sensors.isRightOK() == false))
        {
          if (_alertSensor == SENSOR_FORWARD) return _motionMode = BACKWARD;
          if (sensors.isForwardOK() == false) return _motionMode = BACKWARD;
        }

        //5-. Todo OK
        _alert = false;
        return _motionMode = FORWARD;
      }

      /****************************************************************
       * MotionModeEnum _setMotionMode()
       * 
       ****************************************************************/
      MotionModeEnum _setMotionMode(Sensors sensors) {
        //1.- Comprobamos bateria
        if (sensors.isBatteryOK() == false) return _motionMode = STOP;

        //2.- Todo es OK
        if (sensors.isOK() == true) return _motionMode = FORWARD;

        //3.- Entramos en modo alerta
        _alert = true;
        _alertSensor = sensors.isForwardOK() == false ? SENSOR_FORWARD :
                       sensors.isLeftOK()    == false ? SENSOR_LEFT :
                       sensors.isRightOK()   == false ? SENSOR_RIGHT : SENSOR_NONE;

        return _motionMode = ALERT;
      }

    public:
      Rover5() : _rightEngine  (PIN_IN1_D, PIN_IN2_D),
                 _leftEngine   (PIN_IN1_I, PIN_IN2_I),
                 _alertSensor  (SENSOR_NONE),
                 _alert        (false),
                 _forwardSpeed (0),
                 _backwardSpeed(0),
                 _turnSpeed    (0)
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
        _rightEngine.forward();
        _leftEngine.forward ();
      }

      /****************************************************************
       * void backward()
       ****************************************************************/
      void backward() {
        _rightEngine.backward();
        _leftEngine.backward ();

        delay(100);
        stopCar();
      }

      /****************************************************************
       * void turnLeft()
       ****************************************************************/
      void turnLeft() {
        _rightEngine.forward();
        _leftEngine.backward();

        delay(100);
        stopCar();
      }

      /****************************************************************
       * void turnRight()
       ****************************************************************/
      void turnRight() {
        _rightEngine.backward();
        _leftEngine.forward  ();

        delay(100);
        stopCar();
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
          case STOP:       stopCar();   break;
          case ALERT:      stopCar();   break;
          case FORWARD:    forward();   break;
          case BACKWARD:   backward();  break;
          case TURN_LEFT:  turnLeft();  break;
          case TURN_RIGHT: turnRight(); break;
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

        if (DEBUG == true)
        {
          Serial.print("Motion mode: ");  Serial.println(_motionMode2char());
          Serial.print("Left: ");   Serial.print(sensors.getSensorLeftDistance());  Serial.print("cm. ");
          Serial.print("Center: "); Serial.print(sensors.getSensorDistance());      Serial.print("cm. ");
          Serial.print("Right: ");  Serial.print(sensors.getSensorRightDistance()); Serial.print("cm. ");
          Serial.println();
          Serial.println();
        }

        //3.- Fin.
        return _motionMode;
      }
  };
}
#endif
