#include <Servo.h>
#include "pins.h"
#include "tankGlobals.h"

#ifndef TANK_SONAR_H
#define TANK_SONAR_H

namespace TANK01
{
  class TankSonar
  {
    private:
      const int SERVO1_ANGLE_INI =    0;
      const int SERVO1_ANGLE_FIN =  180;
      const int ANGLE_STEP       =    2;
      const int SERVO1_ANGLE     =   90;
      const int SERVO2_ANGLE     =  135;
      const int SLEEP            =  500;

      unsigned long _instanteMedidaPrevia = 0;
      double        _distancia            = 0.0;
      int           _servo1Angle          = SERVO1_ANGLE;
      int           _servo2Angle          = SERVO2_ANGLE;
      Servo         _servo1;
      Servo         _servo2;

      /**
       * Mueve el servo 1
       */
      void _setServo1(const int angle) {
        _servo1Angle = angle;
        _servo1.write(_servo1Angle);
      }

      /**
       * Mueve el servo 2
       */
      void _setServo2(const int angle) {
        _servo2Angle = angle;
        _servo2.write(_servo2Angle);
      }


      /**
       * Mueve el servo1 despacio.
       */
      void _setServo1Slowly(int finalAngle) {
        const boolean subir = (finalAngle >= _servo1Angle);
        boolean       parar;
        int           i     = _servo1Angle;
  
        
        do
        {
          i += (subir) ? ANGLE_STEP : -ANGLE_STEP;

          _servo1.write(i);
          delay(20);

          parar = (subir) ? (i >= finalAngle) : (i <= finalAngle);
        }
        while (parar == false);

        _setServo1(finalAngle);
      }

      /***************************************************************************************
       * Dispara el TRIGGER durante 2 microsegundos.
       * 
       **************************************************************************************/
      void _calculaDistancia() {
        if (millis() - _instanteMedidaPrevia > 50)
        {
          _instanteMedidaPrevia = millis();

          digitalWrite     (PIN_TRIGGER, LOW);
          delayMicroseconds(2);
          digitalWrite     (PIN_TRIGGER, HIGH);
          delayMicroseconds(10);
          digitalWrite     (PIN_TRIGGER, LOW);

          long duracion = pulseIn(PIN_ECHO, HIGH);
          Serial.print("duracion: "); Serial.println(duracion);

          // (340m/s x 100 cm / 1000000 us) / 2 = 0.0170145
          _distancia = duracion*0.017;
        }
      }

      /***************************************************************************************
       * Situa el servo en una posicion y calcula la distancia
       * 
       **************************************************************************************/
      void _calculaDistancia(int posicion1, int posicion2) {
        _setServo1Slowly(posicion1);
        _setServo2      (posicion2);

        _calculaDistancia();
      }

    public:
      /***************************************************************************************
       * void init()
       **************************************************************************************/
      void init() {
        pinMode(PIN_TRIGGER, OUTPUT);
        pinMode(PIN_ECHO,    INPUT);
        
        _servo1.attach(PIN_SERVO_1);
        _servo2.attach(PIN_SERVO_2);
      }

      /**************************************************************************************
       * void checkObstacleFront()
       **************************************************************************************/
      void checkObstacleFront() {
        _setServo1Slowly(SERVO1_ANGLE);
        _setServo2      (SERVO2_ANGLE);

        _calculaDistancia();
        toString();

        if (_distancia <= DISTANCIA_MINIMA) _MOTION_MODE_ = STANDBY;
        
        return;
      }

      /**************************************************************************************
       * void checkObstacleFront()
       **************************************************************************************/
      void buscar() {
        _calculaDistancia(SERVO1_ANGLE_INI, SERVO2_ANGLE);
        double distancia_izquierda = _distancia;
        toString();

        delay(SLEEP);

        _calculaDistancia(SERVO1_ANGLE, SERVO2_ANGLE);
        double distancia_centro = _distancia;
        toString();
        
        delay(SLEEP);

        _calculaDistancia(SERVO1_ANGLE_FIN, SERVO2_ANGLE);
        double distancia_derecha = _distancia;
        toString();

        delay(SLEEP);

        if      (distancia_centro > DISTANCIA_MINIMA) _MOTION_MODE_ = FORWARD;
        else if (distancia_derecha > distancia_izquierda)
        {
          if (distancia_derecha > DISTANCIA_MINIMA) _MOTION_MODE_ = TURNRIGHT;
        }
        else
        {
          if (distancia_izquierda > DISTANCIA_MINIMA) _MOTION_MODE_ = TURNLEFT;
        }

        _setServo1Slowly(SERVO1_ANGLE);
        
        return;
      }

      /***************************************************************************************
       * void toString()
       * 
       ***************************************************************************************/
      void toString() {
        Serial.print("Angulo servo 1: "); Serial.print(_servo1Angle); Serial.print(" ");
        Serial.print("Angulo servo 2: "); Serial.print(_servo2Angle); Serial.print(" ");
        Serial.print("Distancia: "); Serial.print(_distancia); Serial.println(" cm.");
      }
  };
}
#endif
