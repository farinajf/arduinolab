#include "spiderCom.h"

namespace SPIDER {

  SpiderCom* communication = NULL;

  /****************************************************************
   * void updateService()
   * 
   ****************************************************************/
  void updateService() {
    sei();

    if (communication != NULL)
    {
      communication -> getRobotAction().getRobot().update();
      communication -> updateCommunication();
    }
  }

  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  SpiderCom::SpiderCom() {}
  
  /****************************************************************
   * void init(bool x)
   * 
   ****************************************************************/
  void SpiderCom::init(bool x = true) {
    //0.- Init
    communication = this;

    //1.-
    _communicationAvailable = x;

    //2.-
    this -> _startStateLED();

    //3.-
    _robotAction.init();
    
    //4.- Planifica rutina de servicio
    FlexiTimer2::set(20, updateService);
    FlexiTimer2::start();

    //5.-
    if (_communicationAvailable == true)
    {
      this -> _startPins();
      this -> _startSerial();
      this -> _startRF24();
      this -> _startESP8266();

      this -> _setRobotBootState(this -> _getRobotBootState());
    }

    //6.-
    if (_robotAction.getRobot().getPower().isPowerGroupAutoSwitch()) delay(1000);
  }

  /****************************************************************
   * void updateCommunication()
   * 
   ****************************************************************/
  void SpiderCom::updateCommunication() {
    this -> _updateStateLED();

    if (_communicationAvailable == true)
    {
      this -> _updateSerial();
      this -> _updateRF24();
      this -> _updateESP8266();
      this -> _checkBlockedOrder();
    }
  }


  /****************************************************************
   * void updateOrder()
   * 
   * Se llama desde: Spider0::update()
   * 
   ****************************************************************/
  void SpiderCom::updateOrder() {
    this -> _updateBlockedOrder();
    this -> _updateAutoSleep();
  }


  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/


  /****************************************************************
   * void _checkBlockedOrder()
   * 
   * Envia respuesta: TRANS_START | ORDER_DONE | TRANS_END
   * 
   ****************************************************************/
  void SpiderCom::_checkBlockedOrder() {
    byte outData[OUT_DATA_SIZE];
    byte outDataCounter = 0;
    
    if (_orderState != OrderState::EXECUTE_DONE) return;

    outData[outDataCounter++] = Orders::TRANS_START;
    outData[outDataCounter++] = Orders::ORDER_DONE;
    outData[outDataCounter++] = Orders::TRANS_END;

    if      (_orderSource == OrderSource::FROM_SERIAL)  Serial.write (outData,          outDataCounter);
    else if (_orderSource == OrderSource::FROM_ESP8266) _esp8266.send(_esp8266ClientID, outData, outDataCounter);

    _orderState = OrderState::EXECUTE_NONE;
  }

  
  /****************************************************************
   * RobotState _getRobotBootState()
   * 
   * Lee la ROM para saber el estado del robot
   * 
   ****************************************************************/
  RobotState SpiderCom::_getRobotBootState() {
    byte stateByte = EEPROM.read(EepromAddresses::robotState);

    if      (stateByte == 0) return RobotState::INSTALL;
    else if (stateByte == 1) return RobotState::CALIBRATE;
    else if (stateByte == 2) return RobotState::BOOT;

    return RobotState::INSTALL;
  }


