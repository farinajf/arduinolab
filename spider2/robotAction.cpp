#include "robotAction.h"

namespace SPIDER {

  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  RobotAction::RobotAction() : _robot() {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void RobotAction::init() {
    //1.- Robot
    _robot.init();

    //2-. Initial points
    _initialPoints = _robot.getBootPoints();
  }

  /****************************************************************
   * void activeMode()
   * 
   * Establece:
   *       - _legsState CRAWL_STATE
   *       - _mode      ACTIVE
   ****************************************************************/
  void RobotAction::activeMode() {
    this -> _actionState();

    if (_legsState != LegsState::CRAWL_STATE) this -> initialState();
    if (_mode      == RobotMode::ACTIVE)      return;

    _legsMoveToRelatively(Point(0, 0, _bodyLift), ROBOT_ACTION_BODY_LIFT_SPEED);

    _legsState = LegsState::CRAWL_STATE;
    _mode      = RobotMode::ACTIVE;
  }

  /****************************************************************
   * void changeBodyHeight(float h)
   * 
   ****************************************************************/
  void RobotAction::changeBodyHeight(float h) {
    RobotLegsPoints points;

    this -> _actionState();
    if (_legsState != LegsState::CRAWL_STATE) this -> initialState();
    if (_mode      != RobotMode::ACTIVE)      this -> activeMode();
    
    _bodyLift = constrain(h, -40, -100);

    _robot.getPointsNow(points);

    points._leg1._z = _bodyLift;
    points._leg2._z = _bodyLift;
    points._leg3._z = _bodyLift;
    points._leg4._z = _bodyLift;
    points._leg5._z = _bodyLift;
    points._leg6._z = _bodyLift;

    this-> _legsMoveTo(points, ROBOT_ACTION_BODY_LIFT_SPEED);
  }

  /****************************************************************
   * void crawl(float x, float y, float angle)
   * void crawlForward()
   * void crawlBackward()
   * 
   * void crawlRight()
   * void crawlLeft()
   * 
   * void turnRight()
   * void turnLeft()
   * 
   ****************************************************************/
  void RobotAction::crawl(float x, float y, float angle) {
    RobotLegsPoints points1;
    RobotLegsPoints points2;
    RobotLegsPoints points3;
    RobotLegsPoints points4;
    RobotLegsPoints points5;

    //0.- Estado inicial
    this -> _actionState();
    if (_legsState != LegsState::CRAWL_STATE) this -> initialState();
    if (_mode      != RobotMode::ACTIVE)      this -> activeMode();

    //1.- Calculo de distancia
    float d = sqrt(x*x + y*y);
    
    if (d > ROBOT_ACTION_CRAWL_LENGTH)
    {
      x = x * ROBOT_ACTION_CRAWL_LENGTH / d;
      y = y * ROBOT_ACTION_CRAWL_LENGTH / d;
    }

    //2.- Angulo de giro
    angle = constrain(angle, -ROBOT_ACTION_TURN_ANGLE, ROBOT_ACTION_TURN_ANGLE);

    //3.- Distancia por paso
    x     /= ROBOT_ACTION_CRAWL_STEPS;
    y     /= ROBOT_ACTION_CRAWL_STEPS;
    angle /= ROBOT_ACTION_CRAWL_STEPS;

    //4.- Points 1
    _robot.getPointsNow(points1);

    //5.- Points 2
    points2 = points1;
    this -> _getCrawlPoints(points2, Point(-x/2, -y/2, 0));
    this -> _getTurnPoints (points2, -angle/2);
    
    //6.- Points 3
    points3 = points1;
    this -> _getCrawlPoints(points3, Point(-x, -y, 0));
    this -> _getTurnPoints (points3, -angle);
    
    //7.- Points 4
    points4 = _robot.getBootPoints();
    this -> _getCrawlPoints(points4, Point(x * (ROBOT_ACTION_CRAWL_STEPS - 1) / 4, y * (ROBOT_ACTION_CRAWL_STEPS - 1) / 4, _bodyLift + ROBOT_ACTION_LEG_LIFT));
    this -> _getTurnPoints (points4, angle * (ROBOT_ACTION_CRAWL_STEPS - 1) / 4);
    
    //8.- Points 5
    points5 = _robot.getBootPoints();
    this -> _getCrawlPoints(points5, Point(x * (ROBOT_ACTION_CRAWL_STEPS - 1) / 2, y * (ROBOT_ACTION_CRAWL_STEPS - 1) / 2, _bodyLift + ROBOT_ACTION_LEG_LIFT));
    this -> _getTurnPoints (points5, angle * (ROBOT_ACTION_CRAWL_STEPS - 1) / 2);

    _legMoveIndex = (_legMoveIndex < ROBOT_ACTION_CRAWL_STEPS) ? _legMoveIndex + 1 : 1;

    switch (ROBOT_ACTION_CRAWL_STEPS)
    {
      case 2:
          {
            //TODO
          }
          break;

      case 4:
          {
            //TODO
          }
          break;
          
      case 6: this -> _crawl6Steps(points1, points2, points3, points4, points5); break;
    }
    
    _legsState = LegsState::CRAWL_STATE;
  }
  
  void RobotAction::crawlForward()  {this -> crawl(0,    ROBOT_ACTION_CRAWL_LENGTH, 0);}
  void RobotAction::crawlBackward() {this -> crawl(0, -1*ROBOT_ACTION_CRAWL_LENGTH, 0);}

  void RobotAction::crawlRight() {this -> crawl(   ROBOT_ACTION_CRAWL_LENGTH, 0, 0);}
  void RobotAction::crawlLeft()  {this -> crawl(-1*ROBOT_ACTION_CRAWL_LENGTH, 0, 0);}

  void RobotAction::turnRight() {this -> crawl(0, 0,    ROBOT_ACTION_TURN_ANGLE);}
  void RobotAction::turnLeft()  {this -> crawl(0, 0, -1*ROBOT_ACTION_TURN_ANGLE);}

  /****************************************************************
   * void initialState()
   * 
   * Establece:
   *      - _robot.state ACTION
   *      - _legsState   CRAWL_STATE
   * 
   ****************************************************************/
  void RobotAction::initialState() {
    this -> _actionState();

    if      (_legsState == LegsState::CRAWL_STATE)      this -> activeMode();
    //else if (_legsState == LegsState::TWIST_BODY_STATE) this -> _twistBody(Point(0, 0, _bodyLift - _DEFAULT_BODY_LIFT), Point(0, 0, 0), 0);
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

      this -> _legsMoveTo(points, ROBOT_ACTION_BODY_LIFT_SPEED);
    }

    _robot.getPointsNow(_lastChangeLegsStatePoints);

    _mode      = RobotMode::ACTIVE;
    _legsState = LegsState::CRAWL_STATE;
  }

