#ifndef SPIDER0_H
#define SPIDER0_H

#include <FlexiTimer2.h>
#include "sensors.h"
#include "robotAction.h"

namespace SPIDER {
  /**
   * 
   */
  class Spider0 {
    private:
      const RobotAction _robot;
      const Sensors     _sensors;

      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _updateOrder();

    public:
      Spider0();

      void init();
      void changeBodyHeight(float h);
      void crawlForward();
      void update();

      RobotAction* getRobotAction() {return &_robot;}
  };
}

#endif
