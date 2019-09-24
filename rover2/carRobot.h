#include "distanceSensor.h"
#include "detectorObstaculos.h"
#include "carDriver.h"

#ifndef CAR_ROBOT_H
#define CAR_ROBOT_H

namespace ROVER2
{
enum state_t {
  INITIAL,
  STOPPED,
  FORWARD,
  TURNING,
  REVERSE_RIGHT,
  REVERSE_LEFT
};

class CarRobot {
  private:
    DetectorObstaculos _detector;
    CarDriver          _driver;
    state_t            _state;

    bool _isStopped() const {return _state == STOPPED;}

    void _stop() {
      _driver.stop();
      delay(10);
    }

    /**
     * Gira el robot
     */
    void _backwardRight() {
      _stop();
      
      _state = REVERSE_RIGHT;
      _driver.backward();
    }

    /**
     * Gira el robot
     */
    void _backwardLeft() {
      _stop();
      
      _state = REVERSE_LEFT;
      _driver.backward();
    }

    /**
     *  void _turnRight()
     *
     *  Gira el robot
     */
    void _turnRight() {
      //_stop();
      
      _state = TURNING;
      _driver.right();
    }

    /**
     * void _turnLeft()
     * 
     * Gira el robot
     */
    void _turnLeft() {
      //_stop();
      
      _state = TURNING;
      _driver.left();
    }

    /**
     * void _move()
     * 
     * Mueve hacia adelante el Robot.
     */
    void _move() {
      _state = FORWARD;
      _driver.forward();
    }

    /**
     * void _algorithm()
     * 
     * Algoritmo que controla el movimiento del robot.
     */
    void _algorithm() {
      //1.- Si esta parado nos vamos...
      if (_isStopped() == true) return;

      //2.- Comprobamos si existe un obstaculo
      switch (_detector.turn())
      {
        case RIGHT:       _turnLeft();      return;
        case LEFT:        _turnRight();     return;
        case FRONT_LEFT:  _backwardRight(); return;
        case FRONT_RIGHT: _backwardLeft();  return;

        //No hay objeto
        default:
          switch (_state)
          {
            case REVERSE_RIGHT: _turnRight(); return;
            case REVERSE_LEFT:  _turnLeft();  return;
            case INITIAL:       _move();      return;
            case STOPPED:       _move();      return;
            case TURNING:       _move();      return;
            case FORWARD:       return;
          }
      }
    }

    /**
     * 
     */
  public:
    CarRobot(const CarDriver &driver, const DetectorObstaculos &detector) :
      _detector(detector),
      _driver  (driver)
    {}

    /**
     * Inicializa el objeto.
     */
    void init() {
      _state = INITIAL;

      _detector.init();
      _driver.init();
    }

    /**
     * Detiene el robot.
     */
    state_t stop() {
      _state = STOPPED;
      _driver.stop();

      return _state;
    }


    /**
     * 
     */
    state_t run() {
      //1.- Algoritmo
      _algorithm();

      //2.- Fin
      return _state;
    }
};
}

#endif