  /****************************************************************
   * void _handleOrder(byte data[], OrderSource orderSource)
   * 
   * Lee la orden recibida por el puerto serie, WIFI, ... y establece
   * el valor de _blockedOrder
   * 
   ****************************************************************/
  void SpiderCom::_handleOrder(byte data[], OrderSource orderSource) {
    byte outData[OUT_DATA_SIZE];
    byte outDataCounter = 0;
    
    if (_blockedOrder != 0) return;

    this -> _orderSource = orderSource;

    outData[outDataCounter++] = Orders::TRANS_START;

    if (data[1] == Orders::REQ_ECHO)                           //  0
    {
      outData[outDataCounter++] = Orders::ECHO;
    }
    else if (data[1] == Orders::REQ_SUPPLY_VOLTAGE)            // 10
    {
      float result = this -> _getSupplyVoltage();

      outData[outDataCounter++] = Orders::SUPPLY_VOLTAGE;
      outData[outDataCounter++] = (int)(result * 100) / 128;
      outData[outDataCounter++] = (int)(result * 100) % 128;
    }
    else if (data[1] == Orders::REQ_CHANGE_IO)                 // 20
    {
      digitalWrite(_PINS[data[2]], data[3]);
      
      outData[outDataCounter++] = Orders::ORDER_DONE;
    }
    else if (data[1] == Orders::REQ_MOVE_LEG)                  // 30
    {
      _robotAction.legMoveToRelativelyDirectly(data[2], Point(data[3] - 64, data[4] - 64, data[5] - 64));
      
      outData[outDataCounter++] = Orders::ORDER_DONE;
    }
    else if (data[1] == Orders::REQ_CALIBRATE)                 // 32
    {
      _robotAction.getRobot().calibrateServos();
      
      outData[outDataCounter++] = Orders::ORDER_DONE;
    }
    else if (data[1] >= 64 && data[1] <= 108)                  // Simple action
    {
      _blockedOrder             = data[1];
      
      outData[outDataCounter++] = Orders::ORDER_START;
    }
    else if (data[1] == Orders::REQ_CRAWL)                     //110
    {
      _blockedOrder             = data[1];
      _crawlParameters[0]       = data[2];
      _crawlParameters[1]       = data[3];
      _crawlParameters[2]       = data[4];
      
      outData[outDataCounter++] = Orders::ORDER_START;
    }
    else if (data[1] == Orders::REQ_CHANGE_BODY_HEIGHT)        //112
    {
      _blockedOrder              = data[1];
      _changeHeightParameters[0] = data[2];
      
      outData[outDataCounter++]  = Orders::ORDER_START;
    }
    else if (data[1] == Orders::REQ_MOVE_BODY)                 //114
    {
      _blockedOrder             = data[1];
      _moveBodyParameters[0]    = data[2];
      _moveBodyParameters[1]    = data[3];
      _moveBodyParameters[2]    = data[4];

      outData[outDataCounter++] = Orders::ORDER_START;
    }
    else if (data[1] == Orders::REQ_ROTATE_BODY)               //116
    {
      _blockedOrder             = data[1];
      _rotateBodyParameters[0]  = data[2];
      _rotateBodyParameters[1]  = data[3];
      _rotateBodyParameters[2]  = data[4];

      outData[outDataCounter++] = Orders::ORDER_START;
    }
    else if (data[1] == Orders::REQ_TWIST_BODY)                //118
    {
      _blockedOrder             = data[1];
      _twistBodyParameters[0]   = data[2];
      _twistBodyParameters[1]   = data[3];
      _twistBodyParameters[2]   = data[4];
      _twistBodyParameters[3]   = data[5];
      _twistBodyParameters[4]   = data[6];
      _twistBodyParameters[5]   = data[7];
      
      outData[outDataCounter++] = Orders::ORDER_START;
    }

    outData[outDataCounter++] = Orders::TRANS_END;

    if      (orderSource == OrderSource::FROM_SERIAL)  Serial.write (outData,          outDataCounter);
    else if (orderSource == OrderSource::FROM_ESP8266) _esp8266.send(_esp8266ClientID, outData, outDataCounter);
  }


  /****************************************************************
   * void _saveRobotBootState(RobotState x)
   * 
   * Almacena en la ROM el estado del robot.
   * 
   ****************************************************************/
  void SpiderCom::_saveRobotBootState(RobotState x) {
    byte stateByte = 0;

    if      (x == RobotState::INSTALL)   stateByte = 0;
    else if (x == RobotState::CALIBRATE) stateByte = 1;
    else if (x == RobotState::BOOT)      stateByte = 2;

    if (EEPROM.read(EepromAddresses::robotState) != stateByte) EEPROM.write(EepromAddresses::robotState, stateByte);
  }
  
  
  /****************************************************************
   * void _setRobotBootState(RobotState state)
   * 
   * En funcion del estado invoca los siguientes metodos del robot:
   * - installState()
   * - calibrateState()
   * - bootState()
   * 
   ****************************************************************/
  void SpiderCom::_setRobotBootState(RobotState state) {
    if      (state == RobotState::INSTALL)   _robotAction.getRobot().installState();
    else if (state == RobotState::CALIBRATE) _robotAction.getRobot().calibrateState();
    else if (state == RobotState::BOOT)      _robotAction.getRobot().bootState();
  }


  /****************************************************************
   * void _startESP8266()
   ****************************************************************/
  void SpiderCom::_startESP8266() {
    _esp8266Available = false;
    
    if (_esp8266.kick())
    {
      if (_esp8266.setOprToSoftAP())
      {
        if (_esp8266.setSoftAPParam(_esp8266SSID, _esp8266PWD, _esp8266CHL))
        {
          if (_esp8266.enableMUX())
          {
            if (_esp8266.startTCPServer(_esp8266Port))
            {
              if (_esp8266.setTCPServerTimeout(0)) _esp8266Available = true;
            }
          }
        }
      }
    }
  }

  /****************************************************************
   * void _startPins()
   ****************************************************************/
  void SpiderCom::_startPins() {
    for (int i = 0; i < 8; i++)
    {
      pinMode     (_PINS[i], OUTPUT);
      digitalWrite(_PINS[i], LOW);
    }
  }

