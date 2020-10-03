#ifndef SPIDER0_H
#define SPIDER0_H

#include "spiderMotor.h"

namespace SPIDER {
  class Spider0 {
    private:
      const SpiderMotor _motor;

    public:
      Spider0();

      void init();

      void move() const;
      void move(const int pataIzqDelanteraAngles[3], const int pataIzqMediaAngles[3], const int pataIzqTraseraAngles[3], const int pataDerDelanteraAngles[3], const int pataDerMediaAngles[3], const int pataDerTraseraAngles[3]) const;
  };
}
#endif
