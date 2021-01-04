#ifndef SPIDER0_H
#define SPIDER0_H

#include "receptorIR.h"
#include "sensors.h"
#include "SpiderMotor.h"

namespace SPIDER {
  enum DriveMode_t {
    DRIVE_GROUP_LEG_1, //R-1, L-2, R-3
    DRIVE_GROUP_LEG_2, //L_1, R-2, L-3
    DRIVE_NONE
  };

  class Spider0 {
    private:
      const SpiderMotor _motor;
      const ReceptorIR  _ir;
      const Sensors     _sensors;
      DriveMode_t       _driveMode = DRIVE_GROUP_LEG_1;

      void _up()     const;
      void _down()   const;
      void _left()   const;
      void _right()  const;
      void _setDriveMode();
      void _drive();
      void _reposo() const;

    public:
      Spider0();

      void init();
      void drive();
  };
}
#endif
