#ifndef SPIDER0_H
#define SPIDER0_H

#include "receptorIR.h"
#include "sensors.h"
#include "SpiderMotor.h"

namespace SPIDER {
  enum LegGroup_t {
    GROUP_LEG_1, //R-1, L-2, R-3
    GROUP_LEG_2, //L_1, R-2, L-3
    NONE
  };

  class Spider0 {
    private:
      const SpiderMotor _motor;
      const ReceptorIR  _ir;
      const Sensors     _sensors;

      void _up   (LegGroup_t group, const short deltaCoxa, const short deltaFemur, const short deltaTibia) const;
      void _drive();
      void _reposo()   const;
      void _showInfo() const;

    public:
      Spider0();

      void init();
      void drive();
  };
}
#endif
