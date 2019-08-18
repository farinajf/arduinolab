/**
 * 
 */
#include <Servo.h>

#define PIN_SERVO 12
#define PIN_TRIG  10
#define PIN_ECHO  11

const int ROTACION_INI =  15;
const int ROTACION_FIN = 165;
const int SLEEP        = 100;

Servo _servo;
long  _duracion;
int   _distancia;

/**
 * 
 */
int _calculaDistancia() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(PIN_TRIG, LOW);

  _duracion = pulseIn(PIN_ECHO, HIGH);

  _distancia = ((_duracion*0.034)/2.0);

  return _distancia;
}

/**
 * 
 */
void setup() {
  Serial.begin(9600);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  
  _servo.attach(PIN_SERVO);
}

/**
 * 
 */
void loop() {
  //1.- Giro en un sentido
  for(int i = ROTACION_INI; i <= ROTACION_FIN;i++)
  {  
    _servo.write(i);
    delay(SLEEP);

    _distancia = _calculaDistancia();

    Serial.print(i); Serial.print(","); Serial.print(_distancia); Serial.print(".");
  }

  //2.- Giro en el sentido contrario
  for(int i = ROTACION_FIN; i >= ROTACION_INI; i--)
  {  
    _servo.write(i);
    delay(SLEEP);

    _distancia = _calculaDistancia();

    Serial.print(i); Serial.print(","); Serial.print(_distancia); Serial.print(".");
  }
}
