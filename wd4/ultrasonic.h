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
    attachPinChangeInterrupt(PIN_CENTER_ECHO, _measureDistance, FALLING);
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
    attachPinChangeInterrupt(PIN_RIGHT_ECHO, _measureDistanceRight, FALLING);
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
    attachPinChangeInterrupt(PIN_LEFT_ECHO, _measureDistanceLeft, FALLING);
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
  pinMode(PIN_CENTER_TRIGGER, OUTPUT);
  pinMode(PIN_CENTER_ECHO,    INPUT);

  pinMode(PIN_RIGHT_TRIGGER,  OUTPUT);
  pinMode(PIN_RIGHT_ECHO,     INPUT);

  pinMode(PIN_LEFT_TRIGGER,   OUTPUT);
  pinMode(PIN_LEFT_ECHO,      INPUT);

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
  attachPinChangeInterrupt(PIN_CENTER_ECHO, _measureDistance, RISING);

  digitalWrite     (PIN_CENTER_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite     (PIN_CENTER_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite     (PIN_CENTER_TRIGGER, LOW);
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
  attachPinChangeInterrupt(PIN_RIGHT_ECHO, _measureDistanceRight, RISING);

  digitalWrite     (PIN_RIGHT_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite     (PIN_RIGHT_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite     (PIN_RIGHT_TRIGGER, LOW);
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
  attachPinChangeInterrupt(PIN_LEFT_ECHO, _measureDistanceLeft, RISING);

  digitalWrite     (PIN_LEFT_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite     (PIN_LEFT_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite     (PIN_LEFT_TRIGGER, LOW);
}
