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
   * void activeMode()
   * 
   * Estabelce el modo ACTIVO
   * 
   ****************************************************************/
  void RobotAction::activeMode() {
    //1.- ActionState
    this -> _actionState();

    //2.- Comprobar Legs State
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
   * void _getCrawlPoint(Point &p, Point direccion)
   * 
   * p = p + direccion
   * 
   ****************************************************************/
  void RobotAction::_getCrawlPoint(Point &p, Point direccion) {
    p = Point(p._x + direccion._x, p._y + direccion._y, p._z + direccion._z);
  }
  
  /****************************************************************
   * void _getCrawlPoints(RobotLegsPoints &points, Point direccion)
   * 
   * points._leg1 = points._leg1 + direccion
   * points._leg2 = points._leg2 + direccion
   * points._leg3 = points._leg3 + direccion
   * points._leg4 = points._leg4 + direccion
   * points._leg5 = points._leg5 + direccion
   * points._leg6 = points._leg6 + direccion
   * 
   ****************************************************************/
  void RobotAction::_getCrawlPoints(RobotLegsPoints &points, Point direccion) {
    this -> _getCrawlPoint(points._leg1, direccion);
    this -> _getCrawlPoint(points._leg2, direccion);
    this -> _getCrawlPoint(points._leg3, direccion);
    this -> _getCrawlPoint(points._leg4, direccion);
    this -> _getCrawlPoint(points._leg5, direccion);
    this -> _getCrawlPoint(points._leg6, direccion);
  }
}
