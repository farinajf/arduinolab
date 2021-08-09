#ifndef ROBOT_ACTION_H
#define ROBOT_ACTION_H

#include "robot.h"

#define ROBOT_ACTION_DEFAULT_BODY_LIFT -100
#define ROBOT_ACTION_BODY_LIFT_SPEED      1
#define ROBOT_ACTION_CRAWL_LENGTH        42
#define ROBOT_ACTION_TURN_ANGLE          18
#define ROBOT_ACTION_CRAWL_STEPS          6 //2, 4, 6
#define ROBOT_ACTION_LEG_LIFT            20
#define ROBOT_ACTION_LEG_LIFT_SPEED       7.5

namespace SPIDER {
  /**
   * 
   */
  class RobotAction {
    private:
      const Robot _robot;

      RobotLegsPoints _lastChangeLegsStatePoints;
      RobotLegsPoints _initialPoints;
      LegsState       _legsState    = LegsState::CRAWL_STATE;
      RobotMode       _mode         = RobotMode::SLEEP;
      float           _bodyLift     = (float) ROBOT_ACTION_DEFAULT_BODY_LIFT;
      int             _legMoveIndex = 1;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _actionState();
      bool _checkCrawlPoints    (RobotLegsPoints  points);
      void _crawl6Steps         (RobotLegsPoints &points1, RobotLegsPoints &points2, RobotLegsPoints &points3, RobotLegsPoints &points4, RobotLegsPoints &points5);
      void _legsMoveTo          (RobotLegsPoints  points,  short speed);
      void _legsMoveTo          (RobotLegsPoints  points,  short leg, short speed);
      void _legsMoveToRelatively(Point            delta,   short speed);
      void _getCrawlPoints      (RobotLegsPoints &points,  Point point);
      void _getCrawlPoint       (Point           &point,   Point direction);
      void _getTurnPoints       (RobotLegsPoints &points,  float angle);
      void _getTurnPoint        (Point           &point,   float angle);

    public:
      RobotAction();

      void init();
      
      void activeMode();
      void initialState();
      void sleepMode();
      void switchMode();

      void changeBodyHeight(float h);
      void crawl           (float x, float y, float angle);
      void crawlForward();
      void crawlBackward();
      void crawlLeft();
      void crawlRight();
      void turnLeft();
      void turnRight();
      void update();

      Robot* getRobot() const {return &_robot;}
  };
}

#endif
