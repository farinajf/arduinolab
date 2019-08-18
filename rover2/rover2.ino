/*

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

#define PIN_EN_A       10
#define PIN_IN1_A      A5
#define PIN_IN2_A      A4
#define PIN_EN_B        5
#define PIN_IN1_B      A2
#define PIN_IN2_B      A3

const unsigned int minDistance  =   20;
const unsigned int minDistanceR =   15;
const unsigned int minDistanceL =   15;
const unsigned int maxDistance  =  200;
const short        speedA       =  130; //Left
const short        speedB       =  150; //Right
const short        speedTurn    = 1000; //Giro
const int          delayTurnMax =  200; // Milisegundos de giro

ROVER2::DistanceSensor     sonar   (PIN_ECHO_SONAR_FRONT, PIN_TRIG_SONAR_FRONT, minDistance,  maxDistance);
ROVER2::DistanceSensor     sonarR  (PIN_ECHO_SONAR_RIGHT, PIN_TRIG_SONAR_RIGHT, minDistanceR, maxDistance);
ROVER2::DistanceSensor     sonarL  (PIN_ECHO_SONAR_LEFT,  PIN_TRIG_SONAR_LEFT,  minDistanceL, maxDistance);
ROVER2::DetectorObstaculos detector(sonar,                sonarL,               sonarR);
ROVER2::CarDriver          driver  (PIN_EN_A,             PIN_IN1_A,            PIN_IN2_A,    speedA,
                                    PIN_EN_B,             PIN_IN1_B,            PIN_IN2_B,    speedB,      speedTurn);
ROVER2::CarRobot           robot   (driver,               detector);

/**
 * Establece un retardo aleatorio.
 */
void _randomDelay() {
  int x = random(50, delayTurnMax);

  Serial.print("Random: "); Serial.println(x);
  
  delay(x);
}

/**
 * 
 */
void setup() {
  randomSeed(analogRead(0));
  robot.init();
}

/**
 * 
 */
void loop() {
    ROVER2::state_t state = robot.run();
    
    switch (state)
    {
      case ROVER2::TURNING: _randomDelay(); break;
      default:              delay(50);      break;
    }
}
