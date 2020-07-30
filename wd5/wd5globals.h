#ifndef WD5_GLOBALS_H
#define WD5_GLOBALS_H

unsigned int DISTANCE_MAX               = 200;
unsigned int DISTANCE_MIN               =  35;
unsigned int DISTANCE_MIN_LATERAL       =  30;
unsigned int DISTANCE_SUPER_MIN         =   5;
float        VOLTAGE_UMBRAL             = 6.5;
int          FORWARD_SPEED              = 150;
int          BACKWARD_SPEED             = 150;
int          TURN_SPEED                 = 150;

bool         DEBUG                      = true;

/**
 * 
 */
enum MotionModeEnum {
  START,
  STOP,
  ALERT,
  ALERT_FLIP,
  FORWARD,
  BACKWARD,
  TURN_LEFT,
  TURN_RIGHT
};

enum AlertSensorEnum {
  SENSOR_FORWARD,
  SENSOR_RIGHT,
  SENSOR_LEFT,
  SENSOR_NONE
};

#endif