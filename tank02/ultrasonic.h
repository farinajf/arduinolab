volatile unsigned long _measurePrevTime = 0;
volatile unsigned int  _rightCount      = 0;
volatile unsigned int  _leftCount       = 0;
volatile char          _measureFlag     = 0;

unsigned long _getDistancePrevTime = 0;
unsigned long _leftCountTime       = 0;
unsigned long _rightCountTime      = 0;
double        distance             = 0;
bool          isObstacleLeft       = false;
bool          isObstacleRight      = false;
char          _rightReceiveFlag    = 0;
char          _leftReceiveFlag     = 0;

////////////////////////////////////////////////////////////////////
//Private
////////////////////////////////////////////////////////////////////
/**
 * 
 */
void _measureDistance() {
  if (_measureFlag == 0)
  {
    _measurePrevTime = micros();
    attachPinChangeInterrupt(PIN_ECHO, _measureDistance, FALLING);
    _measureFlag = 1;
  }
  else if (_measureFlag == 1)
  {
    distance = (micros() - _measurePrevTime) * 0.017;
    _measureFlag = 2;
  }
}

/**
 * Cuenta el numero de veces que salta la interrupcion
 */
void _leftReceive() {_leftCount++;}

/**
 * Cuenta el numero de veces que salta la interrupcion
 */
void _rightReceive() {_rightCount++;}

////////////////////////////////////////////////////////////////////
// Public
////////////////////////////////////////////////////////////////////
/**
 * 
 */
void ultrasonicInit() {
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO,    INPUT);

  pinMode(PIN_IR_LEFT, INPUT);
  pinMode(PIN_IR_RIGHT, INPUT);

  //attachPinChangeInterrupt(PIN_IR_LEFT,  _leftReceive,  LOW);
  //attachPinChangeInterrupt(PIN_IR_RIGHT, _rightReceive, FALLING);
}

/**
 * Calcula la distancia al frente.
 */
void getDistance() {
  if (millis() - _getDistancePrevTime <= 50) return;

  _getDistancePrevTime = millis();

  _measureFlag = 0;
  attachPinChangeInterrupt(PIN_ECHO, _measureDistance, RISING);
  
  digitalWrite     (PIN_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite     (PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite     (PIN_TRIGGER, LOW);
}

/**
 * Controla si hay obstaculos a la derecha o a la izquierda
 */
void checkObstacle() {
  if (millis() - _leftCountTime > 50)
  {
    isObstacleLeft = (digitalRead(PIN_IR_LEFT) == HIGH) ? false : true;

    _leftCount     = 0;
    _leftCountTime = millis();
  }
  if (millis() - _rightCountTime > 50)
  {
    isObstacleRight = (digitalRead(PIN_IR_RIGHT) == HIGH) ? false : true;

    _rightCount     = 0;
    _rightCountTime = millis();
  }

  Serial.print(isObstacleLeft); Serial.print("  "); Serial.println(isObstacleRight);
}
