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
    if (_communication.isCommunicationEnable() == false) _communication.getController().changeBodyHeight(h);
  }

  /****************************************************************
   * void crawl(float x, float y, float angulo)
   * 
   ****************************************************************/
  void Spider0::crawl(float x, float y, float angulo) {
    if (_communication.isCommunicationEnable() == false) _communication.getController().crawl(x, y, angulo);
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
    if (_communication.isCommunicationEnable() == false) _communication.getController().crawlForward();
  }

  void Spider0::crawlBackward() {
    if (_communication.isCommunicationEnable() == false) _communication.getController().crawlBackward();
  }

  void Spider0::crawlLeft() {
    if (_communication.isCommunicationEnable() == false) _communication.getController().crawlLeft();
  }

  void Spider0::crawlRight() {
    if (_communication.isCommunicationEnable() == false) _communication.getController().crawlRight();
  }

  void Spider0::turnLeft() {
    if (_communication.isCommunicationEnable() == false) _communication.getController().turnLeft();
  }

  void Spider0::turnRight() {
    if (_communication.isCommunicationEnable() == false) _communication.getController().turnRight();
  }

  /****************************************************************
   * void legMoveToRelatively(int leg, float x, float y, float z)
   * 
   ****************************************************************/
  void Spider0::legMoveToRelatively(int leg, float x, float y, float z) {
    if (_communication.isCommunicationEnable() == false) _communication.getController().moveLeg(leg, Point(x, y, z));
  }

  /****************************************************************
   * setActionGroup(int x)
   * 
   ****************************************************************/
  void Spider0::setActionGroup(int x) {
    if (_communication.isCommunicationEnable() == false) _communication.getController().setPasosCiclo(x);
  }

  /****************************************************************
   * setActionSpeed(float x)
   * 
   ****************************************************************/
  void Spider0::setActionSpeed(float x) {
    if (_communication.isCommunicationEnable() == false) _communication.getController().setSpeed(x / 100);
  }

  /****************************************************************
   * void moveBody(float x, float y, float z)
   * 
   ****************************************************************/
  void Spider0::moveBody(float x, float y, float z) {
    //if (_communication.isCommunicationEnable() == false) _communication.getController().moveBody(x, y, z); //TODO
  }

  /****************************************************************
   * void rotateBody(float x, float y, float z)
   * 
   ****************************************************************/
  void Spider0::rotateBody(float x, float y, float z) {
    //if (_communication.isCommunicationEnable() == false) _communication.getController().rotateBody(x, y, z); //TODO
  }

  /****************************************************************
   * void twistBody(float xMove, float yMove, float zMove, float xRotate, float yRotate, float zRotate)
   * 
   ****************************************************************/
  void Spider0::twistBody(float xMove, float yMove, float zMove, float xRotate, float yRotate, float zRotate) {
    if (_communication.isCommunicationEnable() == false) _communication.getController().twistBody(Point(xMove,   yMove,   zMove),
                                                                                                  Point(xRotate, yRotate, zRotate));
  }








  /****************************************************************
   * void activeMode()
   ****************************************************************/
  void Spider0::activeMode() {
    if (_communication.isCommunicationEnable() == false) _communication.getController().setActiveMode();
  }

  /****************************************************************
   * void sleepMode()
   ****************************************************************/
  void Spider0::sleepMode() {
    if (_communication.isCommunicationEnable() == false) _communication.getController().setSleepMode();
  }

  /****************************************************************
   * void switchMode()
   ****************************************************************/
  void Spider0::switchMode()  {
    if (_communication.isCommunicationEnable() == false) _communication.getController().switchMode();
  }


  /****************************************************************
   * void update()
   ****************************************************************/
  void Spider0::update() {
    if (_communication.isCommunicationEnable() == true) _communication.updateOrder();
  }

  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/


}
