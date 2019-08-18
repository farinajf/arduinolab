/*

*/
#include "distanceSensor.h"
#include "carDriver.h"
#include "carRobot.h"

#define PIN_TrigSonar  12
#define PIN_EchoSonar  11

#define PIN_TrigSonarR  6
#define PIN_EchoSonarR  7

#define PIN_TrigSonarL  9
#define PIN_EchoSonarL  8

#define PIN_EN_A       10
#define PIN_IN1_A      A5
#define PIN_IN2_A      A4
#define PIN_EN_B        5
#define PIN_IN1_B      A2
#define PIN_IN2_B      A3

const unsigned int minDistance  =  25;
const unsigned int maxDistance  = 200;
const short        speedA       = 130; //Left
const short        speedB       = 150; //Right
const short        speedTurn    = 300; //Giro
const int          delayTurnMax = 200;
const int          runtime      = 180;

ROVER2::DistanceSensor     sonar   (maxDistance, PIN_EchoSonar,  PIN_TrigSonar);
ROVER2::DistanceSensor     sonarR  (maxDistance, PIN_EchoSonarR, PIN_TrigSonarR);
ROVER2::DistanceSensor     sonarL  (maxDistance, PIN_EchoSonarL, PIN_TrigSonarL);
ROVER2::CarDriver          driver  (PIN_EN_A,    PIN_IN1_A,      PIN_IN2_A, speedA,
                                    PIN_EN_B,    PIN_IN1_B,      PIN_IN2_B, speedB,
                                    speedTurn);
ROVER2::DetectorObstaculos detector(sonar,       sonarL,         sonarR,    minDistance, maxDistance);
ROVER2::CarRobot           robot   (driver,      detector,       runtime,   delayTurnMax);

void setup() {
    robot.init();
}

void loop() {
    ROVER2::state_t state = robot.run();
    
    switch (state)
    {
      case ROVER2::TURNING: delay( 1); break;
      default:              delay(50); break;
    }
}
