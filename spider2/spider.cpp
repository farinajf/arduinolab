#include "spider.h"

namespace SPIDER {

  Spider0* spider = NULL;

  /****************************************************************
   * void updateService()
   * 
   ****************************************************************/
  void updateService() {
    sei();

    if (spider != NULL)
    {
      spider -> getRobotAction() -> update();
    }
  }

  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Spider0::Spider0() : _sensors(), _robot() {}
  
  /****************************************************************
   * void init()
   ****************************************************************/
  void Spider0::init() {
    //0.- Init
    spider = this;
    
    //1.- Sensors
    _sensors.init();

    //2.- Robot
    _robot.init();

    //3.- Planifica rutina de servicio
    FlexiTimer2::set(20, updateService);
    FlexiTimer2::start();
  }

  /****************************************************************
   * void changeBodyHeight(float h)
   ****************************************************************/
  void Spider0::changeBodyHeight(float h) {
    _robot.changeBodyHeight(h);
  }

  /****************************************************************
   * void crawlForward()
   ****************************************************************/
  void Spider0::crawlForward() {
    _robot.crawlForward();
  }

  /****************************************************************
   * void update()
   ****************************************************************/
  void Spider0::update() {
    //1.- Get information from sensors
    _sensors.calculate();

    //2.- Check battery
    if (_sensors.isBatteryOK() == true) _updateOrder();
    else delay(10000);
  }



  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * void _updateOrder()
   * 
   ****************************************************************/
  void Spider0::_updateOrder() {
    //TODO
  }
}
