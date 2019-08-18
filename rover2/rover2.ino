/*

*/
#include "distanceSensor.h"
#include "carDriver.h"
#include "carRobot.h"

const short pinTrigSonar  = 12;
const short pinEchoSonar  = 11;
const short pinTrigSonarR =  6;
const short pinEchoSonarR =  7;
const short pinTrigSonarL =  9;
const short pinEchoSonarL =  8;

const unsigned int minDistance =  25;
const unsigned int maxDistance = 200;

const short pinEN_A  =  10;
const short pinIN1_A =  A5;
const short pinIN2_A =  A4;
const short pinEN_B  =   5;
const short pinIN1_B =  A2;
const short pinIN2_B =  A3;
const short speedA   = 130; //Left
const short speedB   = 150; //Right

const int runtime    = 300;

ROVER2::DistanceSensor     sonar   (maxDistance, pinEchoSonar,  pinTrigSonar);
ROVER2::DistanceSensor     sonarR  (maxDistance, pinEchoSonarR, pinTrigSonarR);
ROVER2::DistanceSensor     sonarL  (maxDistance, pinEchoSonarL, pinTrigSonarL);
ROVER2::CarDriver          driver  (pinEN_A, pinIN1_A, pinIN2_A, speedA, pinEN_B, pinIN1_B, pinIN2_B, speedB);
ROVER2::DetectorObstaculos detector(sonar, sonarL, sonarR, minDistance, maxDistance);
ROVER2::CarRobot           robot   (driver, detector, runtime);

void setup() {
    robot.init();
}

void loop() {
    ROVER2::state_t state = robot.run();
    
    switch (state)
    {
      case ROVER2::TURNING: delay(50); break;
      default:              delay(50); break;
    }
}
