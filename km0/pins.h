#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

/**
 * Pines usados:
 *  3, 5, 5, 6, 7, 8, 9, 10, 11, 12, 13
 *  A0, A1, A2, A3, A4, A5
 *  
 */

//Signal Right & Left
#define PIN_LIGHT_LEFT  3
#define PIN_LIGHT_RIGHT 4

//Motor DERECHO
#define PIN_EN_D        5 //PWD
#define PIN_IN1_D       7
#define PIN_IN2_D       6

//Motor IZQUIERDO
#define PIN_EN_I       10 //PWD
#define PIN_IN1_I       9
#define PIN_IN2_I       8

//ULTRASONIC
#define PIN_TRIGGER    A0
#define PIN_ECHO       A1

//TRACKING SENSOR (Line walking)
#define PIN_TLS_RIGHT  A2
#define PIN_TLS_LEFT   A3

//INFRARED
#define PIN_IR_RIGHT   A4
#define PIN_IR_LEFT    A5

//SERVO
#define PIN_SERVO      11

//BUZZER
#define PIN_BUZZER     12

//BOTON
#define PIN_KEY        13

#endif
