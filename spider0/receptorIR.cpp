#include "receptorIR.h"

namespace SPIDER {
  /****************************************************************
   * void _encoding(decode_results *results)
   ****************************************************************/
//  void ReceptorIR::_encoding(const decode_results *results) const {
//    switch (results->decode_type)
//    {
//      case NEC:          Serial.print("NEC");           break;
//      case SONY:         Serial.print("SONY");          break;
//      case RC5:          Serial.print("RC5");           break;
//      case RC6:          Serial.print("RC6");           break;
//      case DISH:         Serial.print("DISH");          break;
//      case SHARP:        Serial.print("SHARP");         break;
//      case JVC:          Serial.print("JVC");           break;
////      case SANYO:        Serial.print("SANYO");         break;
////      case MITSUBISHI:   Serial.print("MITSUBISHI");    break;
//      case SAMSUNG:      Serial.print("SAMSUNG");       break;
//      case LG:           Serial.print("LG");            break;
//      case WHYNTER:      Serial.print("WHYNTER");       break;
////      case AIWA_RC_T501: Serial.print("AIWA_RC_T501");  break;
//      case PANASONIC:    Serial.print("PANASONIC");     break;
//      case DENON:        Serial.print("Denon");         break;
//      case UNKNOWN:      Serial.print("UNKNOWN");       break;
//    }
//  }

  /****************************************************************
   * void _ircode(decode_results *results)
   ****************************************************************/
//  void ReceptorIR::_ircode(const decode_results *results) const {
//    // Panasonic has an Address
//    if (results->decode_type == PANASONIC)
//    {
//      Serial.print(results->address, HEX);
//      Serial.print(":");
//    }
//
//    // Print Code
//    Serial.print(results->value, HEX);
//  }

  /****************************************************************
   * void _dumpInfo(const decode_results *results) const
   ****************************************************************/
//  void ReceptorIR::_dumpInfo(const decode_results *results) const {
//    if (results -> overflow)
//    {
//      Serial.println("Codigo IR demasiado largo. Edita RremoteInt.h e incrementa RAWBUF!!");
//      return;
//    }
//
//    Serial.print  ("Encoding: ");
//    _encoding(results);
//    Serial.println("");
//
//    Serial.print  ("Code: ");
//    _ircode(results);
//    Serial.print  (" (");
//    Serial.print  (results->bits, DEC);
//    Serial.println("bits");
//  }

  /****************************************************************
   * CodigoIR _getResultado(const decode_results results) const
   * 
   ****************************************************************/
//  CodigoIR ReceptorIR::_getResultado(const decode_results *results) const {
//    
//    //_dumpInfo(results);
//    
//    switch (results->value)
//    {
//      case 0xFD8877:   return IR_UP;
//      case 0xFD9867:   return IR_DOWN;
//      case 0xFD28D7:   return IR_LEFT;
//      case 0xFD6897:   return IR_RIGHT;
//      case 0xFDA857:   return IR_OK;
//      case 0xFD30CF:   return IR_ASTERISK;
//      case 0xFD708F:   return IR_HASH;
//      case 0xFDB04F:   return IR_T_0;
//      case 0xFD00FF:   return IR_T_1;
//      case 0xFD807F:   return IR_T_2;
//      case 0xFD40BF:   return IR_T_3;
//      case 0xFD20DF:   return IR_T_4;
//      case 0xFDA05F:   return IR_T_5;
//      case 0xFD609F:   return IR_T_6;
//      case 0xFD10EF:   return IR_T_7;
//      case 0xFD906F:   return IR_T_8;
//      case 0xFD50AF:   return IR_T_9;
//      case 0xFFFFFFFF: return IR_CODE_REPEAT;
//      default:         return IR_NONE; 
//    }
//  }

  /****************************************************************
   * void init()
   ****************************************************************/
  void ReceptorIR::init() {
//    _receiver.enableIRIn();
  }

  /****************************************************************
   * CodigoIR receive()
   * 
   ****************************************************************/
//  CodigoIR ReceptorIR::receive() {
//    decode_results received;
//    CodigoIR       result = IR_NONE;
//
//    if (_receiver.decode(&received) == true)
//    {
//      result = _getResultado(&received);
//
//      if (result != IR_CODE_REPEAT) _lastResult = result;
//
//      // Prepare for the next value
//      _receiver.resume();
//    }
//
//    return (result != IR_CODE_REPEAT) ? result : _lastResult;
//  }
}