  /****************************************************************
   * void sleepMode()
   * 
   * Establece:
   *       - _legsState CRAWL_STATE
   *       - _mode      SLEEP
   ****************************************************************/
  void RobotAction::sleepMode() {
    this -> _actionState();

    if (_legsState != LegsState::CRAWL_STATE) this -> initialState();
    if (_mode      == RobotMode::SLEEP)       return;

    _legsMoveToRelatively(Point(0, 0, _bodyLift), ROBOT_ACTION_BODY_LIFT_SPEED);

    _legsState = LegsState::CRAWL_STATE;
    _mode      = RobotMode::SLEEP;
  }

  /****************************************************************
   * void switchMode()
   * 
   * Establece:
   *       - _legsState CRAWL_STATE
   *       - _mode      SLEEP
   ****************************************************************/
  void RobotAction::switchMode() {
    this -> _actionState();

    if (_mode == RobotMode::ACTIVE) this -> sleepMode();
    else                            this -> activeMode();
  }

  /****************************************************************
   * void update()
   ****************************************************************/
  void RobotAction::update() {
    _robot.update();
  }







  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * void _actionState()
   * 
   * Establece:
   *      - _robot.state ACTION
   *      - _mode        SLEEP
   *      - _legsState   CRAWL_STATE
   * 
   ****************************************************************/
  void RobotAction::_actionState() {
    if (_robot.getState() == RobotState::ACTION) return;

    _robot.bootState();
    _robot.setState(RobotState::ACTION);
    

    _mode                      = RobotMode::SLEEP;
    _legsState                 = LegsState::CRAWL_STATE;
    _lastChangeLegsStatePoints = _initialPoints;
  }

