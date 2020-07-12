#ifndef ROVER5_GLOBALS_H
#define ROVER5_GLOBALS_H

unsigned int DISTANCE_MIN_LATERAL =  25;
unsigned int DISTANCE_MIN         =  35;
unsigned int DISTANCE_MAX         = 200; // Distancia maxima en cm
unsigned int PING_INTERVAL        =  50; // Intervalo entre PINGs

enum MotionModeEnum {
  START,
  STOP,
  ALERT,
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
