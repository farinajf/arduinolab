#include "robotLegItem.h"

namespace SPIDER {
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  Point::Point() {}

  Point::Point(float x, float y, float z) : _x(x), _y(y), _z(z) {}

  /****************************************************************
   * static float getDistance(Point p1, Point p2)
   ****************************************************************/
  float Point::getDistance(Point p1, Point p2) {
    float dx = p1._x - p2._x;
    float dy = p1._y - p2._y;
    float dz = p1._z - p2._z;

    float d2 = dx*dx + dy*dy + dz*dz;

    return (d2 < FLOAT_PRECISSION) ? 0.0 : sqrt(d2);
  }






  
  /****************************************************************
   * 
   * Constructor()
   * 
   ****************************************************************/
  RobotLegItem::RobotLegItem(const uint8_t addr,
                             const short   position_0,
                             const short   position_90,
                             const short   minAngle,
                             const short   maxAngle,
                             const short   zeroAngle,
                             const bool    jointDir) : _addr       (addr),
                                                       _position_0 (position_0),
                                                       _position_90(position_90),
                                                       _minAngle   (minAngle),
                                                       _maxAngle   (maxAngle),
                                                       _zeroAngle  (zeroAngle),
                                                       _jointDir   (jointDir) {}

  /****************************************************************
   * void init()
   ****************************************************************/
  void RobotLegItem::init() {}

  /****************************************************************
   * bool checkJointAngle(float jointAngle)
   * 
   ****************************************************************/
  bool RobotLegItem::checkJointAngle(float jointAngle) const {
    while (jointAngle > _maxAngle) jointAngle -= 360;
    while (jointAngle < _minAngle) jointAngle += 360;

    return (jointAngle >= _minAngle && jointAngle <= _maxAngle) ? true : false;
  }

  /****************************************************************
   * void rotateToDirectly(ServoDriver *driver, float angle)
   * 
   ****************************************************************/
  void RobotLegItem::rotateToDirectly(ServoDriver *driver, float jointAngle) {
    if (this -> checkJointAngle(jointAngle) == false) return;

    float servoAngle = _zeroAngle + (_jointDir ? 1 : -1) * jointAngle;

    while (servoAngle > 360) servoAngle -= 360;
    while (servoAngle < 0)   servoAngle += 360;

    if (servoAngle > 180) return;
    
    if (_firstRotate == true) _firstRotate = false;

    driver -> rotateTo(_addr, servoAngle, _position_0, _position_90);
    delay(FIRST_ROTATE_DELAY);

    _angleNow      = jointAngle;
    _servoAngleNow = servoAngle;
  }

  
  
  
  
  /***********************************************************************************
   *                    Metodos Privados
   **********************************************************************************/

}
