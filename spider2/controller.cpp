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
  
  void RobotController::turnLeft()      {this -> crawl(0,                  0,                 _ANGULO_GIRO);}
  void RobotController::turnRight()     {this -> crawl(0,                  0,                -_ANGULO_GIRO);}

  /****************************************************************
   * void crawl(float x, float y, float angle)
   * 
   * Desplazamiento: (x,y)
   * Rotacion: angulo theta
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

    //4.- Calcular movimientos
    switch (_crawlMode)
    {
      case RobotCrawlMode::TRIPOD: _crawlTripod(x, y, angle); break;
      case RobotCrawlMode::RIPPLE: _crawlRipple(x, y, angle); break;
      case RobotCrawlMode::WAVE:   _crawlWave  (x, y, angle); break;
    }

    _estadoPatas = LegsState::CRAWL_STATE;
  }


  /****************************************************************
   * void moveLeg(int leg, Point p)
   * 
   ****************************************************************/
  void RobotController::moveLeg(int leg, Point p) {
    //1.- ActionState
    this -> _setActionState();

    //2.- Comprobar LEGS STATE
    if (_estadoPatas == LegsState::LEG_MOVE_STATE) this -> setCrawlLegState();

    //3.- Mover pata
    this -> moveLegDirectly(leg, p);
    _robot.waitUntilFree();

    //4.- Actualizar estado
    _estadoPatas = LegsState::LEG_MOVE_STATE;
  }

  /****************************************************************
   * void moveLegDirectly(int leg, Point p)
   * 
   ****************************************************************/
  void RobotController::moveLegDirectly(int leg, Point p) {
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
    _robot.move(points, _LEG_LIFT_STEP_DISTANCE);
  }

  /****************************************************************
   * void moveBody(float x, float y, float z)
   * 
   ****************************************************************/
  void RobotController::moveBody(float x, float y, float z) {
    this -> twistBody(Point(x, y, z), Point(0, 0, 0));
  }

  /****************************************************************
   * void rotateBody(float x, float y, float z)
   * 
   ****************************************************************/
  void RobotController::rotateBody(float x, float y, float z) {
    this -> twistBody(Point(0, 0, 0), Point(x, y, z));
  }
  

  /****************************************************************
   * void setPasosCiclo(int x)
   * 
   ****************************************************************/
  void RobotController::setPasosCiclo(int x) {
    switch (x)
    {
      case 2:  _crawlMode = RobotCrawlMode::RIPPLE; return;
      case 3:  _crawlMode = RobotCrawlMode::WAVE;   return;
      default: _crawlMode = RobotCrawlMode::TRIPOD; return;
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
   * void twistBody(Point move, Point rotate)
   * 
   * move:   desplazamiento
   * rotate: direccion del eje de rotacion; su magnitud es el angulo de rotacion
   * 
   ****************************************************************/
  void RobotController::twistBody(Point move, Point rotate) {
    //1.- El angulo de rotacion es la magnitud del vector de rotacion
    float angulo = rotate.norma2();

    //2.- Mover robot
    this -> _twistBody(move, rotate, angulo);
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

    _robot.getPointsNow(_posicionUltima);

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
   * Matriz de rotacion: R(z,angle)
   * 
   * | x'| = | cos(angle)    -sin(angle)   0|   |x|
   * | y'| = | sin(angle)     cos(angle)   0| * |y|
   * | z'| = |     0             0         1|   |z|
   * 
   ****************************************************************/
  void RobotController::_addGiro(RobotLegsPoints &points, float angle) {
    //0.- De grados a radianes
    angle *= PI / 180;

    //1.- Calcular seno y coseno
    float COS = cos(angle);
    float SIN = sin(angle);

    //2.- Rotar las patas
    this -> _addGiro(points._leg1, SIN, COS);
    this -> _addGiro(points._leg2, SIN, COS);
    this -> _addGiro(points._leg3, SIN, COS);
    this -> _addGiro(points._leg4, SIN, COS);
    this -> _addGiro(points._leg5, SIN, COS);
    this -> _addGiro(points._leg6, SIN, COS);
  }

  /****************************************************************
   * void _addGiro(Point &point, float SIN, float COS)
   * 
   * Calcula las nuevas coordenadas (X, Y) despues de girar alpha grados el vector.
   * 
   * x' = x*C - y*S
   * y' = x*S + y*C
   * 
   ****************************************************************/
  void RobotController::_addGiro(Point &point, float SIN, float COS) {
    //1.- Nuevas coordenadas
    float x = point._x * COS - point._y * SIN;
    float y = point._x * SIN + point._y * COS;

    //2.- Devolvemos el resultado
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
   * void _crawlRipple(float x, float y, float angle)
   * 
   * 
   *                 P1
   *                / \
   *              /     \
   *            /         \
   *          /             \
   *        /                 \
   *      /                     \
   *     *-----*-----*-----*-----*
   *    P6    P5     P4    P3    P2
   * 
   ****************************************************************/
  void RobotController::_crawlRipple(float x, float y, float angle) {
    x     /= 2;
    y     /= 2;
    angle /= 2;
    
     RobotLegsPoints p0;
    _robot.getPointsNow(p0);

    RobotLegsPoints p1 = BOOT_POINTS;
    this -> _addDelta(p1, Point(0, 0, _altura + _ALTURA_SUSPENSION));

    RobotLegsPoints p2 = BOOT_POINTS;
    this -> _addDelta(p2, Point(x/2, y/2, _altura));
    this -> _addGiro (p2, angle/2);

    RobotLegsPoints p3 = p0;
    this -> _addDelta(p3, Point(-x/4, -y/4, 0));
    this -> _addGiro (p3, -angle/4);

    _addPasoCiclo();

    switch (_pasoCiclo)
    {
      case 1:
          p3._leg1 = p1._leg1; //Pata 1 suspendida
          p3._leg6 = p2._leg6;
          
          if (this -> _checkPoints(p3) == true) this -> _move(p3, 1, _LEG_LIFT_STEP_DISTANCE);
          break;

      case 2:
          p3._leg1 = p2._leg1;
          p3._leg5 = p1._leg5; //Pata 5 suspendida
          
          if (this -> _checkPoints(p3) == true) this -> _move(p3, 5, _LEG_LIFT_STEP_DISTANCE);
          break;

      case 3:
          p3._leg3 = p1._leg3; //Pata 3 suspendida
          p3._leg5 = p2._leg5;
          
          if (this -> _checkPoints(p3) == true) this -> _move(p3, 3, _LEG_LIFT_STEP_DISTANCE);
          break;

      case 4:
          p3._leg3 = p2._leg3;
          p3._leg4 = p1._leg4; //Pata 4 suspendida
          
          if (this -> _checkPoints(p3) == true) this -> _move(p3, 4, _LEG_LIFT_STEP_DISTANCE);
          break;

      case 5:
          p3._leg2 = p1._leg2; //Pata 2 suspendida
          p3._leg4 = p2._leg4;
          
          if (this -> _checkPoints(p3) == true) this -> _move(p3, 2, _LEG_LIFT_STEP_DISTANCE);
          break;

      case 6:
          p3._leg2 = p2._leg2;
          p3._leg6 = p1._leg6; //Pata 6 suspendida
          
          if (this -> _checkPoints(p3) == true) this -> _move(p3, 6, _LEG_LIFT_STEP_DISTANCE);
          break;
    }

    return;
  }

  /****************************************************************
   * void _crawlTripod(float x, float y, float angle)
   * 
   * Se mueven 2 grupos de 3 patas.
   * 
   *             P4
   *            /  \
   *          /      \
   *        /          \
   *      /              \
   *     *--------*-------*
   *    P3       P2       P5
   *    
   ****************************************************************/
  void RobotController::_crawlTripod(float x, float y, float angle) {
    x     /= 2;
    y     /= 2;
    angle /= 2;
    
    RobotLegsPoints p1;
    _robot.getPointsNow(p1);

    RobotLegsPoints p2 = p1;
    this -> _addDelta(p2, Point(-x/2, -y/2, 0));
    this -> _addGiro (p2, -angle/2);

    RobotLegsPoints p3 = p1;
    this -> _addDelta(p3, Point(-x, -y, 0));
    this -> _addGiro (p3, -angle);

    RobotLegsPoints p4 = BOOT_POINTS;
    this -> _addDelta(p4, Point(0, 0, _altura + _ALTURA_SUSPENSION));

    RobotLegsPoints p5 = BOOT_POINTS;
    this -> _addDelta(p5, Point(x/2, y/ 2, _altura));
    this -> _addGiro (p5, angle/2);

    _addPasoCiclo();

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

    return;
  }

  /****************************************************************
   * void _crawlWave(float x, float y, float angle)
   * 
   ****************************************************************/
  void RobotController::_crawlWave(float x, float y, float angle) {
    x     /= 2;
    y     /= 2;
    angle /= 2;
    
    RobotLegsPoints p0;
    _robot.getPointsNow(p0);

    RobotLegsPoints p1 = BOOT_POINTS;
    this -> _addDelta(p1, Point(0, 0, _altura + _ALTURA_SUSPENSION));

    RobotLegsPoints p2 = BOOT_POINTS;
    this -> _addDelta(p2, Point(x/2, y/ 2, _altura));
    this -> _addGiro (p2, angle/2);

    RobotLegsPoints p3 = p0;
    this -> _addDelta(p3, Point(-x/10, -y/10, 0));
    this -> _addGiro (p3, -angle/10);

    RobotLegsPoints p4 = p0;
    this -> _addDelta(p4, Point(-x/5, -y/5, 0));
    this -> _addGiro (p4, -angle/5);

    

    _addPasoCiclo();

    switch (_pasoCiclo)
    {
      case 1:
          p3._leg6 = p1._leg6;  //Pata 6 suspendida
          p4._leg6 = p2._leg6;  //Para 6 adelantada
          
          if (this -> _checkPoints(p3) == true)
          {
            if (this -> _checkPoints(p4) == false)
            {
              p4 = p3;
              
              p4._leg6._z = p3._leg6._z;
            }
            this -> _move(p3, 6, _LEG_LIFT_STEP_DISTANCE);
            this -> _move(p4, 6, _LEG_LIFT_STEP_DISTANCE);
          }
          break;
          
      case 2:
          p3._leg5 = p1._leg5;  //Pata 5 suspendida
          p4._leg5 = p2._leg5;  //Para 5 adelantada
          
          if (this -> _checkPoints(p3) == true)
          {
            if (this -> _checkPoints(p4) == false)
            {
              p4 = p3;
              
              p4._leg5._z = p3._leg5._z;
            }
            this -> _move(p3, 5, _LEG_LIFT_STEP_DISTANCE);
            this -> _move(p4, 5, _LEG_LIFT_STEP_DISTANCE);
          }
          break;

      case 3:
          p3._leg4 = p1._leg4;  //Pata 4 suspendida
          p4._leg4 = p2._leg4;  //Para 4 adelantada
          
          if (this -> _checkPoints(p3) == true)
          {
            if (this -> _checkPoints(p4) == false)
            {
              p4 = p3;
              
              p4._leg4._z = p3._leg4._z;
            }
            this -> _move(p3, 4, _LEG_LIFT_STEP_DISTANCE);
            this -> _move(p4, 4, _LEG_LIFT_STEP_DISTANCE);
          }
          break;
          
      case 4:
          p3._leg3 = p1._leg3;  //Pata 3 suspendida
          p4._leg3 = p2._leg3;  //Para 3 adelantada
          
          if (this -> _checkPoints(p3) == true)
          {
            if (this -> _checkPoints(p4) == false)
            {
              p4 = p3;
              
              p4._leg3._z = p3._leg3._z;
            }
            this -> _move(p3, 3, _LEG_LIFT_STEP_DISTANCE);
            this -> _move(p4, 3, _LEG_LIFT_STEP_DISTANCE);
          }
          break;

      case 5:
          p3._leg2 = p1._leg2;  //Pata 2 suspendida
          p4._leg2 = p2._leg2;  //Para 2 adelantada
          
          if (this -> _checkPoints(p3) == true)
          {
            if (this -> _checkPoints(p4) == false)
            {
              p4 = p3;
              
              p4._leg2._z = p3._leg2._z;
            }
            this -> _move(p3, 2, _LEG_LIFT_STEP_DISTANCE);
            this -> _move(p4, 2, _LEG_LIFT_STEP_DISTANCE);
          }
          break;
          
      case 6:
          p3._leg1 = p1._leg1;  //Pata 1 suspendida
          p4._leg1 = p2._leg1;  //Para 1 adelantada
          
          if (this -> _checkPoints(p3) == true)
          {
            if (this -> _checkPoints(p4) == false)
            {
              p4 = p3;
              
              p4._leg1._z = p3._leg1._z;
            }
            this -> _move(p3, 1, _LEG_LIFT_STEP_DISTANCE);
            this -> _move(p4, 1, _LEG_LIFT_STEP_DISTANCE);
          }
          break;
    }

    return;
  }

  /****************************************************************
   * void _getRotatePoint(Point &p, Point r, float alpha)
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
  void RobotController::_getRotatePoint(Point &p, Point r, float alpha) {
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
   * void _getRotatePoints(RobotLegsPoints &points, Point rotateAxis, float rotateAngle)
   * 
   * 
   ****************************************************************/
  void RobotController::_getRotatePoints(RobotLegsPoints &points, Point rotateAxis, float rotateAngle) {
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

    this -> _getRotatePoint(points._leg1, rotateAxis, rotateAngle);
    this -> _getRotatePoint(points._leg2, rotateAxis, rotateAngle);
    this -> _getRotatePoint(points._leg3, rotateAxis, rotateAngle);
    this -> _getRotatePoint(points._leg4, rotateAxis, rotateAngle);
    this -> _getRotatePoint(points._leg5, rotateAxis, rotateAngle);
    this -> _getRotatePoint(points._leg6, rotateAxis, rotateAngle);
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
    _posicionUltima = _posicionInicial;
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
   * void twistBody(Point move, Point rotateAxis, float rotateAngle)
   * 
   * delta:       desplazamiento
   * rotateAxis:  eje de rotacion
   * rotateAngle: angulo de rotacion, entre -15 y 15.
   * 
   ****************************************************************/
  void RobotController::_twistBody(Point delta, Point rotateAxis, float rotateAngle) {
    //0.- ActionState
    this -> _setActionState();

    //1.- Check LEGS STATE
    if (_estadoPatas != LegsState::TWIST_BODY_STATE) this -> setCrawlLegState();

    //2.- Establecer la altura por defecto
    RobotLegsPoints points = _posicionUltima;

    points._leg1._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg2._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg3._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg4._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg5._z = RobotShape::DEFAULT_BODY_LIFT;
    points._leg6._z = RobotShape::DEFAULT_BODY_LIFT;

    //3.- Calcular desplazamiento
    delta._x = constrain(delta._x, -30, 30);
    delta._y = constrain(delta._y, -30, 30);
    delta._z = constrain(delta._z, -45,  0);

    //4.- Se resta el desplazamiento
    this -> _addDelta(points, delta);

    //4.- Calcular rotacion
    rotateAngle = constrain(rotateAngle, -_ANGULO_GIRO, _ANGULO_GIRO);
    this -> _getRotatePoints(points, rotateAxis, rotateAngle);

    //5.- Mover robot
    this -> _move(points, _BODY_TWIST_STEP_DISTANCE);

    //6.- LEGS STATE
    _estadoPatas = LegsState::TWIST_BODY_STATE;
  }

}
