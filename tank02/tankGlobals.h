#ifndef TANK_GLOBALS_H
#define TANK_GLOBALS_H

int _FORWARD_SPEED  = 200;
int _BACKWARD_SPEED = 200;
int _TURN_SPEED     = 200;

unsigned int DISTANCE_SUPER_MAX = 400;
unsigned int DISTANCE_MAX       =  30;
unsigned int DISTANCE_MIN       =  10;
unsigned int DISTANCE_SUPER_MIN =   3;

/**
 * 
 */
enum FUNCTION_MODE_ENUM {
  IDLE,
  OBSTACLE,
  BLUETOOTH
};

/**
 * 
 */
enum MOTION_MODE_ENUM {
  STANDBY,
  FORWARD,
  BACKWARD,
  TURNLEFT,
  TURNRIGHT,
  STOP,
  START
};

#endif
