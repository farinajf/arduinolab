#ifndef SENSORS_H
#define SENSORS_H

#include "infrarrojos.h"
#include "trackingline.h"
#include "ultrasonic.h"

/**
 * TODO
 * 
 * Sensors: HC-SR04 + Infrarrojos
 */
namespace KM0CAR {
  class Sensors {
    private:
      TrakingLine _tl;
      Ultrasonic  _sonar;
      IR          _ir;

    public:
      Sensors() {}

      double getDistanceForward()     const {return _sonar.getDistanceForward();}
      double getDistanceMiddleRight() const {return _sonar.getDistanceMiddleRight();}
      double getDistanceMiddleLeft()  const {return _sonar.getDistanceMiddleLeft();}
      double getDistanceRight()       const {return _sonar.getDistanceRight();}
      double getDistanceLeft()        const {return _sonar.getDistanceLeft();}

      void init();
      void checkIRObstacle();
      void forwardDistance();
      void lateralDistance();

      bool isAlertColission()    const;
      bool isDistanceRightOK()   const;
      bool isDistanceLeftOK()    const;
      bool isDistanceForwardOK() const;
      bool isIROK()              const;
      bool isIRRightOK()         const;
      bool isIRLeftOK()          const;
      bool isLateralOK()         const;
  };
}

#endif
