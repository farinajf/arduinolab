#ifndef ROBOT_ACTION_H
#define ROBOT_ACTION_H

#include "globals.h"
#include "robot.h"

namespace SPIDER {
  /**
   * 
   */
  class RobotAction {
    private:
      const float _BODY_LIFT_STEP_DISTANCE = 1.0;
      const float _LEG_LIFT_STEP_DISTANCE  = 7.5;
      
      Robot           _robot;
      RobotLegsPoints _initialPoints;
      RobotLegsPoints _lastChangeLegsStatePoints;
      LegsState       _legsState = LegsState::CRAWL_STATE;
      RobotMode       _mode      = RobotMode::SLEEP;
      float           _bodyLift  = RobotShape::DEFAULT_BODY_LIFT;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _actionState();
      void _getCrawlPoint       (Point           &point,  Point delta);
      void _getCrawlPoints      (RobotLegsPoints &points, Point delta);
      void _legsMoveTo          (RobotLegsPoints  points, float stepDistance);
      void _legsMoveToRelatively(Point            point,  float stepDistance);
      void _twistBody           (Point            move,   Point rotateAxis, float rotateAngle);


    public:
      RobotAction();

      void init();
      void changeBodyHeight           (float h);
      void initialState();
      void legMoveToRelativelyDirectly(int   leg,  Point p);
      
      void activeMode();
      void sleepMode();
      void switchMode();

      //TODO
      void crawl           (float x, float y, float angle) {}
      void crawlForward() {}
      void crawlBackward() {}
      void crawlLeft() {}
      void crawlRight() {}
      void moveBody        (float x, float y, float z) {}
      void rotateBody      (float x, float y, float z) {}
      void setActionGroup  (int   x) {}
      void setSpeedMultiple(float x) {}
      void turnLeft() {}
      void turnRight() {}
      void twistBody(Point move, Point rotate) {}

      // INLINE
      Robot& getRobot() {return _robot;}
  };
}

#endif
