#ifndef SPIDER0_COM_H
#define SPIDER0_COM_H

#include <SPI.h>
#include "globals.h"
#include "orders.h"
#include "controller.h"
#include "RF24.h"
#include "ESP8266.h"

namespace SPIDER {
  /**
   * 
   */
  void updateService();

  
  /**
   * 
   */
  class SpiderCom {
    private:
      static const int IN_DATA_SIZE  = 32;
      static const int OUT_DATA_SIZE = 32;
      
      const unsigned long _AUTO_SLEEP_OVERTIME = 10000;
      const unsigned long _esp8266Port         = 65535;
      const unsigned int  _LED_BLINK_CYCLE     = 20;
      const int           _PINS[8]             = { 20, 21, A0, A1, 15, 14, 2, 3};

      volatile byte       _blockedOrder        = 0;

      
      RobotController _controller;
      unsigned long   _lastBlockedOrderTime   = 0;
      unsigned long   _ledCounter             = 0;
      OrderSource     _orderSource            = OrderSource::FROM_NONE;
      OrderState      _orderState             = OrderState::EXECUTE_NONE;
      byte            _crawlParameters       [3];
      byte            _changeHeightParameters[1];
      byte            _moveBodyParameters    [3];
      byte            _rotateBodyParameters  [3];
      byte            _twistBodyParameters   [6];
      bool            _communicationEnable     = false;
      int             _ledState               = 0;

      //SERIAL
      byte _serialInData[IN_DATA_SIZE];
      byte _serialInDataCounter = 0;

      // WIFI
      ESP8266 _esp8266          = ESP8266(Serial2, 115200);
      String  _esp8266SSID      = "FHR";
      String  _esp8266PWD       = "hexapodo";
      byte    _esp8266CHL       = 1;
      byte    _esp8266ClientID;
      byte    _esp8266InData[IN_DATA_SIZE];
      bool    _esp8266Available = false;

      //RF24
      RF24 _rf24           = RF24(9, 53);
      byte _rf24Address[6] = { 'F', 'N', 'K', '2', '9' };
      byte _rf24Channel    = 125;
      byte _rf24InData[IN_DATA_SIZE];
      bool _rf24Available  = false;
      

      /*********************************************************
       *                Metodos privados
       *********************************************************/
      void       _checkBlockedOrder();
      void       _handleOrder(byte data[], OrderSource orderSource);
      RobotState _getRobotBootState();
      void       _setRobotBootState (RobotState state);
      void       _saveRobotBootState(RobotState state);
      void       _startESP8266();
      void       _startPins();
      void       _startRF24();
      void       _startSerial();
      void       _startStateLED();
      void       _updateAutoSleep();
      void       _updateBlockedOrder();
      void       _updateESP8266();
      void       _updateRF24();
      void       _updateSerial();
      void       _updateStateLED();

      // Inline
      float _getSupplyVoltage()  {return _controller.getRobot().getPower().getVoltage();}
      void  _setStateLED(bool x) {digitalWrite(STATE_LED_PIN, x);}



    public:
      SpiderCom();

      void init            (bool   x = true);
      void setWiFi         (String name, String password);
      void setWiFiChannel  (byte   canal);
      void setRemote       (byte   b0,   byte b1, byte b2, byte b3, byte b4);
      void setRemoteChannel(byte   canal);
      void updateCommunication();
      void updateOrder();

      //Inline
      RobotController& getController()         {return _controller;}
      bool             isCommunicationEnable() {return _communicationEnable;}
  };
}

#endif
