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
      const float _DISTANCIA_CICLO          =  40;
      const float _ANGULO_GIRO              =  25;
      const float _ALTURA_SUSPENSION        =  20;
      const float _MIN_ALPHA_INTERVAL       =   0;


      Robot           _robot;
      RobotLegsPoints _posicionInicial;
      float           _altura          = RobotShape::DEFAULT_BODY_LIFT;
      LegsState       _estadoPatas     = LegsState::CRAWL_STATE;
      RobotMode       _modo            = RobotMode::SLEEP;
      int             _totalPasosCiclo = 2;
      int             _pasoCiclo       = 1;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _addDelta      (RobotLegsPoints &points, Point delta);
      void _addDelta      (Point           &point,  Point delta);
      void _addGiro       (RobotLegsPoints &points, float angulo);
      void _addGiro       (Point           &point,  float angulo);
      bool _checkPoints   (RobotLegsPoints  points);
      void _move          (RobotLegsPoints  points, float stepDistance);
      void _move          (RobotLegsPoints  points, int   leg,        float stepDistance);
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
      void moveLeg         (int   leg,  Point p);
      void moveLegDirectly (int   leg,  Point p);
      void setPasosCiclo   (int   x);
      void setSpeed        (float x);
      void turnLeft();
      void turnRight();
      void twistBody       (Point move, Point rotate) {} //TODO

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
