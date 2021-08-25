#ifndef ROBOT_LEG_H
#define ROBOT_LEG_H

#include "globals.h"
#include "robotLegItem.h"

namespace SPIDER {
      
  /**
   * 
   */
  class RobotLeg {
    private:
      const    float  _x0;
      const    float  _y0;

      volatile float _stepDistance = DEFAULT_STEP_DISTANCE;
      volatile bool  _firstMove    = true;
      volatile bool  _busy         = false;
      
      RobotLegItem _coxa;
      RobotLegItem _femur;
      RobotLegItem _tibia;
      Point        _posicionActual;
      Point        _posicionFinal;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _calculateAngle  (float x,     float y,    float z,     float          &alpha, float      &beta, float       &gamma);
      void _calculatePoint  (float alpha, float beta, float gamma, Point          &p);
      void _calculatePoint  (float alpha, float beta, float gamma, volatile float &x, volatile float &y, volatile float &z);
      bool _checkAngle      (float alpha, float beta, float gamma);
      void _rotateToDirectly(float alpha, float beta, float gamma);
       

    public:
      static constexpr float DEFAULT_STEP_DISTANCE = 2.0;
      static constexpr float NEGLIGIBLE_DISTANCE   = 0.1;

      
      
      RobotLeg(float x0, float y0);

      void init(const RobotLegItemParam &coxa, const RobotLegItemParam &femur, const RobotLegItemParam &tibia);

      void calculateAngle  (Point destino, float &alpha, float &beta, float &gamma);
      bool checkPoint      (Point point);
      void moveTo          (Point destino);
      void moveToDirectly  (Point destino);
      void moveToRelatively(Point destino);
      void setOffsetEnable (bool  x);
      void rotarServos     (float alpha, float beta, float gamma);
      void updateLegAction (float speed);



      // INLINE
      RobotLegItem& getCoxa()           {return _coxa;}
      RobotLegItem& getFemur()          {return _femur;}
      RobotLegItem& getTibia()          {return _tibia;}
      Point&        getPosicionActual() {return _posicionActual;}
      bool          isBusy()            {return _busy;}
      
      void setStepDistance(float x) {_stepDistance = x;}
  };
}

#endif
