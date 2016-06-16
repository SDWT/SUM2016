/* FILENAME: U_SCENE.H
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Units difinitions
 */

#ifndef __U_SCENE_H_
#define __U_SCENE_H_

#include "anim.h"

typedef enum tagds1AIRPLNSTATE
{
  DS1_AIRPLN_STATE_FLY_IN, 
  DS1_AIRPLN_STATE_LANDING,
  DS1_AIRPLN_STATE_LANDING_RUNWAY,
  DS1_AIRPLN_STATE_TAXI,
  DS1_AIRPLN_STATE_ALIGN,
  DS1_AIRPLN_STATE_TAKEOFF_RUNWAY,
  DS1_AIRPLN_STATE_TAKEOFF,
  DS1_AIRPLN_STATE_FLY_OUT
} ds1AIRPLNSTATE;

/* Plane unit */
typedef struct
{
  CHAR *FileName;
  VEC Pos;
  INT SPEED;
  ds1AIRPLNSTATE STATE;
  ds1OBJ Obj;
} ds1PLANE;

/* Port Unit */
typedef struct
{
  CHAR *FileName;
  VEC Pos;     /* Position airport */
  ds1OBJ Obj;  /* Airport object */
               /* Runway in */
               /* Runway out */
               /* Runway taxi */
} ds1PORT;

typedef struct
{
  ds1UNIT;
  ds1PLANE Plane;
} ds1UNIT_PLANE;

/* Port Unit */
typedef struct
{
  ds1UNIT;
  ds1PORT Port;  /* Airport object */
} ds1UNIT_PORT;

#endif /* __U_SCENE_H_ */

/* END OF 'U_SCENE.H' FILE */
