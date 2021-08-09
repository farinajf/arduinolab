#ifndef ROBOT_LEG_H
#define ROBOT_LEG_H

#include "globals.h"
#include "servoDriver.h"
#include "robotLegItem.h"

#define ROBOT_LEG_DEFAULT_STEP_DISTANCE 2
#define ROBOT_LEG_NEGLIGIBLE_DISTANCE   0.1

namespace SPIDER {
  const float L_COXA  = 60.0;
  const float L_FEMUR = 40.0;
  const float L_TIBIA = 64.0;

  const float X0 = 60.0;
  const float Y0 = 82.5;

  const uint8_t LEG1_ADDR       [3] = {  0,   1,   2}; //Delantera
  const uint8_t LEG2_ADDR       [3] = {  4,   5,   6}; //Media
  const uint8_t LEG3_ADDR       [3] = {  8,   9,  10}; //Trasera
  const uint8_t LEG4_ADDR       [3] = { 15,  14,  13};
  const uint8_t LEG5_ADDR       [3] = { 11,  10,   9};
  const uint8_t LEG6_ADDR       [3] = {  7,   6,   5};

  const short   LEG_POSITION_0 [3] = {120, 120, 120};
  const short   LEG_POSITION_90[3] = {335, 335, 335};

  const short   LEG1_MIN_ANGLE_90[3] = {  90, -90,  20}, LEG2_MIN_ANGLE_90[3] = { 135, -90,  20}, LEG3_MIN_ANGLE_90[3] = {-200, -90,  20}, LEG4_MIN_ANGLE_90[3] = { -20, -90,  20}, LEG5_MIN_ANGLE_90[3] = { -45, -90,  20}, LEG6_MIN_ANGLE_90[3] = { -90, -90,  20};
  const short   LEG1_MAX_ANGLE_90[3] = { 200,  90, 180}, LEG2_MAX_ANGLE_90[3] = { 225,  90, 180}, LEG3_MAX_ANGLE_90[3] = { -90,  90, 180}, LEG4_MAX_ANGLE_90[3] = {  90,  90, 180}, LEG5_MAX_ANGLE_90[3] = {  45,  90, 180}, LEG6_MAX_ANGLE_90[3] = {  20,  90, 180};

  const short   LEG1_ZERO_ANGLE_90[3] = { -45,  90, 180}; // Done
  const short   LEG2_ZERO_ANGLE_90[3] = { -90,  90, 180}; // Done
  const short   LEG3_ZERO_ANGLE_90[3] = {-135,  90, 180}; // Done
  const short   LEG4_ZERO_ANGLE_90[3] = {  45,  90,   0}; // Done
  const short   LEG5_ZERO_ANGLE_90[3] = {  90,  90,   0}; // Done
  const short   LEG6_ZERO_ANGLE_90[3] = { 135,  90,   0}; // Done

  const bool    LEG_1_3_JOIN_DIR[3] = {true, true,  false};
  const bool    LEG_4_6_JOIN_DIR[3] = {true, false, true};

  /**
   *      P1 +---------------------+ P4    ^          P1_COXA = (-X_COXA,  Y_COXA, H)
   *         |                     |       |          P2_COXA = (-X_COXA,  0,      H)
   *         |        y^           |       |          P3_COXA = (-X_COXA, -Y-COXA, H)
   *         |         |           |       |          P4_COXA = ( X_COXA,  Y-COXA, H)
   *         |         |           |       |          P5_COXA = ( X_COXA,  0,      H)
   *      P2 +         +-->        + P5   2Y0         P6_COXA = ( X_COXA, -Y-COXA, H)
   *         |            x        |       |
   *         |                     |       |
   *         |                     |       |
   *         |                     |       |
   *      P3 +---------------------+ P6    v
   *         <-------- 2X0 ------->
   *
   *
   */
  class RobotLeg {
    private:
      const RobotLegItem _coxa;
      const RobotLegItem _femur;
      const RobotLegItem _tibia;
      const float        _x0;
      const float        _y0;

      volatile short _stepDistance = ROBOT_LEG_DEFAULT_STEP_DISTANCE;
      volatile bool  _firstMove    = true;
      volatile bool  _isBusy       = false;
      
      ServoDriver   *_driver;
      Point          _pointNow;
      Point          _pointGoal;

      
      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _calculateAngle  (float x,     float y,     float z,     float &alpha, float &beta, float &gamma);
      void _calculatePoint  (float alpha, float beta,  float gamma, Point &point);
      void _calculatePoint  (float alpha, float beta,  float gamma, float &x, float &y, float &z);
      bool _checkAngle      (float alpha, float beta,  float gamma);
      void _rotateToDirectly(float alpha, float beta,  float gamma);

    public:
      RobotLeg(const uint8_t addr[3],
               const short   position_0[3],
               const short   position_90[3],
               const float   x0,
               const float   y0,
               const short   minAngle[3],
               const short   maxAngle[3],
               const short   zeroAngle[3],
               const bool    jointDir[3]);

      void init();

      void calculateAngle(Point &point, float &alpha, float &beta,  float &gamma);
      bool checkPoint    (Point &p);
      void moveTo        (Point  p);
      void moveToDirectly(Point  p);

      // INLINE
      RobotLegItem getCoxa()         {return _coxa;}
      RobotLegItem getFemur()        {return _femur;}
      RobotLegItem getTibia()        {return _tibia;}
      ServoDriver* getDriver()       {return _driver;}
      Point        getPointNow()     {return _pointNow;}
      Point        getPointGoal()    {return _pointGoal;}
      short        getStepDistance() {return _stepDistance;}
      bool         isBusy()          {return _isBusy;}
      
      void setBusy        (bool         x) {_isBusy       = x;}
      void setDriver      (ServoDriver *x) {_driver       = x;}
      void setStepDistance(short        x) {_stepDistance = x;}
  };
}

#endif
