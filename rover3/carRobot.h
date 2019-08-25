#include "carDriver.h"
#include "distanceSensor.h"

#ifndef CAR_ROBOT_H
#define CAR_ROBOT_H

namespace ROVER3
{
/**
 * Estado de movimiento del robot.
 */
enum state_t {
  INITIAL,
  STOPPED,
  FORWARD,
  TURNING,
  REVERSE_LEFT,
  REVERSE_RIGHT
};

enum positionObstacle_t {
  RIGHT,
  LEFT,
  FRONT_LEFT,
  FRONT_RIGHT,
  NONE
};

class CarRobot {
  private:
    DistanceSensor _sonar;
    DistanceSensor _sonarL;
    DistanceSensor _sonarR;
    CarDriver      _driver;
    state_t        _state;

    bool _isStopped() const {return _state == STOPPED;}

    bool _isTurning() const {return _state == TURNING;}

    /********************************************************************
     * Localiza un objeto:
     * - Al frente
     * - A la izquierda
     * - A la derecha
     ********************************************************************/
    positionObstacle_t _localizarObjeto() {
      unsigned int d;
      unsigned int dl;
      unsigned int dr;
      
      //1.- Comprobamos al frente
      d = _sonar.getDistancia();
      if (_sonar.hayObjetoCerca(d) == true)
      {
        detener();

        dl = _sonarL.getDistancia();
        dr = _sonarR.getDistancia();

        return (dl < dr) ? FRONT_LEFT : FRONT_RIGHT;
      }

      //2.- Comprobamos a la izquierda
      dl = _sonarL.getDistancia();
      if (_sonarL.hayObjetoCerca(dl) == true)
      {
        detener();

        dr = _sonarR.getDistancia();

        return (dl < dr) ? LEFT : RIGHT;
      }

      //3.- Comprobamos a la derecha
      dr = _sonarR.getDistancia();
      if (_sonarR.hayObjetoCerca(dr) == true) return RIGHT;

      //4.- Fin
      return NONE;
    }

    /********************************************************************
     * Localiza un objeto cercano y en función de este mueve el robot
     * en una dirección.
     * 
     ********************************************************************/
    state_t _algoritmo() {
      //1.- Si esta parado nos vamos...
      if (_isStopped() == true) return;

      //1.- Si esta girando paramos...
      if (_isTurning() == true) _driver.parar();

      //2.- Comprobamos si existe un obstaculo
      positionObstacle_t posicion = _localizarObjeto();
      Serial.print("Objeto localizado: "); Serial.println(posicion);
      
      switch (posicion)
      {
        case RIGHT:       girarIzquierda(); return _state;
        case LEFT:        girarDerecha();   return _state;
        case FRONT_LEFT:  backwardRight();  return _state;
        case FRONT_RIGHT: backwardLeft();   return _state;

        default:
          switch (_state)
          {
            case REVERSE_RIGHT: girarDerecha();   break;
            case REVERSE_LEFT:  girarIzquierda(); break;
            case INITIAL:       forward();        break;
            case TURNING:       forward();        break;
            case FORWARD:       break;
          }

          return _state;
      }
    }

  public:
    CarRobot(const CarDriver &driver, const DistanceSensor &sonar, const DistanceSensor &sonarL, const DistanceSensor &sonarR) :
      _sonar (sonar),
      _sonarL(sonarL),
      _sonarR(sonarR),
      _driver(driver)
    {}

    
    /********************************************************************
     * Inicializa el objeto.
     * 
     ********************************************************************/
    void init() {
      Serial.begin(9600);

      _state = INITIAL;

      _driver.init();
    }

    /********************************************************************
     * Detiene el robot.
     * 
     ********************************************************************/
    void detener() {
      _state = STOPPED;

      _driver.parar();
    }

    /********************************************************************
     * Mueve el robot hacia la izquierda.
     * 
     ********************************************************************/
    void girarIzquierda() {
      _state = TURNING;

      _driver.izquierda();
    }

    /********************************************************************
     * Mueve el robot hacia la derecha.
     * 
     ********************************************************************/
    void girarDerecha() {
      _state = TURNING;

      _driver.derecha();
    }

    /********************************************************************
     * Mueve el robot hacia adelante.
     * 
     ********************************************************************/
    void forward() {
      _state = FORWARD;

      _driver.forward();
    }

    /********************************************************************
     * Mueve el robot hacia atrás.
     * 
     ********************************************************************/
    void backwardLeft() {
      _state = REVERSE_LEFT;

      _driver.backward();
    }

    /********************************************************************
     * Mueve el robot hacia atrás.
     * 
     ********************************************************************/
    void backwardRight() {
      _state = REVERSE_RIGHT;

      _driver.backward();
    }
    
    /********************************************************************
     * Mueve el robot en una dirección en función de la localización de
     * los objetos.
     * 
     ********************************************************************/
    state_t mover() {
      return _algoritmo();
    }
  };
}

#endif
