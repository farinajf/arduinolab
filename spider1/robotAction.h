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
      const float _BODY_LIFT_STEP_DISTANCE  =   1.0;
      const float _BODY_TWIST_STEP_DISTANCE =   1.25;
      const float _LEG_LIFT_STEP_DISTANCE   =   7.5;
      const float _DISTANCIA_CRAWL          =  42;
      const float _ANGULO_GIRO              =  18;
      const float _LEG_LIFT                 =  20;
      const float _MIN_ALPHA_INTERVAL       =   0;
      
      Robot           _robot;
      RobotLegsPoints _initialPoints;
      RobotLegsPoints _lastChangeLegsStatePoints;
      LegsState       _legsState    = LegsState::CRAWL_STATE;
      RobotMode       _mode         = RobotMode::SLEEP;
      float           _bodyLift     = RobotShape::DEFAULT_BODY_LIFT;
      int             _crawlSteps   = 2;
      int             _legMoveIndex = 1;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _actionState();
      bool _checkCrawlPoints    (RobotLegsPoints  points);
      void _getCrawlPoint       (Point           &point,  Point delta);
      void _getCrawlPoints      (RobotLegsPoints &points, Point delta);
      void _getMoveBodyPoint    (Point           &point,  Point delta);
      void _getMoveBodyPoints   (RobotLegsPoints &points, Point delta);
      void _getRotateBodyPoint  (Point           &point,  Point rotateAxis, float rotateAngle);
      void _getRotateBodyPoints (RobotLegsPoints &points, Point rotateAxis, float rotateAngle);
      void _getTurnPoints       (RobotLegsPoints &points, float angulo);
      void _getTurnPoint        (Point           &point,  float angulo);
      void _legsMoveTo          (RobotLegsPoints  points, float stepDistance);
      void _legsMoveTo          (RobotLegsPoints  points, int   leg,        float stepDistance);
      void _legsMoveToRelatively(Point            point,  float stepDistance);
      void _twistBody           (Point            move,   Point rotateAxis, float rotateAngle);


    public:
      RobotAction();

      void init();
      void changeBodyHeight           (float h);
      void crawl                      (float x, float y, float angulo);
      void crawlForward();
      void crawlBackward();
      void crawlLeft();
      void crawlRight();
      void initialState();
      void legMoveToRelatively        (int   leg,  Point p);
      void legMoveToRelativelyDirectly(int   leg,  Point p);
      void moveBody                   (float x,    float y, float z);
      void rotateBody                 (float x,    float y, float z);
      void setActionGroup             (int   x);
      void setSpeedMultiple           (float x);
      void turnLeft();
      void turnRight();
      void twistBody                  (Point move, Point rotate);
      
      void activeMode();
      void sleepMode();
      void switchMode();

      // INLINE
      Robot& getRobot()    {return _robot;}
      float  getBodyLift() {return _bodyLift;}
  };
}

#endif
