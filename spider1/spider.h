#ifndef SPIDER0_H
#define SPIDER0_H

#include "globals.h"
#include "spiderCom.h"

namespace SPIDER {
  /**
   * 
   */
  class Spider0 {
    private:
      SpiderCom _communication;

      /*********************************************************
       *                Metodos privados
       *********************************************************/


    public:
      Spider0();

      void init  (bool x = false);
      void update();

  };
}

#endif
