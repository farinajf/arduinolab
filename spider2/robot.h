#ifndef ROBOT_H
#define ROBOT_H

#include "globals.h"
#include "servoDriver.h"
#include "robotLeg.h"

namespace SPIDER {
  /**
   *      P1 +---------------------+ P4
   *         |                     |   
   *         |        y^           |   
   *         |         |           |   
   *         |         |           |   
   *      P2 +         +-->        + P5
   *         |            x        |
   *         |                     |
   *         |                     |
   *         |                     |
   *      P3 +---------------------+ P6
   */
  class Robot {
    private:
      const RobotLegsPoints _BOOT_POINTS = RobotLegsPoints(Point(-105,  135, -100),   // 130.6º, -81.4º,  49.0º
                                                           Point(-125,    0, -100),   // 180.0º, -87.2º,  48.2º
                                                           Point(-105, -135, -100),   //-130.6º, -81.4º,  49.0º
                                                           Point( 105,  135, -100),   // 49.04º, -81.4º,  49.0º
                                                           Point( 125,    0, -100),   //     0º, -87.2º,  48.2º 
                                                           Point( 105, -135, -100));  // -49.4º, -81.4º,  49.0º
      const ServoDriver _rightDriver;
      const ServoDriver _leftDriver;

      RobotState _state = RobotState::BOOT;
      RobotLeg   _leg1;
      RobotLeg   _leg2;
      RobotLeg   _leg3;
      RobotLeg   _leg4;
      RobotLeg   _leg5;
      RobotLeg   _leg6;
      short      _speedMultiple = 1;

      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _moveToDirectly(RobotLegsPoints *points);
      void _updateAction  ();
      void _updateAction  (RobotLeg        &leg);

    public:
      Robot();

      void init();
      void bootState   ();
      bool checkPoints (RobotLegsPoints &p);
      void getPointsNow(RobotLegsPoints &p);
      void moveTo      (RobotLegsPoints  p);
      void setSpeed    (short            speed);
      void setSpeed    (short            s1, short s2, short s3, short s4, short s5, short s6);
      void update();
      void waitUntilFree();

      RobotLegsPoints getBootPoints() {return _BOOT_POINTS;}
      RobotLeg        getLeg1()       {return _leg1;}
      RobotLeg        getLeg2()       {return _leg2;}
      RobotLeg        getLeg3()       {return _leg3;}
      RobotLeg        getLeg4()       {return _leg4;}
      RobotLeg        getLeg5()       {return _leg5;}
      RobotLeg        getLeg6()       {return _leg6;}
      RobotState      getState()      {return _state;}

      void setState(RobotState x) {_state = x;}
  };
}

#endif
