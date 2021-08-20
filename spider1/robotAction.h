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
      void _getCrawlPoint (Point           &point,  Point direccion);
      void _getCrawlPoints(RobotLegsPoints &points, Point direccion);

      //TODO
      void _legsMoveToRelatively(Point point, float stepDistance) {}

    public:
      RobotAction();

      void init();
      void activeMode();
      void sleepMode();

      //TODO
      void changeBodyHeight(float h) {}
      void crawl           (float x, float y, float angle) {}
      void crawlForward() {}
      void crawlBackward() {}
      void crawlLeft() {}
      void crawlRight() {}
      void initialState() {}
      void moveBody  (float x, float y, float z) {}
      void rotateBody(float x, float y, float z) {}
      void switchMode() {}
      void turnLeft() {}
      void turnRight() {}
      void twistBody(Point move, Point rotate) {}

      // INLINE
      Robot& getRobot() {return _robot;}
  };
}

#endif
