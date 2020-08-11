#ifndef WD5_GLOBALS_H
#define WD5_GLOBALS_H

/*
#define MODO_DEBUG
*/

unsigned int DISTANCE_MAX               = 200;
unsigned int DISTANCE_MIN               =  35;
unsigned int DISTANCE_MIN_LATERAL       =  30;
unsigned int DISTANCE_SUPER_MIN         =   5;
float        VOLTAGE_UMBRAL             = 6.5;
#ifdef MODO_DEBUG
bool         DEBUG                      = true;
int          FORWARD_SPEED              = 0;
int          BACKWARD_SPEED             = 0;
int          TURN_SPEED                 = 0;
#else
bool         DEBUG                      = false;
int          FORWARD_SPEED              = 250;
int          BACKWARD_SPEED             = 200;
int          TURN_SPEED                 = 200;
#endif
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

enum AlertSensorEnum {
  SENSOR_FORWARD,
  SENSOR_RIGHT,
  SENSOR_LEFT,
  SENSOR_NONE
};

#endif
