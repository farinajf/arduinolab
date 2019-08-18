#include "movingAverage.h"
#include "distanceSensor.h"
#include "detectorObstaculos.h"
#include "carDriver.h"

#ifndef CAR_ROBOT_H
#define CAR_ROBOT_H

namespace ROVER2
{
enum state_t {
  STOPPED,
  MOVING,
  TURNING
};

class CarRobot {
  private:
    DetectorObstaculos _detector;
    CarDriver          _driver;
    state_t            _state;

    bool _isStopped() const {return _state == STOPPED;}
    
    /**
     * Gira el robot
     */
    void _backward() {
      _state = TURNING;
      _driver.backward();
    }

    /**
     *  void _turnRight()
     *
     *  Gira el robot
     */
    void _turnRight() {
      _state = TURNING;
      _driver.right();
    }

    /**
     * void _turnLeft()
     * 
     * Gira el robot
     */
    void _turnLeft() {
      _state = TURNING;
      _driver.left();
    }

    /**
     * void _move()
     * 
     * Mueve hacia adelante el Robot.
     */
    void _move() {
      _state = MOVING;
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
      positionObstacle_t position = _detector.turn();
      switch (position)
      {
        case RIGHT: _turnLeft();  return;
        case LEFT:  _turnRight(); return;
        case FRONT: _backward();  return;
        default:    _move();      return;
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
      _state = MOVING;

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
