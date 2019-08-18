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
    const int          _runtime;
    unsigned long      _endtime;
    state_t            _state;
    int                _delayTurnMax;

    bool _isDone    (unsigned long x) const {
      return (x >  _endtime);
    }
    bool _isStopped ()                const {
      return _state == STOPPED;
    }

    /**
       void _backward()

       Gira el robot
    */
    void _backward() {
      _state = TURNING;
      _driver.backward();
    }
    /**
       void _stop()

       Detiene el Robot.
    */
    void _stop() {
      _state = STOPPED;
      _driver.stop();
    }

    /**
       void _turnRight()

       Gira el robot
    */
    void _turnRight() {
      _state = TURNING;
      _driver.right();

      int x = random(_delayTurnMax);
      Serial.print("Random: "); Serial.println(x);
      delay(x);
    }

    /**
      void _turnLeft()

      Gira el robot
    */
    void _turnLeft() {
      _state = TURNING;
      _driver.left();

      int x = random(_delayTurnMax);
      Serial.print("Random: "); Serial.println(x);
      delay(x);
    }

    /**
       void _move()

       Mueve hacia adelante el Robot.
    */
    void _move() {
      _state = MOVING;
      _driver.forward();
    }

    /**
       void _algorithm()

       Algoritmo que controla el movimiento del robot.
    */
    void _algorithm(unsigned long time) {
      //1.- Si esta parado nos vamos...
      if (_isStopped() == true) return;

      //2.- Si se acabo el tiempo apagamos...
      if (_isDone(time) == true)
      {
        _stop();
        return;
      }

      //3.- Comprobamos si existe un obstaculo
      positionObstacle_t position = _detector.turn();
      switch (position)
      {
        case RIGHT: _turnLeft();  break;
        case LEFT:  _turnRight(); break;
        case FRONT: _backward();  break;
        default:    _move();      break;
      }

      //5.- Fin
      return;
    }

  public:
    CarRobot(const CarDriver &driver, const DetectorObstaculos &detector, const int runtime, const int delayTurnMax) :
      _detector    (detector),
      _driver      (driver),
      _runtime     (runtime),
      _delayTurnMax(delayTurnMax)
    {}

    /**
       void init()
    */
    void init() {
      _endtime = millis() + (_runtime * 1000L);
      _state   = MOVING;

      _detector.init();
      _driver.init();

      randomSeed(analogRead(0));
    }

    /**
       void run()
    */
    state_t run() {
      //0.- Instante actual
      unsigned long time = millis();

      //1.- Algoritmo
      _algorithm(time);

      //2.- Fin
      return _state;
    }
};
}

#endif
