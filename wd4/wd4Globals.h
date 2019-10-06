#ifndef WD4_GLOBALS_H
#define WD4_GLOBALS_H

unsigned int DISTANCE_SUPER_MAX = 400;
unsigned int DISTANCE_MAX       =  30;
unsigned int DISTANCE_MIN       =  10;
unsigned int DISTANCE_SUPER_MIN =   3;
float        VOLTAGE_UMBRAL     = 6.5;
bool         MODO_PRUEBAS       = false;
int          FORWARD_SPEED      = 200;
int          BACKWARD_SPEED     = 200;
int          TURN_SPEED         = 200;

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
