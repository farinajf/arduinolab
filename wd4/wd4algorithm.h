#include "wd4Globals.h"

#ifndef WD4ALGORIHM_H
#define WD4ALGORIHM_H

/****************************************************************
 * MOTION_MODE_ENUM _getLateralMotion(int  distanceLeft,
 *                                    int  distanceRight)
 * 
 ****************************************************************/
MOTION_MODE_ENUM _getLateralMotion(int dl, int dr) {
  return (dl < dr) ? TURNRIGHT : TURNLEFT;
}


/****************************************************************
 * MOTION_MODE_ENUM _getLateralMotion(int  distanceLeft,
 *                                    int  distanceRight,
 *                                    bool isObjectLeft,
 *                                    bool isObjectRight)
 * 
 ****************************************************************/
MOTION_MODE_ENUM _getLateralMotion(int dl, int dr, bool iol, bool ior) {
  if ( iol &&  ior) return BACKWARD;
  
  if ( iol && !ior) return TURNRIGHT;
  if (!iol &&  ior) return TURNLEFT;

  return (dl < dr) ? TURNRIGHT : TURNLEFT;
}

/****************************************************************
 * MOTION_MODE_ENUM getMotionMode(int  distance,
 *                                int  distanceLeft,
 *                                int  distanceRight,
 *                                bool isObjectLeft,
 *                                bool isObjectRight)
 * 
 ****************************************************************/
MOTION_MODE_ENUM getMotionMode(int d, int dl, int dr, bool iol, bool ior) {
  //1.- Objeto muy cerca
  if (d  < DISTANCE_SUPER_MIN)         return BACKWARD;
  if (dl < DISTANCE_SUPER_MIN_LATERAL) return BACKWARD;
  if (dr < DISTANCE_SUPER_MIN_LATERAL) return BACKWARD;

  //2.- Objetos cerca
  if ((dl < DISTANCE_MIN_LATERAL) && (dr < DISTANCE_MIN_LATERAL)) return BACKWARD;

  //2.- Objeto cerca delante
  if (d < DISTANCE_MIN) return _getLateralMotion(dl, dr, iol, ior);

  //3.- Objeto esquina izquierda o derecha
  if ((dl < DISTANCE_MIN_LATERAL) || (dr < DISTANCE_MIN_LATERAL)) return _getLateralMotion(dl, dr);

  //4.- Objeto en el lateral izquierdo
  if (iol && !ior) return TURNRIGHT;

  //5.- Objeto en el lateral derecho
  if (!iol && ior) return TURNLEFT;

  //6.- Fin
  return FORWARD;
}
#endif
