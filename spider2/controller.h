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
      const float _DISTANCIA_CICLO          =  40; //42
      const float _ANGULO_GIRO              =  25; //18
      const float _ALTURA_SUSPENSION        =  20;
      const float _MIN_ALPHA_INTERVAL       =   0;


      Robot           _robot;
      RobotLegsPoints _posicionUltima;
      RobotLegsPoints _posicionInicial;
      RobotCrawlMode  _crawlMode       = RobotCrawlMode::TRIPOD;
      float           _altura          = RobotShape::DEFAULT_BODY_LIFT;
      LegsState       _estadoPatas     = LegsState::CRAWL_STATE;
      RobotMode       _modo            = RobotMode::SLEEP;
      int             _pasoCiclo       = 0;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _addDelta       (RobotLegsPoints &points, Point delta);
      void _addDelta       (Point           &point,  Point delta);
      void _addGiro        (RobotLegsPoints &points, float angulo);
      void _addGiro        (Point           &point,  float angulo);
      bool _checkPoints    (RobotLegsPoints  points);
      void _crawlRipple    (float            x,      float y,          float angulo);
      void _crawlTripod    (float            x,      float y,          float angulo);
      void _crawlWave      (float            x,      float y,          float angulo);
      void _getRotatePoint (Point           &point,  Point rotateAxis, float rotateAngle);
      void _getRotatePoints(RobotLegsPoints &points, Point rotateAxis, float rotateAngle);
      void _move           (RobotLegsPoints  points, float stepDistance);
      void _move           (RobotLegsPoints  points, int   leg,        float stepDistance);
      void _setActionState();
      void _setBodyHeight  (float            h);
      void _twistBody      (Point            delta,  Point rotateAxis, float rotateAngle);
      
      // INLINE
      void _addPasoCiclo() {
        (_pasoCiclo < _getTotalPasosCiclo()) ? _pasoCiclo++ : _pasoCiclo = 1;
      }
      
      int _getTotalPasosCiclo() {
        switch (_crawlMode)
        {
          case RobotCrawlMode::TRIPOD: return 2;
          case RobotCrawlMode::RIPPLE: return 6;
          case RobotCrawlMode::WAVE:   return 6;
        }
      }


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
      void moveBody        (float x,    float y, float z);
      void rotateBody      (float x,    float y, float z);
      void setPasosCiclo   (int   x);
      void setSpeed        (float x);
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
