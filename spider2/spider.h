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

      void changeBodyHeight(float h);
      void crawl           (float x, float y, float angulo);
      void crawlForward();
      void crawlBackward();
      void crawlLeft();
      void crawlRight();
      void legMoveToRelatively(int    leg,  float x, float y, float z);
      void moveBody           (float  x,    float y, float z);
      void rotateBody         (float  x,    float y, float z);
      void setActionGroup     (int    group);
      void setActionSpeed     (float  speed);
      void setWiFi            (String name, String password);
      void setWiFiChannel     (byte   canal);
      void setRemote          (byte   b0,   byte b1, byte b2, byte b3, byte b4);
      void setRemoteChannel   (byte   canal);
      void turnLeft();
      void turnRight();
      void twistBody(float xMove, float yMove, float zMove, float xRotate, float yRotate, float zRotate);
      void update();

      void activeMode();
      void sleepMode();
      void switchMode();
      
      
      //INLINE
      float            getAltura()          {return _communication.getController().getAltura();}
      RobotController& getRobotController() {return _communication.getController();}
  };
}

#endif