  /****************************************************************
   * void _startRF24()
   ****************************************************************/
  void SpiderCom::_startRF24() {
    pinMode(RF24_PIN, INPUT_PULLUP);
    
    _rf24Available = _rf24.begin();
    if (_rf24Available == false) return;

    _rf24.setDataRate    (RF24_1MBPS);
    _rf24.setPALevel     (RF24_PA_MAX);
    _rf24.setRetries     (0, 15);
    _rf24.enableDynamicPayloads();
    _rf24.setChannel     (_rf24Channel);
    _rf24.openWritingPipe(_rf24Address);
    _rf24.openReadingPipe(1, _rf24Address);
    _rf24.startListening();
  }

  /****************************************************************
   * void _startSerial()
   ****************************************************************/
  void SpiderCom::_startSerial() {
    Serial.begin(115200);
  }

  /****************************************************************
   * void _startStateLED()
   ****************************************************************/
  void SpiderCom::_startStateLED() {
    pinMode     (STATE_LED_PIN, OUTPUT);
    digitalWrite(STATE_LED_PIN, LOW);
  }

  /****************************************************************
   * void _updateAutoSleep()
   * 
   ****************************************************************/
  void SpiderCom::_updateAutoSleep() {
    if (_lastBlockedOrderTime == 0) return;

    if (millis() - _lastBlockedOrderTime <= _AUTO_SLEEP_OVERTIME) return;

    if (_robotAction.getRobot().getState() == RobotState::ACTION) _robotAction.sleepMode();
    
    _lastBlockedOrderTime = 0;
  }


