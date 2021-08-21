#include "robotAction.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  RobotAction::RobotAction() {}


  /****************************************************************
   * void init()
   * 
   ****************************************************************/
  void RobotAction::init() {
    //1.- Robot init
    _robot.init();

    //2.- Initial points
    _initialPoints = BOOT_POINTS;

    //3.- InitialPoins = BOOT_POINTS + (0, 0, _bodyLift)
    this -> _getCrawlPoints(_initialPoints, Point(0, 0, _bodyLift));
  }

  /****************************************************************
   * void changeBodyHeight(float h)
   * 
   ****************************************************************/
  void RobotAction::changeBodyHeight(float h) {
    RobotLegsPoints points;

    //0.- La altura debe ser negativa
    if (h > 0) h = -1.0 * h;
    
    //1.- ActionState
    this -> _actionState();

    //2.- Comprobar LEGS STATE
    if (_legsState != LegsState::CRAWL_STATE) this -> initialState();

    //3.- Comprobar MODE
    if (_mode != RobotMode::ACTIVE) this -> activeMode();

    //4.- Ajustar altura
    h = constrain(h, -45, 0);
    
    _bodyLift = RobotShape::DEFAULT_BODY_LIFT + h;

    //5.- Calcular nueva posicion
    _robot.getPointsNow(points);

    points._leg1._z = _bodyLift;
    points._leg2._z = _bodyLift;
    points._leg3._z = _bodyLift;
    points._leg4._z = _bodyLift;
    points._leg5._z = _bodyLift;
    points._leg6._z = _bodyLift;

    //6.- Mover patas a la nueva posicion
    this -> _legsMoveTo(points, _BODY_LIFT_STEP_DISTANCE);

    //7.- Actualizar LEGS STATE
    _legsState = LegsState::CRAWL_STATE;
  }

  /****************************************************************
   * void initialState()
   * 
   * Establece la posicion inicial
   *      Modo;       ACTIVE
   *      Legs State: CRAWL_STATE
   * 
   ****************************************************************/
  void RobotAction::initialState() {
    //1.- ActionState
    this -> _actionState();

    //2.- Comprobar LEGS STATE
    if      (_legsState == LegsState::CRAWL_STATE)      this -> activeMode();
    else if (_legsState == LegsState::TWIST_BODY_STATE) this -> _twistBody(Point(0, 0, _bodyLift - RobotShape::DEFAULT_BODY_LIFT), Point(0, 0, 0), 0);
    else if (_legsState == LegsState::LEG_MOVE_STATE)
    {
      RobotLegsPoints points;

      _robot.getPointsNow(points);

      points._leg1._z = _bodyLift;
      points._leg2._z = _bodyLift;
      points._leg3._z = _bodyLift;
      points._leg4._z = _bodyLift;
      points._leg5._z = _bodyLift;
      points._leg6._z = _bodyLift;

      this -> _legsMoveTo(points, _BODY_LIFT_STEP_DISTANCE);
    }

    _robot.getPointsNow(_lastChangeLegsStatePoints);

    _mode      = RobotMode::ACTIVE;
    _legsState = LegsState::CRAWL_STATE;
  }

  /****************************************************************
   * void legMoveToRelativelyDirectly(int leg, Point p)
   * 
   ****************************************************************/
  void RobotAction::legMoveToRelativelyDirectly(int leg, Point p) {
    RobotLegsPoints points;

    //1.- Obtener posicion actual
    _robot.getPointsNow(points);

    //2.- Calcular nueva posicion de la pata indicada
    switch(leg)
    {
      case 1:
          points._leg1._x += p._x;
          points._leg1._y += p._y;
          points._leg1._z += p._z;
          break;
          
      case 2:
          points._leg2._x += p._x;
          points._leg2._y += p._y;
          points._leg2._z += p._z;
          break;
          
      case 3:
          points._leg3._x += p._x;
          points._leg3._y += p._y;
          points._leg3._z += p._z;
          break;
          
      case 4:
          points._leg4._x += p._x;
          points._leg4._y += p._y;
          points._leg4._z += p._z;
          break;
          
      case 5:
          points._leg5._x += p._x;
          points._leg5._y += p._y;
          points._leg5._z += p._z;
          break;
          
      case 6:
          points._leg6._x += p._x;
          points._leg6._y += p._y;
          points._leg6._z += p._z;
          break;
    }

    //3.- Comprobar la nueva posicion
    if (_robot.checkPoints(points) == false) return;

    //4.- Mover para
    _robot.moveTo(points, _LEG_LIFT_STEP_DISTANCE);
  }

  /****************************************************************
   * void activeMode()
   * 
   * Estabelce el modo ACTIVO
   * 
   ****************************************************************/
  void RobotAction::activeMode() {
    //1.- ActionState
    this -> _actionState();

    //2.- Comprobar LEGS STATE
    if (_legsState != LegsState::CRAWL_STATE) this -> initialState();

    //3.- Si el modo es ACTIVE nos vamos...
    if (_mode == RobotMode::ACTIVE) return;

    //4.- Posicionar patas
    this -> _legsMoveToRelatively(Point(0, 0, _bodyLift), _BODY_LIFT_STEP_DISTANCE);

    //5.- Actualizar estado y modo
    _legsState = LegsState::CRAWL_STATE;
    _mode      = RobotMode::ACTIVE;
  }

  /****************************************************************
   * void sleepMode()
   * 
   * Estabelce el modo SLEEP
   * 
   ****************************************************************/
  void RobotAction::sleepMode() {
    //1.- ActionState
    this -> _actionState();

    //2.- Comprobar Legs State
    if (_legsState != LegsState::CRAWL_STATE) this -> initialState();

    //3.- Si el modo es SLEEP nos vamos...
    if (_mode == RobotMode::SLEEP) return;

    //4.- Posicionar patas
    this -> _legsMoveToRelatively(Point(0, 0, -_bodyLift), _BODY_LIFT_STEP_DISTANCE);

    //5.- Actualizar estado y modo
    _legsState = LegsState::CRAWL_STATE;
    _mode      = RobotMode::SLEEP;
  }

  /****************************************************************
   * void switchMode()
   * 
   * Estabelce el modo SLEEP
   * 
   ****************************************************************/
  void RobotAction::switchMode() {
    //1.- ActionState
    this -> _actionState();

    //2.- Si el modo es ACTIVE => SLEEP
    if (_mode == RobotMode::ACTIVE) this -> sleepMode();
    else                            this -> activeMode();
  }




  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/


  /****************************************************************
   * void _actionState()
   * 
   ****************************************************************/
  void RobotAction::_actionState() {
    if (_robot.getState() == RobotState::ACTION) return;

    // 1.- Reinicia el estado
    _robot.bootState();

    //2.- Establece el estado a ACTION
    _robot.setState(RobotState::ACTION);

    //3.- Modo SLEEP
    _mode = RobotMode::SLEEP;

    //4.- Estado de las patas: CRAWL_STATE
    _legsState = LegsState::CRAWL_STATE;

    //5.- Resetea el último cambio de posicion de las patas
    _lastChangeLegsStatePoints = _initialPoints;
  }

  /****************************************************************
   * void _getCrawlPoint(Point &p, Point delta)
   * 
   * p = p + delta
   * 
   ****************************************************************/
  void RobotAction::_getCrawlPoint(Point &p, Point delta) {
    p = Point(p, delta._x, delta._y, delta._z);
  }
  
  /****************************************************************
   * void _getCrawlPoints(RobotLegsPoints &points, Point delta)
   * 
   * points._leg1 = points._leg1 + delta
   * points._leg2 = points._leg2 + delta
   * points._leg3 = points._leg3 + delta
   * points._leg4 = points._leg4 + delta
   * points._leg5 = points._leg5 + delta
   * points._leg6 = points._leg6 + delta
   * 
   ****************************************************************/
  void RobotAction::_getCrawlPoints(RobotLegsPoints &points, Point delta) {
    this -> _getCrawlPoint(points._leg1, delta);
    this -> _getCrawlPoint(points._leg2, delta);
    this -> _getCrawlPoint(points._leg3, delta);
    this -> _getCrawlPoint(points._leg4, delta);
    this -> _getCrawlPoint(points._leg5, delta);
    this -> _getCrawlPoint(points._leg6, delta);
  }

  /****************************************************************
   * void _legsMoveTo(RobotLegsPoints points, float stepDistance)
   * 
   * Mueve las patas a la posicion absoulta POINTS.
   * 
   ****************************************************************/
  void RobotAction::_legsMoveTo(RobotLegsPoints points, float stepDistance) {
    //0.- Chequear la posicion final
    if (_robot.checkPoints(points) == false) return;

    //1.- Mover las patas a la posicion final
    _robot.moveTo(points, stepDistance);

    //2.- Esperar a completar movimiento
    _robot.waitUntilFree();
  }

  /****************************************************************
   * void _legsMoveToRelatively(Point p, float stepDistance)
   * 
   * Mueve las patas al punto P.
   * 
   ****************************************************************/
  void RobotAction::_legsMoveToRelatively(Point p, float stepDistance) {
    RobotLegsPoints points;

    //1.- Obtener la posicion actual de las patas
    _robot.getPointsNow(points);

    //2.- Calcular la nueva posicion
    this -> _getCrawlPoints(points, p);

    //3.- Mover las patas a la nueva posicion
    this -> _legsMoveTo(points, stepDistance);
  }
}
