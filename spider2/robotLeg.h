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
      void _getAngles  (float x,     float y,    float z,     float          &alpha, float      &beta, float       &gamma);
      void _getPoint   (float alpha, float beta, float gamma, Point          &p);
      void _getPoint   (float alpha, float beta, float gamma, volatile float &x, volatile float &y, volatile float &z);
      bool _checkAngles(float alpha, float beta, float gamma);
      void _rotate     (float alpha, float beta, float gamma);
       

    public:
      static constexpr float DEFAULT_STEP_DISTANCE = 2.0;
      static constexpr float NEGLIGIBLE_DISTANCE   = 0.1;

      
      RobotLeg(float x0, float y0);

      void init(const RobotLegItemParam &coxa, const RobotLegItemParam &femur, const RobotLegItemParam &tibia);

      void getAngles      (Point destino, float &alpha, float &beta, float &gamma);
      bool checkPoint     (Point point);
      void move           (Point destino);
      void moveDirectly   (Point destino);
      void shift          (Point delta);
      void setOffsetEnable(bool  x);
      void setServos      (float alpha, float beta, float gamma);
      void update         (float speed);



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