  /****************************************************************
   * void _updateBlockedOrder()
   * 
   * Se llama desde SpiderCom::updateOrder()
   *          Se llama desde Spider0::update()
   * 
   ****************************************************************/
  void SpiderCom::_updateBlockedOrder() {

    //0.- Si no hay orden, no vamos...
    if (_blockedOrder == 0) return;

    //1.- Procesar la orden
    byte blockedOrder = this -> _blockedOrder;
    
    _lastBlockedOrderTime = millis();
    _orderState           = OrderState::EXECUTE_START;

    if (blockedOrder == Orders::REQ_CRAWL_FORWARD)            // 80
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.crawlForward();
    }
    else if (blockedOrder == Orders::REQ_CRAWL_BACKWARD)      // 82
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.crawlBackward();
    }
    else if (blockedOrder == Orders::REQ_CRAWL_LEFT)          // 84
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.crawlLeft();
    }
    else if (blockedOrder == Orders::REQ_CRAWL_RIGHT)         // 86
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.crawlRight();
    }
    else if (blockedOrder == Orders::REQ_TURN_LEFT)           // 88
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.turnLeft();
    }
    else if (blockedOrder == Orders::REQ_TURN_RIGHT)          // 90
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.turnRight();
    }
    else if (blockedOrder == Orders::REQ_ACTIVE_MODE)         // 92
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.activeMode();
    }
    else if (blockedOrder == Orders::REQ_SLEEP_MODE)          // 94
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.sleepMode();
    }
    else if (blockedOrder == Orders::REQ_SWITCH_MODE)         // 96
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.switchMode();
    }
    else if (blockedOrder == Orders::REQ_INSTALL_STATE)       // 64
    {
      this -> _saveRobotBootState(RobotState::INSTALL);
      
      _robotAction.getRobot().installState();
    }
    else if (blockedOrder == Orders::REQ_CALIBRATE_STATE)     // 66
    {
      this -> _saveRobotBootState(RobotState::CALIBRATE);
      
      _robotAction.getRobot().calibrateState();
    }
    else if (blockedOrder == Orders::REQ_BOOT_STATE)          // 68
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      _robotAction.getRobot().bootState();
    }
    else if (blockedOrder == Orders::REQ_CALIBRATE_VERIFY)    // 70
    {
      _robotAction.getRobot().calibrateVerify();
    }
    else if (blockedOrder == Orders::REQ_CRAWL)               //110
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      float x      = _crawlParameters[0] - 64;
      float y      = _crawlParameters[1] - 64;
      float angulo = _crawlParameters[2] - 64;

      _robotAction.crawl(x, y, angulo);
    }
    else if (blockedOrder == Orders::REQ_CHANGE_BODY_HEIGHT)  //112
    {
      this -> _saveRobotBootState(RobotState::BOOT);
      
      float h = _changeHeightParameters[0] - 64;

      _robotAction.changeBodyHeight(h);
    }
    else if (blockedOrder == Orders::REQ_MOVE_BODY)           //114
    {
      this -> _saveRobotBootState(RobotState::BOOT);

      float x =         _moveBodyParameters[0] - 64;
      float y =         _moveBodyParameters[1] - 64;
      float z = -1.0 * (_moveBodyParameters[2] - 64);

      _robotAction.moveBody(x, y, z);
    }
    else if (blockedOrder == Orders::REQ_ROTATE_BODY)         //116
    {
      this -> _saveRobotBootState(RobotState::BOOT);

      float x = _rotateBodyParameters[0] - 64;
      float y = _rotateBodyParameters[1] - 64;
      float z = _rotateBodyParameters[2] - 64;

      _robotAction.rotateBody(x, y, z);
    }
    else if (blockedOrder == Orders::REQ_TWIST_BODY)          //118
    {
      this -> _saveRobotBootState(RobotState::BOOT);

      float xMove   =         _twistBodyParameters[0] - 64;
      float yMove   =         _twistBodyParameters[1] - 64;
      float zMove   = -1.0 * (_twistBodyParameters[2] - 64);
      float xRotate =         _twistBodyParameters[3] - 64;
      float yRotate =         _twistBodyParameters[4] - 64;
      float zRotate =         _twistBodyParameters[5] - 64;

      _robotAction.twistBody(Point(xMove, yMove, zMove), Point(xRotate, yRotate, zRotate));
    }

    //.- Fin
    _blockedOrder = 0;
    _orderState   = OrderState::EXECUTE_DONE;
  }

  
  /****************************************************************
   * void _updateESP8266()
   * 
   ****************************************************************/
  void SpiderCom::_updateESP8266() {
    if (_esp8266Available == false) return;

    int inDataCount = _esp8266.recv( &_esp8266ClientID, _esp8266InData, IN_DATA_SIZE, 2);
    if (inDataCount <= 0) return;

    for (int i = 0; i < inDataCount; i++)
    {
      if (_esp8266InData[i] == Orders::TRANS_START) this -> _handleOrder(_esp8266InData + i, OrderSource::FROM_ESP8266);
    }
  }

  
  /****************************************************************
   * void _updateRF24()
   * 
   ****************************************************************/
  void SpiderCom::_updateRF24() {
    if (_rf24Available    == false) return;
    if (_rf24.available() == false) return;

    int inDataCount = _rf24.getDynamicPayloadSize();
    if (inDataCount <= 0) return;

    _rf24.read(_rf24InData, inDataCount);

    for (int i = 0; i < inDataCount; i++)
    {
      if ((_rf24InData[i] == Orders::TRANS_START) && (_rf24InData[i + 1] != Orders::REQ_ECHO)) this -> _handleOrder(_rf24InData + i, OrderSource::FROM_RF24);
    }
  }

  
  /****************************************************************
   * void _updateSerial()
   * 
   ****************************************************************/
  void SpiderCom::_updateSerial() {
    while (Serial.available() > 0)
    {
      byte inByte = Serial.read();

      if (inByte == Orders::TRANS_START) _serialInDataCounter = 0;
      _serialInData[_serialInDataCounter++] = inByte;
      
      if (inByte == Orders::TRANS_END)
      {
        if (_serialInData[0] == Orders::TRANS_START)
        {
          this -> _handleOrder(_serialInData, OrderSource::FROM_SERIAL);
          _serialInDataCounter = 0;
        }
      }
    }
  }
  
  /****************************************************************
   * void _updateStateLED()
   * 
   * Actualizar el estado de los LEDs
   * 
   ****************************************************************/
  void SpiderCom::_updateStateLED() {
    if (_ledCounter / _LED_BLINK_CYCLE < abs(_ledState))
    {
      if      (_ledCounter % _LED_BLINK_CYCLE == 0)                    this -> _setStateLED(_ledState > 0 ? HIGH : LOW);
      else if (_ledCounter % _LED_BLINK_CYCLE == _LED_BLINK_CYCLE / 2) this -> _setStateLED(_ledState > 0 ? LOW : HIGH);
    }

    _ledCounter++;

    if (_ledCounter / _LED_BLINK_CYCLE >= abs(_ledState) + (unsigned int) 3)
    {
      _ledCounter = 0;

      if      (_robotAction.getRobot().getState() == RobotState::ACTION)    _ledState = 1;
      else if (_robotAction.getRobot().getState() == RobotState::BOOT)      _ledState = 1;
      else if (_robotAction.getRobot().getState() == RobotState::CALIBRATE) _ledState = 2;
      else if (_robotAction.getRobot().getState() == RobotState::INSTALL)   _ledState = 3;

      if ((_robotAction.getRobot().getPower().isPowerGroupAutoSwitch() == true) && (_robotAction.getRobot().getPower().isPowerGroupState() == false)) _ledState = -1;
    }
  }
}
