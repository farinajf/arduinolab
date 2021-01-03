#ifndef SPIDER0_H
#define SPIDER0_H

#include "receptorIR.h"
#include "sensors.h"
#include "SpiderMotor.h"

namespace SPIDER {
  enum DriveMode_t {
    DRIVE_LEG_RIGHT_1,
    DRIVE_LEG_RIGHT_2,
    DRIVE_LEG_RIGHT_3,
    DRIVE_LEG_LEFT_1,
    DRIVE_LEG_LEFT_2,
    DRIVE_LEG_LEFT_3,
    DRIVE_NONE
  };

  class Spider0 {
    private:
      const SpiderMotor _motor;
      const ReceptorIR  _ir;
      const Sensors     _sensors;
      DriveMode_t       _driveMode = DRIVE_LEG_LEFT_1;

      SpiderLeg_t _getLeg() const;
      void        _up()     const;
      void        _down()   const;
      void        _left()   const;
      void        _right()  const;
      void        _setDriveMode();
      void        _drive();
      void        _reposo() const;

    public:
      Spider0();

      void init();
      void drive();
  };
}
#endif
