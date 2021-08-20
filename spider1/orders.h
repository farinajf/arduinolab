#ifndef ORDERS_H
#define ORDERS_H

#include "globals.h"

namespace SPIDER {
  class Orders {
    // Format:  [transStart] [order] [data 0] [data 1] ... [data n] [transEnd]
    //          [x] is byte type and the range of [order] and [data x] is 0~127
    // Process: The requesting party send the order, then the responding party respond the order.
    //          The non blocking order will be responded immediately, and the blocking order will
    //          be responded orderStart immediately, then respond orderDone after completion.

    public:
      // Data stream control orders, range is 128 ~ 255
      // These orders are used to control data stream.

      static const byte TRANS_START = 128;
      static const byte TRANS_END   = 129;


      // Orders, range is 0 ~ 127
      // Orders are used to control target.
      // Some orders have proprietary response orders, others use orderStart and orderDone.
      // The even orders is sent by the requesting party, and the odd orders is sent by the responding party.

      // Non blocking orders, range is 0 ~ 63

      // Connection
      // Request echo, to confirm the target
      static const byte REQ_ECHO = 0;                  // [order]
      // Respond echo
      static const byte ECHO     = 1;                  // [order]

      // Function
      // Request supply voltage
      static const byte REQ_SUPPLY_VOLTAGE = 10;       // [order]
      // Respond supply voltage
      static const byte SUPPLY_VOLTAGE     = 11;       // [order] [voltage * 100 / 128] [voltage * 100 % 128]
      // Request change I/O port state
      static const byte REQ_CHANGE_IO      = 20;       // [order] [IOindex] [1/0]

      // Installation
      static const byte requestMoveLeg = 30;            // [order] [leg] [64 + dx] [64 + dy] [64 + dz]
      static const byte requestCalibrate = 32;          // [order]

      // Blocking orders, range is 64 ~ 127

      // Installation
      static const byte REQ_INSTALL_STATE  = 64;       // [order]
      static const byte requestCalibrateState = 66;     // [order]
      static const byte requestBootState = 68;          // [order]
      static const byte requestCalibrateVerify = 70;    // [order]

      // Simple action
      static const byte REQ_CRAWL_FORWARD  = 80;       // [order]
      static const byte REQ_CRAWL_BACKWARD = 82;       // [order]
      static const byte REQ_CRAWL_LEFT     = 84;       // [order]
      static const byte REQ_CRAWL_RIGHT    = 86;       // [order]
      static const byte REQ_TURN_LEFT      = 88;       // [order]
      static const byte REQ_TURN_RIGHT     = 90;       // [order]
      static const byte REQ_ACTIVE_MODE    = 92;       // [order]
      static const byte REQ_SLEEP_MODE     = 94;       // [order]
      static const byte REQ_SWITCH_MODE    = 96;       // [order]

      // Complex action
      static const byte requestCrawl = 110;             // [order] [64 + x] [64 + y] [64 + angle]
      static const byte REQ_CHANGE_BODY_HEIGHT = 112;  // [order] [64 + height]
      static const byte requestMoveBody = 114;          // [order] [64 + x] [64 + y] [64 + z]
      static const byte requestRotateBody = 116;        // [order] [64 + x] [64 + y] [64 + z]
      static const byte requestTwistBody = 118;         // [order] [64 + xMove] [64 + yMove] [64 + zMove] [64 + xRotate] [64 + yRotate] [64 + zRotate]

      // Universal responded orders, range is 21 ~ 127
      // These orders are used to respond orders without proprietary response orders.

      static const byte ORDER_START = 21;              // [order]
      static const byte ORDER_DONE  = 23;              // [order]
  };
}

#endif