  /****************************************************************
   * void _checkCrawlPoints(RobotLegsPoints points)
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
    _robot.getLeg2().calculateAngle(points._leg2, alpha1, beta, gamma);
    _robot.getLeg3().calculateAngle(points._leg3, alpha1, beta, gamma);
    _robot.getLeg4().calculateAngle(points._leg4, alpha1, beta, gamma);
    _robot.getLeg5().calculateAngle(points._leg5, alpha1, beta, gamma);
    _robot.getLeg6().calculateAngle(points._leg6, alpha1, beta, gamma);

    if (alpha1 < 0) alpha1 += 360;
    if (alpha2 < 0) alpha2 += 360;
    if (alpha3 < 0) alpha3 += 360;
    if (alpha4 < -180) alpha4 += 360; else if (alpha4 > 180) alpha4 -= 360;
    if (alpha5 < -180) alpha4 += 360; else if (alpha5 > 180) alpha4 -= 360;
    if (alpha6 < -180) alpha4 += 360; else if (alpha6 > 180) alpha4 -= 360;

    if (alpha1 < 90  || alpha1 > 180 ||
        alpha3 < 180 || alpha3 > 270 ||
        alpha4 < 0   || alpha4 > 90 ||
        alpha6 < -90 || alpha6 > 0 ||
        alpha2 - alpha1 < 0 ||
        alpha3 - alpha2 < 0 ||
        alpha4 - alpha5 < 0 ||
        alpha5 - alpha6 < 0)
      return false;

    return true;
  }

  /****************************************************************
   * void _crawl6Steps(RobotLegsPoints &points1, RobotLegsPoints &points2, RobotLegsPoints &points3, RobotLegsPoints &points4, RobotLegsPoints &points5)
   * 
   ****************************************************************/
  void RobotAction::_crawl6Steps(RobotLegsPoints &points1, RobotLegsPoints &points2, RobotLegsPoints &points3, RobotLegsPoints &points4, RobotLegsPoints &points5) {
    Serial.print("RobotAction::_crawl6Steps()   -> _legMoveIndex: "); Serial.println(_legMoveIndex);
    
    switch(_legMoveIndex)
    {
      case 1:
          points2._leg1 = points4._leg1;
          points3._leg1 = points5._leg1;

          if (this -> _checkCrawlPoints(points2) == true)
          {
            if (this -> _checkCrawlPoints(points3) == false)
            {
              points3          = points2;
              points3._leg1._z = points1._leg1._z;
            }

            this -> _legsMoveTo(points2, 1, ROBOT_ACTION_LEG_LIFT_SPEED);
            this -> _legsMoveTo(points3, 1, ROBOT_ACTION_LEG_LIFT_SPEED);
          }
          break;
          
      case 2:
          points2._leg5 = points4._leg5;
          points3._leg5 = points4._leg5;
          if (this -> _checkCrawlPoints(points2) == true)
          {
            if (this -> _checkCrawlPoints(points3) == false)
            {
              points3          = points2;
              points3._leg5._z = points1._leg5._z;
            }
            this -> _legsMoveTo(points2, 5, ROBOT_ACTION_LEG_LIFT_SPEED);
            this -> _legsMoveTo(points3, 5, ROBOT_ACTION_LEG_LIFT_SPEED);
          }
          break;
          
      case 3:
          points2._leg3 = points4._leg3;
          points3._leg3 = points4._leg3;
          if (this -> _checkCrawlPoints(points2) == true)
          {
            if (this -> _checkCrawlPoints(points3) == false)
            {
              points3          = points2;
              points3._leg3._z = points1._leg3._z;
            }
            this -> _legsMoveTo(points2, 3, ROBOT_ACTION_LEG_LIFT_SPEED);
            this -> _legsMoveTo(points3, 3, ROBOT_ACTION_LEG_LIFT_SPEED);
          }
          break;
          
      case 4:
          points2._leg4 = points4._leg4;
          points3._leg4 = points4._leg4;
          if (this -> _checkCrawlPoints(points2) == true)
          {
            if (this -> _checkCrawlPoints(points3) == false)
            {
              points3          = points2;
              points3._leg4._z = points1._leg4._z;
            }
            this -> _legsMoveTo(points2, 4, ROBOT_ACTION_LEG_LIFT_SPEED);
            this -> _legsMoveTo(points3, 4, ROBOT_ACTION_LEG_LIFT_SPEED);
          }
          break;
          
      case 5:
          points2._leg2 = points4._leg2;
          points3._leg2 = points4._leg2;
          if (this -> _checkCrawlPoints(points2) == true)
          {
            if (this -> _checkCrawlPoints(points3) == false)
            {
              points3          = points2;
              points3._leg2._z = points1._leg2._z;
            }
            this -> _legsMoveTo(points2, 2, ROBOT_ACTION_LEG_LIFT_SPEED);
            this -> _legsMoveTo(points3, 2, ROBOT_ACTION_LEG_LIFT_SPEED);
          }
          break;
          
      case 6:
          points2._leg6 = points4._leg6;
          points3._leg6 = points4._leg6;
          if (this -> _checkCrawlPoints(points2) == true)
          {
            if (this -> _checkCrawlPoints(points3) == false)
            {
              points3          = points2;
              points3._leg6._z = points1._leg6._z;
            }
            this -> _legsMoveTo(points2, 6, ROBOT_ACTION_LEG_LIFT_SPEED);
            this -> _legsMoveTo(points3, 6, ROBOT_ACTION_LEG_LIFT_SPEED);
          }
          break;
    }
  }

