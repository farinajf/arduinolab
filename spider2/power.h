#ifndef POWER_H
#define POWER_H

#include "globals.h"

namespace SPIDER {
  /**
   * 
   */
  class Power {
    private:
      const static int   _SAMPLING_SIZE             = 25;
      const static int   _SAMPLING_PEAK_SIZE        = 25;
      const        float _POWER_GROUP_ON_VOLTAGE    = 6.5;
      const        float _POWER_GROUP_OFF_VOLTAGE   = 5.5;
      const        int   _POWER_GROUP_BOOT_INTERVAL = 5;

      float _samplingPeakData[_SAMPLING_PEAK_SIZE];
      float _samplingData    [_SAMPLING_SIZE];
      float _samplingProportion;
      bool  _powerGroupAutoSwitch;
      bool  _powerGroup1State        = false;
      bool  _powerGroup2State        = false;
      bool  _powerGroup3State        = false;
      int   _samplingPeakDataCounter = 0;
      int   _samplingDataCounter     = 0;
      int   _adcReference;
      int   _updateCounter           = 0;

      volatile float _voltage;
      volatile bool  _poweGroupState;


      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void _sampling();
      void _setPowerGroupState(int group, bool state);

    public:
      Power();

      void init(int adcReference, float samplingProportion, bool powerGroupAutoSwitch);
      void update();


      // INLINE
      float getVoltage()             {return _voltage;}
      bool  isPowerGroupAutoSwitch() {return _powerGroupAutoSwitch;}
      bool  isPowerGroupState()      {return _poweGroupState;}
  };
}

#endif
