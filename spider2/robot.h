#ifndef ROBOT_H
#define ROBOT_H

#include "globals.h"
#include "power.h"
#include "robotLeg.h"

namespace SPIDER {
  /**
   *                   |-|USB 
   *           P1 +--------------+ P4       ^          P1_COXA = (-X0_COXA,  Y_COXA, H)
   *             /                \         |          P2_COXA = (-X1_COXA,  0,      H)
   *            /        y^        \        |          P3_COXA = (-X0_COXA, -Y_COXA, H)
   *           /          |         \       |          P4_COXA = ( X0_COXA,  Y_COXA, H)
   *          /           |          \      |          P5_COXA = ( X1_COXA,  0,      H)
   *      P2 +            +-->        + P5   2Y0       P6_COXA = ( X0_COXA, -Y_COXA, H)
   *          \            x         /      |
   *           \                    /       |
   *            \                  /        |
   *             \                /         |
   *           P3 +--------------+ P6       v
   *              <-------- 2X0 ------->
   *
   *
   */
   
  const RobotLegItemParam LEG1_COXA  = RobotLegItemParam(39,  225,   90, 200, false, EepromAddresses::servo39);
  const RobotLegItemParam LEG2_COXA  = RobotLegItemParam(36,  270,  135, 225, false, EepromAddresses::servo36);
  const RobotLegItemParam LEG3_COXA  = RobotLegItemParam(33,  -45, -200, -90, false, EepromAddresses::servo33);
  const RobotLegItemParam LEG4_COXA  = RobotLegItemParam(22,  135,  -20,  90, false, EepromAddresses::servo22);
  const RobotLegItemParam LEG5_COXA  = RobotLegItemParam(25,   90,  -45,  45, false, EepromAddresses::servo25);
  const RobotLegItemParam LEG6_COXA  = RobotLegItemParam(28,   45,  -90,  20, false, EepromAddresses::servo28);

  const RobotLegItemParam LEG1_FEMUR = RobotLegItemParam(38,   90,  -90,  90, true,  EepromAddresses::servo38);
  const RobotLegItemParam LEG2_FEMUR = RobotLegItemParam(35,   90,  -90,  90, true,  EepromAddresses::servo35);
  const RobotLegItemParam LEG3_FEMUR = RobotLegItemParam(32,   90,  -90,  90, true,  EepromAddresses::servo32);
  const RobotLegItemParam LEG4_FEMUR = RobotLegItemParam(23,   90,  -90,  90, false, EepromAddresses::servo23);
  const RobotLegItemParam LEG5_FEMUR = RobotLegItemParam(26,   90,  -90,  90, false, EepromAddresses::servo26);
  const RobotLegItemParam LEG6_FEMUR = RobotLegItemParam(29,   90,  -90,  90, false, EepromAddresses::servo29);

  const RobotLegItemParam LEG1_TIBIA = RobotLegItemParam(37,  180,    0, 180, false, EepromAddresses::servo37);
  const RobotLegItemParam LEG2_TIBIA = RobotLegItemParam(34,  180,    0, 180, false, EepromAddresses::servo34);
  const RobotLegItemParam LEG3_TIBIA = RobotLegItemParam(31,  180,    0, 180, false, EepromAddresses::servo31);
  const RobotLegItemParam LEG4_TIBIA = RobotLegItemParam(24,    0,    0, 180, true,  EepromAddresses::servo24);
  const RobotLegItemParam LEG5_TIBIA = RobotLegItemParam(27,    0,    0, 180, true,  EepromAddresses::servo27);
  const RobotLegItemParam LEG6_TIBIA = RobotLegItemParam(30,    0,    0, 180, true,  EepromAddresses::servo30);


  const RobotLegsPoints CALIBRATE_STATE_POINTS = RobotLegsPoints(Point(-133,  100, -25),
                                                                 Point(-155,    0, -25),
                                                                 Point(-133, -100, -25),
                                                                 Point( 133,  100, -25),
                                                                 Point( 155,    0, -25),
                                                                 Point( 133, -100, -25));
                                                           
  const RobotLegsPoints CALIBRATE_POINTS       = RobotLegsPoints(Point(-103,  85, 0),
                                                                 Point(-125,   0, 0),
                                                                 Point(-103, -85, 0),
                                                                 Point( 103,  85, 0),
                                                                 Point( 125,   0, 0),
                                                                 Point( 103, -85, 0));
                                                      
//  const RobotLegsPoints BOOT_POINTS            = RobotLegsPoints(Point( -81,  99, 0),
//                                                                 Point(-115,   0, 0),
//                                                                 Point( -81, -99, 0),
//                                                                 Point(  81,  99, 0),
//                                                                 Point( 115,   0, 0),
//                                                                 Point(  81, -99, 0));
  
  const RobotLegsPoints BOOT_POINTS            = RobotLegsPoints(Point( -85,  115, 0),
                                                                 Point(-125,    0, 0),
                                                                 Point( -85, -115, 0),
                                                                 Point(  85,  115, 0),
                                                                 Point( 125,    0, 0),
                                                                 Point(  85, -115, 0));


  /**
   * 
   */
  class Robot {
    private:
      volatile float _speed = 1.0;
      
      RobotState _state = RobotState::BOOT;
      RobotLeg   _leg1;
      RobotLeg   _leg2;
      RobotLeg   _leg3;
      RobotLeg   _leg4;
      RobotLeg   _leg5;
      RobotLeg   _leg6;
      Power      _power;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _calibrateLeg   (RobotLeg       &leg, Point calibratePoint);
      void _moveDirectly   (RobotLegsPoints p);
      void _setOffsetEnable(bool            x);
      void _setStepDistance(float           x);
      void _update();


    public:
      Robot();

      void init();
      void calibrateServos();
      void calibrateVerify();
      bool checkPoints     (RobotLegsPoints  points);
      void getPointsNow    (RobotLegsPoints &points);
      void move            (RobotLegsPoints  points);
      void move            (RobotLegsPoints  points, float stepDistance);
      void setSpeed        (float x);
      void setStepDistance (float x1, float x2, float x3, float x4, float x5, float x6);
      void update();
      void waitUntilFree() const;
      
      void bootState();
      void calibrateState();
      void installState();


      // INLINE
      RobotLeg&  getLeg1()  {return _leg1;}
      RobotLeg&  getLeg2()  {return _leg2;}
      RobotLeg&  getLeg3()  {return _leg3;}
      RobotLeg&  getLeg4()  {return _leg4;}
      RobotLeg&  getLeg5()  {return _leg5;}
      RobotLeg&  getLeg6()  {return _leg6;}
      Power&     getPower() {return _power;}
      RobotState getState() {return _state;}
      
      void setState(RobotState x) {_state = x;}
  };
}

#endif
