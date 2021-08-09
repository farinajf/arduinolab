#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

//Voltaje
#define VOL_MEASURE_PIN    A0

#define GREEN_LED_PIN       4
#define RED_LED_PIN         7
#define IR_RECEIVER_PIN     8
#define STATE_LED_PIN      13
#define FLOAT_PRECISSION    0.001

#define ADDR_PCA9685_RIGHT 0x41
#define ADDR_PCA9685_LEFT  0X40

#define SERIAL_DATA_RATE   115200
#define FIRST_ROTATE_DELAY 50

extern const bool MPU_CALIBRATION;
extern const bool SPIDER_DEBUG;
extern const int  VOLTAGE_UMBRAL;

/**
 * 
 */
enum LegsState {
  CRAWL_STATE,
  TWIST_BODY_STATE,
  LEG_MOVE_STATE
};

/**
 * 
 */
enum RobotMode {
  ACTIVE,
  SLEEP
};

/**
 * 
 */
enum RobotState {
  INSTALL,
  CALIBRATE,
  BOOT,
  ACTION
};

#endif
