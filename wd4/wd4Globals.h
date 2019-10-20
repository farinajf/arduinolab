#ifndef WD4_GLOBALS_H
#define WD4_GLOBALS_H

unsigned int DISTANCE_SUPER_MAX         = 400;
unsigned int DISTANCE_MAX               =  30;
unsigned int DISTANCE_MIN               =  20;
unsigned int DISTANCE_SUPER_MIN         =   3;
unsigned int DISTANCE_MIN_LATERAL       =  20;
unsigned int DISTANCE_SUPER_MIN_LATERAL =   5;
float        VOLTAGE_UMBRAL             = 6.5;
int          FORWARD_SPEED              = 200;
int          BACKWARD_SPEED             = 200;
int          TURN_SPEED                 = 200;

bool         MODO_PRUEBAS               = false;

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
