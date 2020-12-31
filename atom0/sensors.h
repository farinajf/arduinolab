#ifndef SENSORS_H
#define SENSORS_H

#include "infrarrojos.h"
#include "ultrasonic.h"

namespace ATOM0 {
  /**
   * 
   */
  class Sensors {
    private:
      IR _ir;

    public:
      Sensors() {}

      void init();
      void checkIRObstacle();
      void distanceCalculate() {ultrasonicCalculate();};

      double getDistance()      const;
      bool   isAlertColission() const;
      bool   isDistanceOK()     const;
      bool   isIRRightOK()      const;
      bool   isIRLeftOK()       const;
      bool   isIROK()           const;
  };
}

#endif
