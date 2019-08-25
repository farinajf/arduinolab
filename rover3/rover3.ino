/**
 * Robot-CAR
 */
#include "distanceSensor.h"
#include "carDriver.h"
#include "carRobot.h"

#define PIN_TRIG_SONAR_FRONT 12
#define PIN_ECHO_SONAR_FRONT 11
#define PIN_TRIG_SONAR_RIGHT  6
#define PIN_ECHO_SONAR_RIGHT  7
#define PIN_TRIG_SONAR_LEFT   9
#define PIN_ECHO_SONAR_LEFT   8

#define PIN_IN1_A      A5 //Right
#define PIN_IN2_A      A4 //Right

#define PIN_IN1_B      A2 //Left
#define PIN_IN2_B      A3 //Left

const unsigned int minDistance  =   25;
const unsigned int minDistanceR =   25;
const unsigned int minDistanceL =   25;
const unsigned int maxDistance  =  200;

ROVER3::DistanceSensor sonar (PIN_ECHO_SONAR_FRONT, PIN_TRIG_SONAR_FRONT, minDistance,  maxDistance);
ROVER3::DistanceSensor sonarR(PIN_ECHO_SONAR_RIGHT, PIN_TRIG_SONAR_RIGHT, minDistanceR, maxDistance);
ROVER3::DistanceSensor sonarL(PIN_ECHO_SONAR_LEFT,  PIN_TRIG_SONAR_LEFT,  minDistanceL, maxDistance);

ROVER3::L298NEngine md    (PIN_IN1_A, PIN_IN2_A);
ROVER3::L298NEngine mi    (PIN_IN1_B, PIN_IN2_B);
ROVER3::CarDriver   driver(md,        mi);
ROVER3::CarRobot    robot (driver,    sonar,   sonarL,  sonarR);

/**
 * 
 */
void setup() {
  md.init();
  mi.init();
  driver.init();
  robot.init();
}

/**
 * 
 */
void loop() {
  ROVER3::state_t state;

  do
  {
    state = robot.mover();

    switch (state)
    {
      case ROVER3::TURNING: delay(50); break;
      default:              delay(5);  break;
    }
  }
  while (true == true);
}
