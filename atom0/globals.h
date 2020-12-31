#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

extern const unsigned int DISTANCE_MAX;
extern const unsigned int DISTANCE_MIN_FAST;
extern const unsigned int DISTANCE_MIN;
extern const unsigned int DISTANCE_SUPER_MIN;
extern const int          PING_INTERVAL;
extern const int          FORWARD_SPEED_FAST;
extern const int          FORWARD_SPEEP_SLOW;
extern const int          BACKWARD_SPEED;
extern const int          TURN_SPEED;

extern const bool         DEBUG;

/************************************************************/
/*                  PINS                                    */
/************************************************************/
//Motor DERECHO
#define PIN_EN_D    10 //PWD
#define PIN_IN1_D    8
#define PIN_IN2_D    7

//Motor IZQUIERDO
#define PIN_EN_I     9 //PWD
#define PIN_IN1_I    2
#define PIN_IN2_I    4

//ULTRASONIC
#define PIN_TRIGGER_CENTER  5
#define PIN_ECHO_CENTER    A3

//INFRARED
#define PIN_IR_LEFT        A4
#define PIN_IR_RIGHT       A5

#define PIN_LED_ALERT      12

#endif
