#ifndef ROBOT_LEG_ITEM_H
#define ROBOT_LEG_ITEM_H

#include "globals.h"
#include "servoDriver.h"

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

      static float getDistance(Point p1, Point p2);
  };

  /**
   * 
   */
  class RobotLegsPoints {
    private:

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
  
  class RobotLegItem {
    private:
      const uint8_t  _addr;
      const short    _position_0;
      const short    _position_90;
      const short    _minAngle;
      const short    _maxAngle;
      const short    _zeroAngle;
      const bool     _jointDir;

      volatile float _servoAngleNow;
      volatile float _angleNow;
      volatile bool  _firstRotate = true;

      /*********************************************************
       *                Metodos privados
       *********************************************************/
      
    public:
      RobotLegItem(const uint8_t addr, const short position_0, const short position_90, const short minAngle, const short maxAngle, const short zeroAngle, const bool jointDir);

      void init();
      bool checkJointAngle (float        jointAngle) const;
      void rotateToDirectly(ServoDriver *driver, float jointAngle);
  };
}

#endif
