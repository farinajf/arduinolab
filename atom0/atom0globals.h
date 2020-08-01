#ifndef ATOM0_GLOBALS_H
#define ATOM0_GLOBALS_H

unsigned int DISTANCE_MAX        = 200;
unsigned int DISTANCE_MIN        =  35;
unsigned int DISTANCE_SUPER_MIN  =   5;
unsigned int PING_INTERVAL       =  50; // Intervalo entre PINGs
int          FORWARD_SPEED       = 150;
int          BACKWARD_SPEED      = 150;
int          TURN_SPEED          = 100;

bool         DEBUG               = true;

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
  TURN_RIGHT
};

#endif
