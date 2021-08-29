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
   * void crawlForward()
   * void crawlBackward()
   * void crawlLeft()
   * void crawlRight()
   * void turnLeft()
   * void turnRight()
   * 
   ****************************************************************/
  void RobotController::crawlForward()  {this -> crawl(0,                  _DISTANCIA_CICLO,  0);}
  void RobotController::crawlBackward() {this -> crawl(0,                 -_DISTANCIA_CICLO,  0);}
  
  void RobotController::crawlLeft()     {this -> crawl(-_DISTANCIA_CICLO,  0,                 0);}
  void RobotController::crawlRight()    {this -> crawl( _DISTANCIA_CICLO,  0,                 0);}
  
  void RobotController::turnLeft()      {this -> crawl(0,                  0,                -_ANGULO_GIRO);}
  void RobotController::turnRight()     {this -> crawl(0,                  0,                 _ANGULO_GIRO);}

  /****************************************************************
   * void crawl(float x, float y, float angle)
   * 
   ****************************************************************/
  void RobotController::crawl(float x, float y, float angle) {
    //1.- ActionState
    this -> _setActionState();

    //2.- Comprobar ESTADO_PATAS y MODO
    if ((_estadoPatas != LegsState::CRAWL_STATE) || (_modo != RobotMode::ACTIVE)) this -> setActiveMode();

    //3.- Normalizar posicion y angulo
    float distancia = sqrt(x*x + y*y);
    if (distancia > _DISTANCIA_CICLO)
    {
      x *= (_DISTANCIA_CICLO / distancia);
      y *= (_DISTANCIA_CICLO / distancia);
    }

    angle = constrain(angle, -_ANGULO_GIRO, _ANGULO_GIRO);

    //4.- Dividir por el numero de pasos por ciclo
    x     /= _totalPasosCiclo;
    y     /= _totalPasosCiclo;
    angle /= _totalPasosCiclo;

    //5.- Calcular movimientos
    RobotLegsPoints p1;
    _robot.getPointsNow(p1);

    RobotLegsPoints p2 = p1;
    this -> _addDelta(p2, Point(-x/2, -y/2, 0));
    this -> _addGiro (p2, -angle/2);

    RobotLegsPoints p3 = p1;
    this -> _addDelta(p3, Point(-x, -y, 0));
    this -> _addGiro (p3, -angle);

    RobotLegsPoints p4 = BOOT_POINTS;
    this -> _addDelta(p4, Point(x * (_totalPasosCiclo - 1) / 4, y * (_totalPasosCiclo - 1) / 4, _altura + _ALTURA_SUSPENSION));
    this -> _addGiro (p4,   angle * (_totalPasosCiclo - 1) / 4);

    RobotLegsPoints p5 = BOOT_POINTS;
    this -> _addDelta(p5, Point(x * (_totalPasosCiclo - 1) / 2, y * (_totalPasosCiclo - 1) / 2, _altura));
    this -> _addGiro (p5,   angle * (_totalPasosCiclo - 1) / 2);

    (_pasoCiclo < _totalPasosCiclo) ? _pasoCiclo++ : _pasoCiclo = 1;

    switch (_totalPasosCiclo)
    {
      case 2:
          switch (_pasoCiclo)
          {
            case 1:
                p2._leg1 = p4._leg1;  //Pata 1 suspendida
                p2._leg3 = p4._leg3;  //Pata 3 suspendida
                p2._leg5 = p4._leg5;  //Pata 5 suspendida
                
                p3._leg1 = p5._leg1;  //Para 1 adelantada
                p3._leg3 = p5._leg3;  //Para 3 adelantada
                p3._leg5 = p5._leg5;  //Para 5 adelantada
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg1._z = p1._leg1._z;
                    p3._leg3._z = p1._leg3._z;
                    p3._leg5._z = p1._leg5._z;
                  }
                  
                  this -> _move(p2, 1, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 1, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 2:
                p2._leg2 = p4._leg2;  //Pata 2 suspendida
                p2._leg4 = p4._leg4;  //Pata 4 suspendida
                p2._leg6 = p4._leg6;  //Pata 6 suspendida
                
                p3._leg2 = p5._leg2;  //Para 2 adelantada
                p3._leg4 = p5._leg4;  //Para 4 adelantada
                p3._leg6 = p5._leg6;  //Para 6 adelantada
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg2._z = p1._leg2._z;
                    p3._leg4._z = p1._leg4._z;
                    p3._leg6._z = p1._leg6._z;
                  }
                  
                  this -> _move(p2, 2, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 2, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
          }
          break;

      case 4:
          switch (_pasoCiclo)
          {
            case 1:
                p2._leg1 = p4._leg1; //Pata 1 suspendida
                p2._leg6 = p4._leg6; //Pata 6 suspendida
                
                p3._leg1 = p5._leg1;
                p3._leg6 = p5._leg6;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg1._z = p1._leg1._z;
                    p3._leg6._z = p1._leg6._z;
                  }
                  this -> _move(p2, 1, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 1, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 2:
                p2._leg5 = p4._leg5; //Pata 5 suspendida
                
                p3._leg5 = p5._leg5;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg5._z = p1._leg5._z;
                  }
                  this -> _move(p2, 5, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 5, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
    
            case 3:
                p2._leg3 = p4._leg3; //Pata 3 suspendida
                p2._leg4 = p4._leg4; //Pata 4 suspendida
                
                p3._leg3 = p5._leg3;
                p3._leg4 = p5._leg4;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg3._z = p1._leg3._z;
                    p3._leg4._z = p1._leg4._z;
                  }
                  this -> _move(p2, 3, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 3, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 4:
                p2._leg2 = p4._leg2; //Pata 2 suspendida
                
                p3._leg2 = p5._leg2;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg2._z = p1._leg2._z;
                  }
                  this -> _move(p2, 2, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 2, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
          }
          break;
          
      case 6:
          switch (_pasoCiclo)
          {
            case 1:
                p2._leg1 = p4._leg1;  //Pata 1 suspendida
                
                p3._leg1 = p5._leg1;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg1._z = p1._leg1._z;
                  }
                  this -> _move(p2, 1, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 1, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
    
            case 2:
                p2._leg5 = p4._leg5; //Pata 5 suspendida
                
                p3._leg5 = p5._leg5;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg5._z = p1._leg5._z;
                  }
                  this -> _move(p2, 5, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 5, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 3:
                p2._leg3 = p4._leg3; //Pata 3 suspendida
                
                p3._leg3 = p5._leg3;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg3._z = p1._leg3._z;
                  }
                  this -> _move(p2, 3, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 3, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 4:
                p2._leg4 = p4._leg4; //Pata 4 suspendida
                
                p3._leg4 = p5._leg4;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg4._z = p1._leg4._z;
                  }
                  this -> _move(p2, 4, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 4, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 5:
                p2._leg2 = p4._leg2; //Pata 2 suspendida
                
                p3._leg2 = p5._leg2;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg2._z = p1._leg2._z;
                  }
                  this -> _move(p2, 2, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 2, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
                
            case 6:
                p2._leg6 = p4._leg6; //Pata 6 suspendida
                
                p3._leg6 = p5._leg6;
                
                if (this -> _checkPoints(p2) == true)
                {
                  if (this -> _checkPoints(p3) == false)
                  {
                    p3 = p2;
                    
                    p3._leg6._z = p1._leg6._z;
                  }
                  this -> _move(p2, 6, _LEG_LIFT_STEP_DISTANCE);
                  this -> _move(p3, 6, _LEG_LIFT_STEP_DISTANCE);
                }
                break;
          }
          break;
    }

    _estadoPatas = LegsState::CRAWL_STATE;
  }
  

  /****************************************************************
   * void setPasosCiclo(int x)
   * 
   ****************************************************************/
  void RobotController::setPasosCiclo(int x) {
    switch (x)
    {
      case 2:  _totalPasosCiclo = 4; return;
      case 3:  _totalPasosCiclo = 6; return;
      default: _totalPasosCiclo = 2; return;
    }
  }


  /****************************************************************
   * void setSpeed(float x)
   * 
   ****************************************************************/
  void RobotController::setSpeed(float x) {
    _robot.setSpeed(x);
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
   * void _addGiro(RobotLegsPoints &points, float angle)
   * 
   * Para cada pata:
   *      calcula las nuevas coordenadas (X, Y) despues de girar
   *      alpha grados el vector de la pata.
   * 
   ****************************************************************/
  void RobotController::_addGiro(RobotLegsPoints &points, float angle) {
    this -> _addGiro(points._leg1, angle);
    this -> _addGiro(points._leg2, angle);
    this -> _addGiro(points._leg3, angle);
    this -> _addGiro(points._leg4, angle);
    this -> _addGiro(points._leg5, angle);
    this -> _addGiro(points._leg6, angle);
  }

  /****************************************************************
   * void _addGiro(Point &point, float angle)
   * 
   * Calcula las nuevas coordenadas (X, Y) despues de girar alpha grados el vector.
   * 
   ****************************************************************/
  void RobotController::_addGiro(Point &point, float angle) {
    //0.- De grados a radianes
    angle *= PI / 180;

    //1.- Radio de giro
    float radio = sqrt(point._x * point._x + point._y * point._y);

    //2.- Nuevas coordenadas
    float x = radio * cos(angle + atan2(point._y, point._x));
    float y = radio * sin(angle + atan2(point._y, point._x));

    //3.- Devolvemos el resultado
    point = Point(x, y, point._z);
  }

  /****************************************************************
   * bool _checkPoints(RobotLegsPoints points)
   * 
   * Establece:
   *         RobotState:                ACTION
   *         LegsState:                 CRAWL_STATE
   *         lastChangeLegsStatePoints: BOOT_POINTS
   * 
   ****************************************************************/
  bool RobotController::_checkPoints(RobotLegsPoints points) {
    float alpha1;
    float alpha2;
    float alpha3;
    float alpha4;
    float alpha5;
    float alpha6;
    float beta;
    float gamma;

    _robot.getLeg1().getAngles(points._leg1, alpha1, beta, gamma);
    _robot.getLeg2().getAngles(points._leg2, alpha2, beta, gamma);
    _robot.getLeg3().getAngles(points._leg3, alpha3, beta, gamma);
    _robot.getLeg4().getAngles(points._leg4, alpha4, beta, gamma);
    _robot.getLeg5().getAngles(points._leg5, alpha5, beta, gamma);
    _robot.getLeg6().getAngles(points._leg6, alpha6, beta, gamma);

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
   * void _move(RobotLegsPoints points, int leg, float stepDistance)
   * 
   * Mueve las patas a la posicion absoulta POINTS.
   * 
   ****************************************************************/
  void RobotController::_move(RobotLegsPoints points, int leg, float stepDistance) {
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
    _robot.move           (points);
  
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

}
