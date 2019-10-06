volatile unsigned long _measureRightPrevTime = 0;
volatile unsigned long _measureLeftPrevTime  = 0;
volatile unsigned long _measurePrevTime      = 0;
volatile char          _measureRightFlag     = 0;
volatile char          _measureLeftFlag      = 0;
volatile char          _measureFlag          = 0;

unsigned long _distanceRightPrevTime = 0;
unsigned long _distanceLeftPrevTime  = 0;
unsigned long _distancePrevTime      = 0;
double        distanceRight          = 0;
double        distanceLeft           = 0;
double        distance               = 0;

////////////////////////////////////////////////////////////////////
//Private
////////////////////////////////////////////////////////////////////
/**
 * void _measureDistance()
 */
void _measureDistance() {
  if (_measureFlag == 0)
  {
    _measurePrevTime = micros();
    attachPinChangeInterrupt(PIN_ECHO_CENTER, _measureDistance, FALLING);
    _measureFlag = 1;
  }
  else if (_measureFlag == 1)
  {
    distance = (micros() - _measurePrevTime) * 0.017;
    _measureFlag = 2;
  }
}

/**
 * void _measureRightDistance()
 */
void _measureDistanceRight() {
  if (_measureRightFlag == 0)
  {
    _measureRightPrevTime = micros();
    attachPinChangeInterrupt(PIN_ECHO_RIGHT, _measureDistanceRight, FALLING);
    _measureRightFlag = 1;
  }
  else if (_measureRightFlag == 1)
  {
    distanceRight = (micros() - _measureRightPrevTime) * 0.017;
    _measureRightFlag = 2;
  }
}

/**
 * void _measureDistanceLeft()
 */
void _measureDistanceLeft() {
  if (_measureLeftFlag == 0)
  {
    _measureLeftPrevTime = micros();
    attachPinChangeInterrupt(PIN_ECHO_LEFT, _measureDistanceLeft, FALLING);
    _measureLeftFlag = 1;
  }
  else if (_measureLeftFlag == 1)
  {
    distanceLeft = (micros() - _measureLeftPrevTime) * 0.017;
    _measureLeftFlag = 2;
  }
}

////////////////////////////////////////////////////////////////////
// Public
////////////////////////////////////////////////////////////////////
/**
 * 
 */
void ultrasonicInit() {
  pinMode(PIN_TRIGGER_CENTER, OUTPUT);
  pinMode(PIN_ECHO_CENTER,    INPUT);

  pinMode(PIN_TRIGGER_RIGHT,  OUTPUT);
  pinMode(PIN_ECHO_RIGHT,     INPUT);

  pinMode(PIN_TRIGGER_LEFT,   OUTPUT);
  pinMode(PIN_ECHO_LEFT,      INPUT);

  //pinMode(PIN_IR_LEFT,        INPUT);
  //pinMode(PIN_IR_RIGHT,       INPUT);
}

/**
 * void getDistance()
 * 
 * Calcula la distancia al frente.
 * 
 */
void getDistance() {
  if (millis() - _distancePrevTime <= 50) return;

  _distancePrevTime = millis();

  _measureFlag = 0;
  attachPinChangeInterrupt(PIN_ECHO_CENTER, _measureDistance, RISING);

  digitalWrite     (PIN_TRIGGER_CENTER, LOW);
  delayMicroseconds(2);
  digitalWrite     (PIN_TRIGGER_CENTER, HIGH);
  delayMicroseconds(10);
  digitalWrite     (PIN_TRIGGER_CENTER, LOW);
}

/**
 * void getDistanceRight()
 * 
 * Calcula la distancia al frente.
 * 
 */
void getDistanceRight() {
  if (millis() - _distanceRightPrevTime <= 50) return;

  _distanceRightPrevTime = millis();

  _measureRightFlag = 0;
  attachPinChangeInterrupt(PIN_ECHO_RIGHT, _measureDistanceRight, RISING);

  digitalWrite     (PIN_TRIGGER_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite     (PIN_TRIGGER_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite     (PIN_TRIGGER_RIGHT, LOW);
}

/**
 * void getDistanceLeft()
 * 
 * Calcula la distancia al frente.
 * 
 */
void getDistanceLeft() {
  if (millis() - _distanceLeftPrevTime <= 50) return;

  _distanceLeftPrevTime = millis();

  _measureLeftFlag = 0;
  attachPinChangeInterrupt(PIN_ECHO_LEFT, _measureDistanceLeft, RISING);

  digitalWrite     (PIN_TRIGGER_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite     (PIN_TRIGGER_LEFT, HIGH);
  delayMicroseconds(10);
  digitalWrite     (PIN_TRIGGER_LEFT, LOW);
}
