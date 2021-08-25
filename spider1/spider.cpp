#include "spider.h"

namespace SPIDER {

  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Spider0::Spider0() {}
  
  /****************************************************************
   * void init(bool x)
   ****************************************************************/
  void Spider0::init(bool x) {
    _communication.init(x);
  }

  /****************************************************************
   * void changeBodyHeight(float h)
   ****************************************************************/
  void Spider0::changeBodyHeight(float h) {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().changeBodyHeight(h);
  }

  /****************************************************************
   * void crawl(float x, float y, float angulo)
   * 
   ****************************************************************/
  void Spider0::crawl(float x, float y, float angulo) {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().crawlForward();
  }

  /****************************************************************
   * void crawlForward()
   * void crawlBackward()
   * void crawlLeft()
   * void crawlRight()
   * void turnLeft()
   * void turnRight()
   * 
   ****************************************************************/
  void Spider0::crawlForward() {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().crawlForward();
  }

  void Spider0::crawlBackward() {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().crawlBackward();
  }

  void Spider0::crawlLeft() {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().crawlLeft();
  }

  void Spider0::crawlRight() {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().crawlRight();
  }

  void Spider0::turnLeft() {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().turnLeft();
  }

  void Spider0::turnRight() {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().turnRight();
  }

  /****************************************************************
   * void legMoveToRelatively(int leg, float x, float y, float z)
   * 
   ****************************************************************/
  void Spider0::legMoveToRelatively(int leg, float x, float y, float z) {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().legMoveToRelatively(leg, Point(x, y, z));
  }

  /****************************************************************
   * setActionGroup(int x)
   * 
   ****************************************************************/
  void Spider0::setActionGroup(int x) {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().setActionGroup(x);
  }

  /****************************************************************
   * setActionSpeed(float x)
   * 
   ****************************************************************/
  void Spider0::setActionSpeed(float x) {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().setSpeedMultiple(x / 100);
  }

  /****************************************************************
   * void moveBody(float x, float y, float z)
   * 
   ****************************************************************/
  void Spider0::moveBody(float x, float y, float z) {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().moveBody(x, y, z);
  }

  /****************************************************************
   * void rotateBody(float x, float y, float z)
   * 
   ****************************************************************/
  void Spider0::rotateBody(float x, float y, float z) {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().rotateBody(x, y, z);
  }

  /****************************************************************
   * void twistBody(float xMove, float yMove, float zMove, float xRotate, float yRotate, float zRotate)
   * 
   ****************************************************************/
  void Spider0::twistBody(float xMove, float yMove, float zMove, float xRotate, float yRotate, float zRotate) {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().twistBody(Point(xMove,   yMove,   zMove),
                                                                                                      Point(xRotate, yRotate, zRotate));
  }








  /****************************************************************
   * void activeMode()
   ****************************************************************/
  void Spider0::activeMode() {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().activeMode();
  }

  /****************************************************************
   * void sleepMode()
   ****************************************************************/
  void Spider0::sleepMode() {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().sleepMode();
  }

  /****************************************************************
   * void switchMode()
   ****************************************************************/
  void Spider0::switchMode()  {
    if (_communication.isCommunicationAvailable() == false) _communication.getRobotAction().switchMode();
  }


  /****************************************************************
   * void update()
   ****************************************************************/
  void Spider0::update() {
    if (_communication.isCommunicationAvailable() == true) _communication.updateOrder();
  }

  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/


}
