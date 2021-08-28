#include "controller.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  RobotController::RobotController() {}


  /****************************************************************
   * void init()
   * 
   *  - Posicion inicial: BOOT_POINTS
   * 
   ****************************************************************/
  void RobotController::init() {
    //1.- Robot init
    _robot.init();

    //2.- Initial points
    _posicionInicial = BOOT_POINTS;

    //3.- InitialPoins = BOOT_POINTS + (0, 0, _bodyLift)
    this -> _addDelta(_posicionInicial, Point(0, 0, _altura));
  }
  

  /****************************************************************
   * void changeBodyHeight(float h)
   * 
   ****************************************************************/
  void RobotController::changeBodyHeight(float h) {
    RobotLegsPoints posicionActual;

    //1.- ActionState
    this -> _setActionState();

    //2.- Comprobar ESTADO_PATAS y MODO
    if ((_estadoPatas != LegsState::CRAWL_STATE) || (_modo != RobotMode::ACTIVE)) this -> setActiveMode();

    //4.- Ajustar altura
    h = constrain(h, -45, 0);
    
    _altura = RobotShape::DEFAULT_BODY_LIFT + h;

    //5.- Mover patas a la nueva altura
    this -> _setBodyHeight(_altura);

    //6.- Actualizar LEGS STATE
    _estadoPatas = LegsState::CRAWL_STATE;
  }
  

  /****************************************************************
   * void setActiveMode(()
   * 
   * Estabelce:
   *      - Modo;       ACTIVE
   *      - Legs State: CRAWL_STATE
   * 
   ****************************************************************/
  void RobotController::setActiveMode() {
    //1.- ActionState
    this -> _setActionState();

    //2.- Comprobar LEGS STATE
    if (_estadoPatas != LegsState::CRAWL_STATE) this -> setCrawlLegState();

    //3.- Si el modo es ACTIVE nos vamos...
    if (_modo == RobotMode::ACTIVE) return;

    //4.- Posicionar patas
    this -> _setBodyHeight(_altura);

    //5.- Actualizar estado y modo
    _estadoPatas = LegsState::CRAWL_STATE;
    _modo        = RobotMode::ACTIVE;
  }
  

  /****************************************************************
   * void setCrawlLegState()
   * 
   * Establece la posicion inicial
   *      Modo;       ACTIVE
   *      Legs State: CRAWL_STATE
   *      Z:          _bodyLift
   * 
   ****************************************************************/
  void RobotController::setCrawlLegState() {
    //1.- ActionState
    this -> _setActionState();

    //2.- Comprobar LEGS STATE
    if      (_estadoPatas == LegsState::CRAWL_STATE)      this -> setActiveMode ();
    else if (_estadoPatas == LegsState::TWIST_BODY_STATE) this -> _twistBody    (Point(0, 0, _altura - RobotShape::DEFAULT_BODY_LIFT), Point(0, 0, 0), 0);
    else if (_estadoPatas == LegsState::LEG_MOVE_STATE)   this -> _setBodyHeight(_altura);

    //_robot.getPointsNow(_lastChangeLegsStatePoints);

    _estadoPatas = LegsState::CRAWL_STATE;
  }
  

  /****************************************************************
   * void setSleepMode(()
   * 
   * Estabelce:
   *      - Modo;       SLEEP
   *      - Legs State: CRAWL_STATE
   * 
   ****************************************************************/
  void RobotController::setSleepMode() {
    //1.- ActionState
    this -> _setActionState();

    //2.- Comprobar LEGS STATE
    if (_estadoPatas != LegsState::CRAWL_STATE) this -> setCrawlLegState();

    //3.- Si el modo es ACTIVE nos vamos...
    if (_modo == RobotMode::SLEEP) return;

    //4.- Posicionar patas
    this -> _setBodyHeight(0);

    //5.- Actualizar estado y modo
    _estadoPatas = LegsState::CRAWL_STATE;
    _modo        = RobotMode::SLEEP;
  }

  /****************************************************************
   * void switchMode()
   * 
   * Estabelce el modo SLEEP
   * 
   ****************************************************************/
  void RobotController::switchMode() {
    //1.- ActionState
    this -> _setActionState();

    //2.- Si el modo es ACTIVE => SLEEP
    (_modo == RobotMode::ACTIVE) ? this -> setSleepMode() : this -> setActiveMode();
  }





  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * void _addDelta(RobotLegsPoints &points, Point delta)
   * 
   * points._legX = points._legX + delta           X=1,...,6
   * 
   ****************************************************************/
  void RobotController::_addDelta(RobotLegsPoints &points, Point delta) {
    this -> _addDelta(points._leg1, delta);
    this -> _addDelta(points._leg2, delta);
    this -> _addDelta(points._leg3, delta);
    this -> _addDelta(points._leg4, delta);
    this -> _addDelta(points._leg5, delta);
    this -> _addDelta(points._leg6, delta);
  }

  /****************************************************************
   * void _addDelta(Point &p, Point delta)
   * 
   * p = p + delta
   * 
   ****************************************************************/
  void RobotController::_addDelta(Point &p, Point delta) {
    p = Point(p, delta._x, delta._y, delta._z);
  }

  /****************************************************************
   * void _setBodyHeight(float h)
   * 
   ****************************************************************/
  void RobotController::_setBodyHeight(float h) {
    RobotLegsPoints posicionActual;

    //1.- Calcular nueva posicion
    _robot.getPointsNow(posicionActual);

    posicionActual._leg1._z = h;
    posicionActual._leg2._z = h;
    posicionActual._leg3._z = h;
    posicionActual._leg4._z = h;
    posicionActual._leg5._z = h;
    posicionActual._leg6._z = h;

    //2.- Mover patas a la nueva posicion
    this -> _move(posicionActual, _BODY_LIFT_STEP_DISTANCE);
  }

  /****************************************************************
   * void _move(RobotLegsPoints points, float stepDistance)
   * 
   * Mueve las patas a la posicion absoulta POINTS.
   * 
   ****************************************************************/
  void RobotController::_move(RobotLegsPoints points, float stepDistance) {
    //0.- Chequear la posicion final
    if (_robot.checkPoints(points) == false) return;

    //1.- Mover las patas a la posicion final
    _robot.move(points, stepDistance);

    //2.- Esperar a completar movimiento
    _robot.waitUntilFree();
  }

  /****************************************************************
   * void _setActionState()
   * 
   * Establece:
   *    - Estado robot: BOOT
   *    - Posicion:     BOOT_POINTS
   *    - Modo:         SLEEP
   *    - Estado patas: CRAWL_STATE
   * 
   ****************************************************************/
  void RobotController::_setActionState() {
    //1.- Si el estado es ACTION nos vamos
    if (_robot.getState() == RobotState::ACTION) return;

    //2.- Reinicia el estado
    _robot.bootState();

    //3.- Establece el estado a ACTION
    _robot.setState(RobotState::ACTION);

    //4.- Modo SLEEP
    _modo = RobotMode::SLEEP;

    //5.- Estado de las patas: CRAWL_STATE
    _estadoPatas = LegsState::CRAWL_STATE;

    //6.- Resetea el último cambio de posicion de las patas
    //_lastChangeLegsStatePoints = _initialPoints;
  }

}
