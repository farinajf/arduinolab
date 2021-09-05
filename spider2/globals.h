#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

#define FLOAT_PRECISSION    0.01

#define STATE_LED_PIN       13
#define POWER_SAMPLING_PIN  A7
#define POWER_GROUP1_PIN   A15
#define POWER_GROUP2_PIN   A13
#define POWER_GROUP3_PIN   A14
#define RF24_PIN            50


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
enum RobotCrawlMode {
  TRIPOD,
  RIPPLE,
  WAVE
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

/**
 * Estado de las ordenes
 */
enum OrderState {
  EXECUTE_START,
  EXECUTE_DONE,
  EXECUTE_NONE
};

/**
 * Origen de las ordenes
 */
enum OrderSource {
  FROM_SERIAL,
  FROM_RF24,
  FROM_ESP8266,
  FROM_NONE
};

/**
 * 
 */
class EepromAddresses {
  public:
    static constexpr float dataFormatVersion = 0;
    static constexpr float servo22 = 100;
    static constexpr float servo23 = 102;
    static constexpr float servo24 = 104;
    static constexpr float servo25 = 106;
    static constexpr float servo26 = 108;
    static constexpr float servo27 = 110;
    static constexpr float servo28 = 112;
    static constexpr float servo29 = 114;
    static constexpr float servo30 = 116;
    static constexpr float servo39 = 118;
    static constexpr float servo38 = 120;
    static constexpr float servo37 = 122;
    static constexpr float servo36 = 124;
    static constexpr float servo35 = 126;
    static constexpr float servo34 = 128;
    static constexpr float servo33 = 130;
    static constexpr float servo32 = 132;
    static constexpr float servo31 = 134;

    static constexpr float robotState = 140;
};

/**
 *                   |-|USB 
 *           P1 +--------------+ P4       ^          P1_COXA = (-X0_COXA,  Y_COXA, H)
 *             /                \         |          P2_COXA = (-X1_COXA,  0,      H)
 *            /        y^        \        |          P3_COXA = (-X0_COXA, -Y_COXA, H)
 *           /          |         \       |          P4_COXA = ( X0_COXA,  Y_COXA, H)
 *          /           |          \      |          P5_COXA = ( X1_COXA,  0,      H)
 *      P2 +            +-->        + P5   2Y0       P6_COXA = ( X0_COXA, -Y_COXA, H)
 *          \            x         /      |
 *           \                    /       |
 *            \                  /        |
 *             \                /         |
 *           P3 +--------------+ P6       v
 *              <-------- 2X0 ------->
 *
 *
 */
   
  const static float X0                =  32;
  
/**
 * 
 */
class RobotShape {
  public:
    static constexpr float X0                =  32;
    static constexpr float X1                =  46;
    static constexpr float Y0                =  50;
    //static constexpr float Z0                = -15.75;
    static constexpr float DEFAULT_BODY_LIFT = -25; //OJO: -25

    static  constexpr float L_COXA           = 22.75;
    static  constexpr float L_FEMUR          = 55.0;
    static  constexpr float L_TIBIA          = 70.0;
};

#endif
