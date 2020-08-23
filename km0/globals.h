#ifndef GLOBALS_H
#define GLOBALS_H 0

unsigned int DISTANCE_MAX         = 200;
unsigned int DISTANCE_MIN_FAST    =  50;
unsigned int DISTANCE_MIN         =  30;
unsigned int DISTANCE_MIN_LATERAL =  10;
unsigned int DISTANCE_SUPER_MIN   =   5;
int          FORWARD_SPEED_FAST   = 200;
int          FORWARD_SPEEP_SLOW   = 150;
int          BACKWARD_SPEED       = 150;
int          TURN_SPEED           = 150;
bool         DEBUG                = false;

/**
 * 
 */
enum MotionModeEnum {
  START,
  STOP,
  ALERT,
  FORWARD,
  BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
  FLIP_LEFT,
  FLIP_RIGHT
};

#endif
