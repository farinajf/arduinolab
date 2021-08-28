#include "power.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Power::Power() {}


  /****************************************************************
   * void init(int adcReference, float samplingProportion, bool powerGroupAutoSwitch)
   * 
   ****************************************************************/
  void Power::init(int adcReference, float samplingProportion, bool powerGroupAutoSwitch) {
    _adcReference         = adcReference;
    _samplingProportion   = samplingProportion;
    _powerGroupAutoSwitch = powerGroupAutoSwitch;
    
    analogReference(_adcReference);

    for (int i = 0; i < _SAMPLING_SIZE; i++) _samplingData[i] = 0;

    pinMode(POWER_GROUP1_PIN, OUTPUT);
    pinMode(POWER_GROUP2_PIN, OUTPUT);
    pinMode(POWER_GROUP3_PIN, OUTPUT);
  }


  /****************************************************************
   * void update()
   * 
   ****************************************************************/
  void Power::update() {
    this -> _sampling();

    if (_powerGroupAutoSwitch == false) return;

    if      (_voltage > _POWER_GROUP_ON_VOLTAGE)  _poweGroupState = true;
    else if (_voltage < _POWER_GROUP_OFF_VOLTAGE) _poweGroupState = false;

    if (++_updateCounter < _POWER_GROUP_BOOT_INTERVAL) return;

    _updateCounter = 0;

    if (_poweGroupState == true)
    {
      if (_powerGroup1State == false)
      {
        this -> _setPowerGroupState(1, true);
        return;
      }
      if (_powerGroup2State == false)
      {
        this -> _setPowerGroupState(2, true);
        return;
      }
      if (_powerGroup3State == false)
      {
        this -> _setPowerGroupState(3, true);
        return;
      }
    }
    else
    {
      if (_powerGroup1State == true)
      {
        this -> _setPowerGroupState(1, false);
        return;
      }
      if (_powerGroup2State == true)
      {
        this -> _setPowerGroupState(2, false);
        return;
      }
      if (_powerGroup3State == true)
      {
        this -> _setPowerGroupState(3, false);
        return;
      }
    }
  }


  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

  /****************************************************************
   * void _sampling()
   * 
   ****************************************************************/
  void Power::_sampling() {
    float averagePeakVoltage = 0;
    float peakVoltage        = 0;
    float voltage            = 0;

    //0.- Reset
    if (_samplingDataCounter     >= _SAMPLING_SIZE)      _samplingDataCounter     = 0;
    if (_samplingPeakDataCounter >= _SAMPLING_PEAK_SIZE) _samplingPeakDataCounter = 0;

    //1.- Obtener el voltaje
    switch (_adcReference)
    {
      case EXTERNAL:
          voltage = analogRead(POWER_SAMPLING_PIN) * (2.5 * (32 / (32 + 6.2))) / 1023 / _samplingProportion;
          break;

      default:
          voltage = analogRead(POWER_SAMPLING_PIN) * 5.0 / 1023 / _samplingProportion;
          break;
    }

    //2.- Actualizar vector de voltaje
    _samplingData[_samplingDataCounter++] = voltage;

    //3.- Obtener el valor de pico
    for (int i = 0; i < _SAMPLING_SIZE; i++)
    {
      if (peakVoltage < _samplingData[i]) peakVoltage = _samplingData[i];
    }

    //4.- Actualizar el vector de picos de voltaje
    _samplingPeakData[_samplingPeakDataCounter++] = peakVoltage;

    //5.- Calcular el promedio de los picos
    for (int i = 0; i < _SAMPLING_PEAK_SIZE; i++)
    {
      averagePeakVoltage += _samplingPeakData[i];
    }
    averagePeakVoltage /= _SAMPLING_PEAK_SIZE;

    //6.- Actualizar el atributo voltaje
    _voltage = averagePeakVoltage;
  }

  /****************************************************************
   * void _setPowerGroupState(int group, bool state)
   * 
   ****************************************************************/
  void Power::_setPowerGroupState(int group, bool state) {
    switch (group)
    {
      case 1:
          digitalWrite(POWER_GROUP1_PIN, state);
          _powerGroup1State = state;
          break;
          
      case 2:
          digitalWrite(POWER_GROUP2_PIN, state);
          _powerGroup2State = state;
          break;
          
      case 3:
          digitalWrite(POWER_GROUP3_PIN, state);
          _powerGroup3State = state;
          break;
    }
  }
}