  /****************************************************************
   * void _getCrawlPoint(Point &point, Point direction)
   * 
   ****************************************************************/
  void RobotAction::_getCrawlPoint(Point &point, Point direction) {
    point._x += direction._x;
    point._y += direction._y;
    point._z += direction._z;
  }

  /****************************************************************
   * void _getCrawlPoints(RobotLegsPoints &points, Point point)
   * 
   ****************************************************************/
  void RobotAction::_getCrawlPoints(RobotLegsPoints &points, Point point) {
    this -> _getCrawlPoint(points._leg1, point);
    this -> _getCrawlPoint(points._leg2, point);
    this -> _getCrawlPoint(points._leg3, point);
    this -> _getCrawlPoint(points._leg4, point);
    this -> _getCrawlPoint(points._leg5, point);
    this -> _getCrawlPoint(points._leg6, point);
  }

  /****************************************************************
   * void _getTurnPoint(Point &point, float angle)
   * 
   ****************************************************************/
  void RobotAction::_getTurnPoint(Point &point, float angle) {
    float radian = PI * angle / 180;
    
    float x = point._x * cos(radian) - point._y * sin(radian);
    float y = point._x * sin(radian) + point._y * cos(radian);

    point = Point(x, y, point._z);
  }

  /****************************************************************
   * void _getTurnPoints(RobotLegsPoints &points, float angle)
   * 
   ****************************************************************/
  void RobotAction::_getTurnPoints(RobotLegsPoints &points, float angle) {
    this -> _getTurnPoint(points._leg1, angle);
    this -> _getTurnPoint(points._leg2, angle);
    this -> _getTurnPoint(points._leg3, angle);
    this -> _getTurnPoint(points._leg4, angle);
    this -> _getTurnPoint(points._leg5, angle);
    this -> _getTurnPoint(points._leg6, angle);
  }

  /****************************************************************
   * void _legsMoveTo(RobotLegsPoints p, short speed)
   * 
   ****************************************************************/
  void RobotAction::_legsMoveTo(RobotLegsPoints p, short speed) {
    if (_robot.checkPoints(p) == false) return;

    _robot.setSpeed(speed);
    _robot.moveTo  (p);

    _robot.waitUntilFree();
  }

  /****************************************************************
   * void _legsMoveTo(RobotLegsPoints p, short leg, short speed)
   * 
   ****************************************************************/
  void RobotAction::_legsMoveTo(RobotLegsPoints p, short leg, short speed) {
    if (_robot.checkPoints(p) == false) return;

    float d[6] = {
      Point::getDistance(_robot.getLeg1().getPointNow(), p._leg1),
      Point::getDistance(_robot.getLeg2().getPointNow(), p._leg2),
      Point::getDistance(_robot.getLeg3().getPointNow(), p._leg3),
      Point::getDistance(_robot.getLeg4().getPointNow(), p._leg4),
      Point::getDistance(_robot.getLeg5().getPointNow(), p._leg5),
      Point::getDistance(_robot.getLeg6().getPointNow(), p._leg6)
    };
    
    float s[6] = {
      d[0] / d[leg - 1] * speed,
      d[1] / d[leg - 1] * speed,
      d[2] / d[leg - 1] * speed,
      d[3] / d[leg - 1] * speed,
      d[4] / d[leg - 1] * speed,
      d[5] / d[leg - 1] * speed
    };

    _robot.setSpeed( s[0], s[1], s[2], s[3], s[4], s[5]);
    _robot.moveTo  (p);

    _robot.waitUntilFree();
  }

  /****************************************************************
   * void RobotAction::_legsMoveToRelatively(Point delta, short speed)
   * 
   * From points to points + delta
   * 
   ****************************************************************/
  void RobotAction::_legsMoveToRelatively(Point delta, short speed) {
    //TODO
  }
}
