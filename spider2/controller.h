#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "globals.h"
#include "robot.h"

namespace SPIDER {

  
  /**
   * 
   */
  class RobotController {
    private:
      const float _BODY_LIFT_STEP_DISTANCE  =   1.0;
      const float _BODY_TWIST_STEP_DISTANCE =   1.25;
      const float _LEG_LIFT_STEP_DISTANCE   =   7.5;

      
      Robot           _robot;
      RobotLegsPoints _posicionInicial;
      float           _altura      = RobotShape::DEFAULT_BODY_LIFT;
      LegsState       _estadoPatas = LegsState::CRAWL_STATE;
      RobotMode       _modo        = RobotMode::SLEEP;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _addDelta      (Point           &point,  Point delta);
      void _addDelta      (RobotLegsPoints &points, Point delta);
      void _move          (RobotLegsPoints  points, float stepDistance);
      void _setActionState();
      void _setBodyHeight (float            h);
      void _twistBody     (Point            move,   Point rotateAxis, float rotateAngle) {} //TODO


    public:
      RobotController();

      void init();
      void changeBodyHeight(float h);
      void crawl           (float x, float y, float angulo);
      void crawlForward();
      void crawlBackward();
      void crawlLeft();
      void crawlRight();
      void turnLeft();
      void turnRight();
      void twistBody       (Point move, Point rotate);

      void setActiveMode();
      void setCrawlLegState();
      void setSleepMode();
      void switchMode();
      
      // INLINE
      Robot& getRobot()  {return _robot;}
      float  getAltura() {return _altura;}
  };
}

#endif
