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
   * void crawlForward()
   * void crawlBackward()
   * void crawlLeft()
   * void crawlRight()
   * void turnLeft()
   * void turnRight()
   * 
   ****************************************************************/
  void RobotAction::crawlForward()  {this -> crawl(0,                  _DISTANCIA_CRAWL,  0);}
  void RobotAction::crawlBackward() {this -> crawl(0,                 -_DISTANCIA_CRAWL,  0);}
  
  void RobotAction::crawlLeft()     {this -> crawl(-_DISTANCIA_CRAWL,  0,                 0);}
  void RobotAction::crawlRight()    {this -> crawl( _DISTANCIA_CRAWL,  0,                 0);}
  
  void RobotAction::turnLeft()      {this -> crawl(0,                  0,                -_ANGULO_GIRO);}
  void RobotAction::turnRight()     {this -> crawl(0,                  0,                 _ANGULO_GIRO);}
  

  /****************************************************************
   * void crawl(float x, float y, float angulo)
   * 
   ****************************************************************/
  void RobotAction::crawl(float x, float y, float angulo) {
    //1.- ActionState
    this -> _actionState();

    //2.- Comprobar LEGS STATE
    if (_legsState != LegsState::CRAWL_STATE) this -> initialState();

    //3.- Comprobar MODE
    if (_mode != RobotMode::ACTIVE) this -> activeMode();

    //4.- Check parametros
    float distancia = sqrt(x*x + y*y);
    if (distancia > _DISTANCIA_CRAWL)
    {
      x = x * _DISTANCIA_CRAWL/distancia;
      y = y * _DISTANCIA_CRAWL/distancia;
    }

    angulo = constrain(angulo, -_ANGULO_GIRO, _ANGULO_GIRO);

    //5.- Normalizar parametros
    x      = x      / _crawlSteps;
    y      = y      / _crawlSteps;
    angulo = angulo / _crawlSteps;

    //6.- Calcular movimientos
    RobotLegsPoints points1;
    _robot.getPointsNow(points1);

    RobotLegsPoints points2 = points1;
    this -> _getCrawlPoints(points2, Point(-x / 2, -y / 2, 0));
    this -> _getTurnPoints (points2, -angulo / 2);

    RobotLegsPoints points3 = points1;
    this -> _getCrawlPoints(points3, Point(-x, -y, 0));
    this -> _getTurnPoints (points3, -angulo);

    RobotLegsPoints points4 = BOOT_POINTS;
    this -> _getCrawlPoints(points4, Point(x  * (_crawlSteps - 1) / 4, y  * (_crawlSteps - 1) / 4, _bodyLift + _LEG_LIFT));
    this -> _getTurnPoints (points4, angulo   * (_crawlSteps - 1) / 4);

    RobotLegsPoints points5 = BOOT_POINTS;
    this -> _getCrawlPoints(points5, Point(x * (_crawlSteps - 1) / 2, y  * (_crawlSteps - 1) / 2, _bodyLift));
    this -> _getTurnPoints (points5, angulo  * (_crawlSteps - 1) / 2);

    (_legMoveIndex < _crawlSteps) ? _legMoveIndex++ : _legMoveIndex = 1;

    switch (_crawlSteps)
    {
      case 2:
          switch (_legMoveIndex)
          {
            case 1:
                points2._leg1 = points4._leg1;
                points3._leg1 = points5._leg1;
                points2._leg3 = points4._leg3;
                points3._leg3 = points5._leg3;
                points2._leg5 = points4._leg5;
                points3._leg5 = points5._leg5;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg1._z = points1._leg1._z;
                    points3._leg3._z = points1._leg3._z;
                    points3._leg5._z = points1._leg5._z;
                  }
                  this -> _legsMoveTo(points2, 1, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 1, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
    
            case 2:
                points2._leg2 = points4._leg2;
                points3._leg2 = points5._leg2;
                points2._leg4 = points4._leg4;
                points3._leg4 = points5._leg4;
                points2._leg6 = points4._leg6;
                points3._leg6 = points5._leg6;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg2._z = points1._leg2._z;
                    points3._leg4._z = points1._leg4._z;
                    points3._leg6._z = points1._leg6._z;
                  }
                  this -> _legsMoveTo(points2, 2, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 2, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
          }
          break;
          
      case 4:
          switch (_legMoveIndex)
          {
            case 1:
                points2._leg1 = points4._leg1;
                points3._leg1 = points5._leg1;
                points2._leg6 = points4._leg6;
                points3._leg6 = points5._leg6;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3 = points2;
                    points3._leg1._z = points1._leg1._z;
                    points3._leg6._z = points1._leg6._z;
                  }
                  this -> _legsMoveTo(points2, 1, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 1, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 2:
                points2._leg5 = points4._leg5;
                points3._leg5 = points5._leg5;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg5._z = points1._leg5._z;
                  }
                  this -> _legsMoveTo(points2, 5, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 5, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
    
            case 3:
                points2._leg3 = points4._leg3;
                points3._leg3 = points5._leg3;
                points2._leg4 = points4._leg4;
                points3._leg4 = points5._leg4;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg3._z = points1._leg3._z;
                    points3._leg4._z = points1._leg4._z;
                  }
                  this -> _legsMoveTo(points2, 3, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 3, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 4:
                points2._leg2 = points4._leg2;
                points3._leg2 = points5._leg2;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg2._z = points1._leg2._z;
                  }
                  this -> _legsMoveTo(points2, 2, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 2, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
          }
          break;
          
      case 6:
          switch (_legMoveIndex)
          {
            case 1:
                points2._leg1 = points4._leg1;
                points3._leg1 = points5._leg1;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3 = points2;
                    points3._leg1._z = points1._leg1._z;
                  }
                  this -> _legsMoveTo(points2, 1, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 1, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
    
            case 2:
                points2._leg5 = points4._leg5;
                points3._leg5 = points5._leg5;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg5._z = points1._leg5._z;
                  }
                  this -> _legsMoveTo(points2, 5, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 5, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 3:
                points2._leg3 = points4._leg3;
                points3._leg3 = points5._leg3;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg3._z = points1._leg3._z;
                  }
                  this -> _legsMoveTo(points2, 3, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 3, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 4:
                points2._leg4 = points4._leg4;
                points3._leg4 = points5._leg4;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg4._z = points1._leg4._z;
                  }
                  this -> _legsMoveTo(points2, 4, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 4, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 5:
                points2._leg2 = points4._leg2;
                points3._leg2 = points5._leg2;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg2._z = points1._leg2._z;
                  }
                  this -> _legsMoveTo(points2, 2, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 2, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 6:
                points2._leg6 = points4._leg6;
                points3._leg6 = points5._leg6;
                if (this -> _checkCrawlPoints(points2))
                {
                  if (this -> _checkCrawlPoints(points3) == false)
                  {
                    points3          = points2;
                    points3._leg6._z = points1._leg6._z;
                  }
                  this -> _legsMoveTo(points2, 6, _LEG_LIFT_STEP_DISTANCE);
                  this -> _legsMoveTo(points3, 6, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
          }
          break;
    }

    _legsState = LegsState::CRAWL_STATE;
  }

  /****************************************************************
   * void initialState()
   * 
   * Establece la posicion inicial
   *      Modo;       ACTIVE
   *      Legs State: CRAWL_STATE
   *      Z:          _bodyLift
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
   * void legMoveToRelatively(int leg, Point p)
   * 
   ****************************************************************/
  void RobotAction::legMoveToRelatively(int leg, Point p) {
    //1.- ActionState
    this -> _actionState();

    //2.- Comprobar LEGS STATE
    if (_legsState == LegsState::LEG_MOVE_STATE) this -> initialState();

    //3.- Mover pata
    this -> legMoveToRelativelyDirectly(leg, p);
    _robot.waitUntilFree();

    //4.- Actualizar estado
    _legsState = LegsState::LEG_MOVE_STATE;
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
   * void moveBody(float x, float y, float z)
   * 
   ****************************************************************/
  void RobotAction::moveBody(float x, float y, float z) {
    this -> twistBody(Point(x, y, z), Point(0, 0, 0));
  }

  /****************************************************************
   * void rotateBody(float x, float y, float z)
   * 
   ****************************************************************/
  void RobotAction::rotateBody(float x, float y, float z) {
    this -> twistBody(Point(0, 0, 0), Point(x, y, z));
  }

  /****************************************************************
   * void setActionGroup(int x)
   * 
   ****************************************************************/
  void RobotAction::setActionGroup(int x) {
    switch (x)
    {
      case 2:  _crawlSteps = 4; return;
      case 3:  _crawlSteps = 6; return;
      default: _crawlSteps = 2; return;
    }
  }

  /****************************************************************
   * void setSpeedMultiple(float x)
   * 
   ****************************************************************/
  void RobotAction::setSpeedMultiple(float x) {
    _robot.setSpeedMultiple(x);
  }

  /****************************************************************
   * void twistBody(Point move, Point rotate)
   * 
   * move:   desplazamiento
   * rotate: direccion del eje de rotacion; su magnitud es el angulo de rotacion
   * 
   ****************************************************************/
  void RobotAction::twistBody(Point move, Point rotate) {
    //1.- El angulo de rotacion es la magnitud del vector de rotacion
    float angulo = rotate.norma2();

    //2.- Mover robot
    this -> _twistBody(move, rotate, angulo);
  }

  /****************************************************************
   * void activeMode(()
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
   * Establece:
   *         RobotState:                ACTION
   *         LegsState:                 CRAWL_STATE
   *         lastChangeLegsStatePoints: BOOT_POINTS
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
   * bool _checkCrawlPoints(RobotLegsPoints points)
   * 
   * Establece:
   *         RobotState:                ACTION
   *         LegsState:                 CRAWL_STATE
   *         lastChangeLegsStatePoints: BOOT_POINTS
   * 
   ****************************************************************/
  bool RobotAction::_checkCrawlPoints(RobotLegsPoints points) {
    float alpha1;
    float alpha2;
    float alpha3;
    float alpha4;
    float alpha5;
    float alpha6;
    float beta;
    float gamma;

    _robot.getLeg1().calculateAngle(points._leg1, alpha1, beta, gamma);
    _robot.getLeg2().calculateAngle(points._leg2, alpha2, beta, gamma);
    _robot.getLeg3().calculateAngle(points._leg3, alpha3, beta, gamma);
    _robot.getLeg4().calculateAngle(points._leg4, alpha4, beta, gamma);
    _robot.getLeg5().calculateAngle(points._leg5, alpha5, beta, gamma);
    _robot.getLeg6().calculateAngle(points._leg6, alpha6, beta, gamma);

    if (alpha1 < 0) alpha1 += 360;
    if (alpha2 < 0) alpha2 += 360;
    if (alpha3 < 0) alpha3 += 360;
    if (alpha4 < -180) alpha4 += 360; else if (alpha4 > 180) alpha4 -= 360;
    if (alpha5 < -180) alpha4 += 360; else if (alpha5 > 180) alpha4 -= 360;
    if (alpha6 < -180) alpha4 += 360; else if (alpha6 > 180) alpha4 -= 360;

    if (alpha1 < 90 || alpha1 > 180 || alpha3 < 180 || alpha3 > 270) return false;
    if (alpha4 <  0 || alpha4 > 90  || alpha6 < -90 || alpha6 >   0) return false;
    if (alpha2 - alpha1 < _MIN_ALPHA_INTERVAL) return false;
    if (alpha3 - alpha2 < _MIN_ALPHA_INTERVAL) return false;
    if (alpha4 - alpha5 < _MIN_ALPHA_INTERVAL) return false;
    if (alpha5 - alpha6 < _MIN_ALPHA_INTERVAL) return false;

    return true;
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
   * points._legX = points._legX + delta           X=1,...,6
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
   * void _getMoveBodyPoint(Point &p, Point delta)
   * 
   * p = p + delta
   * 
   * OJO
   * 
   ****************************************************************/
  void RobotAction::_getMoveBodyPoint(Point &p, Point delta) {
    p = Point(p, delta._x, delta._y, delta._z);
  }

  /****************************************************************
   * void _getMoveBodyPoints(RobotLegsPoints &points, Point delta)
   * 
   * points._legX = points._legX - delta           X=1,...,6
   * 
   ****************************************************************/
  void RobotAction::_getMoveBodyPoints(RobotLegsPoints &points, Point delta) {
    this -> _getMoveBodyPoint(points._leg1, delta);
    this -> _getMoveBodyPoint(points._leg2, delta);
    this -> _getMoveBodyPoint(points._leg3, delta);
    this -> _getMoveBodyPoint(points._leg4, delta);
    this -> _getMoveBodyPoint(points._leg5, delta);
    this -> _getMoveBodyPoint(points._leg6, delta);
  }

  /****************************************************************
   * void _getRotateBodyPoint(Point &p, Point r, float alpha)
   * 
   * r:     eje de rotacion
   * alpha: angulo de rotacion
   * 
   * Mtriz de transformacion:
   * 
   *       | r.x*r.x*(1 - cos(alpha)) + cos(alpha)         r.x*r.y*(1 - cos(alpha)) - r.z*sin(alpha)     r.x*r.z*(1 - cos(alpha)) + r.y*sin(alpha) |
   *       |                                                                                                                                       |
   *   T = | r.x*r.y*(1 - cos(alpha)) + r.z*sin(alpha)     r.y*r.y*(1 - cos(alpha)) + cos(alpha)         r.y*r.z*(1 - cos(alpha)) - r.x*sin(alpha) |
   *       |                                                                                                                                       |
   *       | r.x*r.z*(1 - cos(alpha)) - r.y*sin(alpha)     r.y*r.z*(1 - cos(alpha)) + r.x*sin(alpha)     r.z*r.z*(1 - cos(alpha)) + cos(alpha)     |
   * 
   ****************************************************************/
  void RobotAction::_getRotateBodyPoint(Point &p, Point r, float alpha) {
    //0.- Puntos actuales
    float x = p._x;
    float y = p._y;
    float z = p._z;

    //1.- Grados -> radianes
    alpha *= PI/180;

    //2.- Calculo de factores
    float COS = cos(alpha);
    float SIN = sin(alpha);
    float AUX = 1 - COS;

    //3.- Calcular nuevos puntos con la matriz T
    p._x = x * (r._x * r._x * AUX +        COS) + y * (r._x * r._y * AUX - r._z * SIN) + z * (r._x * r._z * AUX + r._y * SIN);
    p._y = x * (r._x * r._y * AUX + r._z * SIN) + y * (r._y * r._y * AUX +        COS) + z * (r._y * r._z * AUX - r._x * SIN);
    p._z = x * (r._x * r._z * AUX - r._y * SIN) + y * (r._y * r._z * AUX + r._x * SIN) + z * (r._z * r._z * AUX +        COS);
  }

  /****************************************************************
   * void _getRotateBodyPoints(RobotLegsPoints &points, Point rotateAxis, float rotateAngle)
   * 
   * 
   ****************************************************************/
  void RobotAction::_getRotateBodyPoints(RobotLegsPoints &points, Point rotateAxis, float rotateAngle) {
    float rotateAxisDist = rotateAxis.norma2();

    if (rotateAxisDist == 0)
    {
      rotateAxis._x = 0;
      rotateAxis._y = 0;
      rotateAxis._z = 1;
    }
    else
    {
      rotateAxis._x /= rotateAxisDist;
      rotateAxis._y /= rotateAxisDist;
      rotateAxis._z /= rotateAxisDist;
    }

    this -> _getRotateBodyPoint(points._leg1, rotateAxis, rotateAngle);
    this -> _getRotateBodyPoint(points._leg2, rotateAxis, rotateAngle);
    this -> _getRotateBodyPoint(points._leg3, rotateAxis, rotateAngle);
    this -> _getRotateBodyPoint(points._leg4, rotateAxis, rotateAngle);
    this -> _getRotateBodyPoint(points._leg5, rotateAxis, rotateAngle);
    this -> _getRotateBodyPoint(points._leg6, rotateAxis, rotateAngle);
  }

  /****************************************************************
   * void _getTurnPoint(Point &point, float alpha)
   * 
   * Calcula las nuevas coordenadas (X, Y) despues de girar alpha grados el vector.
   * 
   ****************************************************************/
  void RobotAction::_getTurnPoint(Point &point, float alpha) {
    //0.- De grados a radianes
    alpha = alpha * PI / 180;

    //1.- Radio de giro
    float radio = sqrt(point._x * point._x + point._y * point._y);

    //2.- Nuevas coordenadas
    float x = radio * cos(alpha + atan2(point._y, point._x));
    float y = radio * sin(alpha + atan2(point._y, point._x));

    //3.- Devolvemos el resultado
    point = Point(x, y, point._z);
  }
  
  /****************************************************************
   * void _getTurnPoints(RobotLegsPoints &points, float angulo)
   * 
   * Para cada pata:
   *      calcula las nuevas coordenadas (X, Y) despues de girar
   *      alpha grados el vector de la pata.
   * 
   ****************************************************************/
  void RobotAction::_getTurnPoints(RobotLegsPoints &points, float angulo) {
    this -> _getTurnPoint(points._leg1, angulo);
    this -> _getTurnPoint(points._leg2, angulo);
    this -> _getTurnPoint(points._leg3, angulo);
    this -> _getTurnPoint(points._leg4, angulo);
    this -> _getTurnPoint(points._leg5, angulo);
    this -> _getTurnPoint(points._leg6, angulo);
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
   * void _legsMoveTo(RobotLegsPoints points, int leg, float stepDistance)
   * 
   * Mueve las patas a la posicion absoulta POINTS.
   * 
   ****************************************************************/
  void RobotAction::_legsMoveTo(RobotLegsPoints points, int leg, float stepDistance) {
    if (_robot.checkPoints(points) == false) return;

    float d[6] = {
      Point::getDistance(_robot.getLeg1().getPosicionActual(), points._leg1),
      Point::getDistance(_robot.getLeg2().getPosicionActual(), points._leg2),
      Point::getDistance(_robot.getLeg3().getPosicionActual(), points._leg3),
      Point::getDistance(_robot.getLeg4().getPosicionActual(), points._leg4),
      Point::getDistance(_robot.getLeg5().getPosicionActual(), points._leg5),
      Point::getDistance(_robot.getLeg6().getPosicionActual(), points._leg6)};

    float s[6] = {
      d[0] / d[leg - 1] * stepDistance,
      d[1] / d[leg - 1] * stepDistance,
      d[2] / d[leg - 1] * stepDistance,
      d[3] / d[leg - 1] * stepDistance,
      d[4] / d[leg - 1] * stepDistance,
      d[5] / d[leg - 1] * stepDistance};

    _robot.setStepDistance(s[0], s[1], s[2], s[3], s[4], s[5]);
    _robot.moveTo         (points);
  
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

  /****************************************************************
   * void twistBody(Point move, Point rotateAxis, float rotateAngle)
   * 
   * move:        desplazamiento
   * rotateAxis:  eje de rotacion
   * rotateAngle: angulo de rotacion, entre -15 y 15.
   * 
   ****************************************************************/
  void RobotAction::_twistBody(Point move, Point rotateAxis, float rotateAngle) {
    //0.- ActionState
    this -> _actionState();

    //1.- Check LEGS STATE
    if (_legsState != LegsState::TWIST_BODY_STATE) this -> initialState();

    //2.- Establecer la altura por defecto
    RobotLegsPoints points = _lastChangeLegsStatePoints;

    points._leg1._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg2._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg3._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg4._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg5._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg6._z = RobotShape::DEFAULT_BODY_LIFT;

    //3.- Calcular desplazamiento
    move._x = constrain(move._x, -30, 30);
    move._y = constrain(move._y, -30, 30);
    move._z = constrain(move._z, -45,  0);
    this -> _getMoveBodyPoints(points, move);

    //4.- Calcular rotacion
    rotateAngle = constrain(rotateAngle, -_ANGULO_GIRO, _ANGULO_GIRO);
    this -> _getRotateBodyPoints(points, rotateAxis, rotateAngle);

    //5.- Mover robot
    this -> _legsMoveTo(points, _BODY_TWIST_STEP_DISTANCE);

    //6.- LEGS STATE
    _legsState = LegsState::TWIST_BODY_STATE;
  }
}
