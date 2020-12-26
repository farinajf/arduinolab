#ifndef SPIDER0_H
#define SPIDER0_H

#include "receptorIR.h"
#include "spiderMotor.h"

namespace SPIDER {
  enum DriveMode_t {
    DRIVE_MODE_LEG_MOVE_1,
    DRIVE_MODE_LEG_MOVE_2,
    DRIVE_MODE_LEG_MOVE_3,
    DRIVE_MODE_LEG_MOVE_4,
    DRIVE_MODE_LEG_MOVE_5,
    DRIVE_MODE_LEG_MOVE_6,
    DRIVE_MODE_NONE
  };
  
  class Spider0 {
    private:
      const SpiderMotor _motor;
      const ReceptorIR  _ir;
      DriveMode_t       _driveMode = DRIVE_MODE_NONE;

      void _setDriveMode();
      void _up();
      void _down();
      void _left();
      void _right();

    public:
      Spider0();

      void setDriveMode(DriveMode_t x) {_driveMode = x;}
      
      void init();
      void reposo() const;
      void drive();
  };
}
#endif
