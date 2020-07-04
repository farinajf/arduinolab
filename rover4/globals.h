#ifndef ROVER4_GLOBALS_H
#define ROVER4_GLOBALS_H

unsigned int DISTANCE_MIN_LATERAL =  25;
unsigned int DISTANCE_MIN         =  30;
unsigned int DISTANCE_MAX         = 200;
bool         MODO_PRUEBAS         = false;

/**
 * 
 */
enum MOTION_MODE_ENUM {
  START,
  FORWARD,
  TURNLEFT,
  TURNRIGHT,
  BACKWARD_LEFT,
  BACKWARD_RIGHT,
  STOP
};

/**
 * 
 */
enum POSITION_OBSTACLE_ENUM {
  RIGHT,
  LEFT,
  FRONT_LEFT,
  FRONT_RIGHT,
  NONE
};

#endif
