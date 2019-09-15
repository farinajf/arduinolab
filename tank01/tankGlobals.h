#ifndef TANK_GLOBALS_H
#define TANK_GLOBALS_H

const double DISTANCIA_MINIMA =   4.0;
const int    VELOCIDAD        = 200;
const int    VELOCIDAD_GIRO   = 200;

enum MOTION_MODE_ENUM {
  STANDBY,
  FORWARD,
  BACKWARD,
  TURNLEFT,
  TURNRIGHT,
  STOP,
  START
} _MOTION_MODE_ = START;
#endif
