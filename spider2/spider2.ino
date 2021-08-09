/**
 * SPIDER 0
 */
#include "spider.h"

SPIDER::Spider0 _spider;

/**
 * void setup()
 */
void setup() {
  Serial.begin(9600);

  _spider.init();
}

/**
 * 
 */
void _calibrate() {
  SPIDER::ServoDriver * driver = _spider.getRobotAction() -> getRobot() -> getLeg1().getDriver();
    
  _spider.getRobotAction() -> getRobot() -> getLeg1().getCoxa().rotateToDirectly (driver,  135);
  _spider.getRobotAction() -> getRobot() -> getLeg1().getFemur().rotateToDirectly(driver,    0);
  _spider.getRobotAction() -> getRobot() -> getLeg1().getTibia().rotateToDirectly(driver,  180);



//  SPIDER::ServoDriver * driver = _spider.getRobotAction() -> getRobot() -> getLeg3().getDriver();
//    
//  _spider.getRobotAction() -> getRobot() -> getLeg3().getCoxa().rotateToDirectly (driver, -135);
//  _spider.getRobotAction() -> getRobot() -> getLeg3().getFemur().rotateToDirectly(driver,    0);
//  _spider.getRobotAction() -> getRobot() -> getLeg3().getTibia().rotateToDirectly(driver,  180);

//  SPIDER::ServoDriver * driver = _spider.getRobotAction() -> getRobot() -> getLeg4().getDriver();
//    
//  _spider.getRobotAction() -> getRobot() -> getLeg4().getCoxa().rotateToDirectly (driver,  45);
//  _spider.getRobotAction() -> getRobot() -> getLeg4().getFemur().rotateToDirectly(driver,   0);
//  _spider.getRobotAction() -> getRobot() -> getLeg4().getTibia().rotateToDirectly(driver, 180);

//  SPIDER::ServoDriver * driver = _spider.getRobotAction() -> getRobot() -> getLeg5().getDriver();
//  
//  _spider.getRobotAction() -> getRobot() -> getLeg5().getCoxa().rotateToDirectly (driver,   0);
//  _spider.getRobotAction() -> getRobot() -> getLeg5().getFemur().rotateToDirectly(driver,   0);
//  _spider.getRobotAction() -> getRobot() -> getLeg5().getTibia().rotateToDirectly(driver, 180);

//  SPIDER::ServoDriver * driver = _spider.getRobotAction() -> getRobot() -> getLeg6().getDriver();
//  
//  _spider.getRobotAction() -> getRobot() -> getLeg6().getCoxa().rotateToDirectly (driver, -45);
//  _spider.getRobotAction() -> getRobot() -> getLeg6().getFemur().rotateToDirectly(driver,   0);
//  _spider.getRobotAction() -> getRobot() -> getLeg6().getTibia().rotateToDirectly(driver, 180);
}

/**
 * void _changeBodyHeight()
 */
void _changeBodyHeight() {
  _spider.changeBodyHeight( -40);
  _spider.changeBodyHeight(-100);
}

/**
 * void loop()
 */
void loop() {
  _spider.update();

  _changeBodyHeight();

  //_spider.crawlForward();
}
