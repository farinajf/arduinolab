#ifndef ROBOT_LEG_ITEM_H
#define ROBOT_LEG_ITEM_H

#include "globals.h"
#include <EEPROM.h>
#include <Servo.h>
#include <FlexiTimer2.h>

namespace SPIDER {
  /**
   * 
   */
  class Point {
    public:
      volatile float _x;
      volatile float _y;
      volatile float _z;

      Point();
      Point(float x, float y, float z);
      Point(Point p, float x, float y, float z);

      static float getDistance(Point p1, Point p2);

      float norma2();
  };

  /**
   * 
   */
  class RobotLegsPoints {
    public:
      Point _leg1;
      Point _leg2;
      Point _leg3;
      Point _leg4;
      Point _leg5;
      Point _leg6;

      RobotLegsPoints() {}
      RobotLegsPoints(Point leg1, Point leg2, Point leg3, Point leg4, Point leg5, Point leg6) : _leg1(leg1), _leg2(leg2), _leg3(leg3), _leg4(leg4), _leg5(leg5), _leg6(leg6) {}
  };

  /**
   * 
   */
  class RobotLegItemParam {
    public:
      int   _servoPin;
      float _anguloZero;
      float _anguloMin;
      float _anguloMax;
      bool  _sumaResta;
      int   _offsetAddress;

      RobotLegItemParam() {}
      RobotLegItemParam(int servoPin, float anguloZero, float anguloMin, float anguloMax, bool sumaResta, int offsetAddress) :
                        _servoPin     (servoPin),
                        _anguloZero   (anguloZero),
                        _anguloMin    (anguloMin),
                        _anguloMax    (anguloMax),
                        _sumaResta    (sumaResta),
                        _offsetAddress(offsetAddress) {}
  };




  /**
   * class RobotLegItem
   */
  class RobotLegItem {
    private:
      RobotLegItemParam _params;
      Servo             _servo;

      volatile float _angulo       = 0;
      volatile float _anguloServo  = 0;
      volatile float _offset       = 0;
      volatile bool  _firstRotate  = true;
      volatile bool  _offsetEnable = true;

      /*********************************************************
       *                Metodos privados
       *********************************************************/
      float _getServoAngle(float angulo);
      
    
    
    public:
      static int FIRST_ROTATE_DELAY;
      
      RobotLegItem();

      void  init      (const RobotLegItemParam params);
      bool  checkAngle(float                   angulo);
      float getAngle  (float                   anguloServo);
      void  rotate    (float                   angulo);
      void  setOffset (float                   x);

      //INLINE
      float getAngle() {return _angulo;}

      void setOffsetEnable(bool  x) {_offsetEnable = x;}
  };
}

#endif
