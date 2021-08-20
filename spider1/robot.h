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
   
  const RobotLegItemParam LEG1_COXA  = RobotLegItemParam(39,  -45,   90, 200, true,  EepromAddresses::servo39);
  const RobotLegItemParam LEG2_COXA  = RobotLegItemParam(36,  -90,  135, 225, true,  EepromAddresses::servo36);
  const RobotLegItemParam LEG3_COXA  = RobotLegItemParam(33, -135, -200, -90, true,  EepromAddresses::servo33);
  const RobotLegItemParam LEG4_COXA  = RobotLegItemParam(22,   45,  -20,  90, true,  EepromAddresses::servo22);
  const RobotLegItemParam LEG5_COXA  = RobotLegItemParam(25,   90,  -45,  45, true,  EepromAddresses::servo25);
  const RobotLegItemParam LEG6_COXA  = RobotLegItemParam(28,  135,  -90,  20, true,  EepromAddresses::servo28);

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


  const RobotLegsPoints CALIBRATE_STATE_POINTS = RobotLegsPoints(Point(-133,  100, 25),
                                                                 Point(-155,    0, 25),
                                                                 Point(-133, -100, 25),
                                                                 Point( 133,  100, 25),
                                                                 Point( 155,    0, 25),
                                                                 Point( 133, -100, 25));
                                                           
  const RobotLegsPoints CALIBRATE_POINTS       = RobotLegsPoints(Point(-103,  85, 0),
                                                                 Point(-125,   0, 0),
                                                                 Point(-103, -85, 0),
                                                                 Point( 103,  85, 0),
                                                                 Point( 125,   0, 0),
                                                                 Point( 103, -85, 0));
                                                      
  const RobotLegsPoints BOOT_POINTS            = RobotLegsPoints(Point( -81,  99, 0),
                                                                 Point(-115,   0, 0),
                                                                 Point( -81, -99, 0),
                                                                 Point(  81,  99, 0),
                                                                 Point( 115,   0, 0),
                                                                 Point(  81, -99, 0));

  /**
   * 
   */
  class Robot {
    private:
      volatile float _speedMultiple = 1.0;
      
      RobotState     _state = RobotState::BOOT;
      RobotLeg       _leg1;
      RobotLeg       _leg2;
      RobotLeg       _leg3;
      RobotLeg       _leg4;
      RobotLeg       _leg5;
      RobotLeg       _leg6;
      Power          _power;
      int            _dataFormatVersion;
      int            _productVersion;



      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _moveTo         (RobotLegsPoints p);
      void _moveToDirectly (RobotLegsPoints p);
      void _setOffsetEnable(bool            x);
      void _setStepDistance(float           x);
      void _updateAction();
      void _waitUntilFree() const;


    public:
      Robot();

      void init();
      void bootState();
      void calibrateState();
      void installState();
      void update();

      //TODO
      void calibrateVerify() {}

      // INLINE
      Power&     getPower() {return _power;}
      RobotState getState() {return _state;}
      
      void setState(RobotState x) {_state = x;}
  };
}

#endif
