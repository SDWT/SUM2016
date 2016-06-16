/* FILENAME: U_SCENE.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <string.h>

#include "u_scene.h"
#include "units.h"
#include "anim.h"

typedef struct
{
  ds1UNIT;
  CHAR *FileName;
  VEC Pos;
  /*ds1OBJ Obj;*/
  ds1UNIT_PORT *Port;
  ds1UNIT_PLANE *Planes[3];
} ds1UNIT_SCENE;


/* Unit scene initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_SCENE *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_SCENE *Uni, ds1ANIM *Ani )
{
  /*Uni->Pos = VecSet(10 * Rnd1(), 10 * Rnd1(), 10 * Rnd1());*/
  /*DS1_AnimAddUnit(Uni->Port = DS1_UnitCreatePort("modela\\radar.g3d"));*/
  DS1_AnimAddUnit(Uni->Planes[0] = DS1_UnitCreatePlane("modela\\A380.g3d"));
  Uni->Planes[0]->Plane.Pos = VecSet(0, 7, 0);
  /*DS1_RndObjLoad(&Uni->Obj, Uni->FileName);*/
} /* End of 'DS1_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT_SCENE *Uni, ds1ANIM *Ani )
{
  /*DS1_RndObjFree(&Uni->Obj);*/
} /* End of 'DS1_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_SCENE *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT_SCENE *Uni, ds1ANIM *Ani )
{
} /* End of 'DS1_UnitRender' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitResponse( ds1UNIT_SCENE *Uni, ds1ANIM *Ani )
{

} /* End of 'DS1_UnitResponse' function */

/* Unit scene creation function.
 * ARGUMENTS: 
 *   - Scene file:
 *     CHAR *FileName;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateScene( VOID )
{
  ds1UNIT_SCENE *Uni;

  if ((Uni = (ds1UNIT_SCENE *)DS1_AnimUnitCreate(sizeof(ds1UNIT_SCENE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)DS1_UnitInit;
  Uni->Render = (VOID *)DS1_UnitRender;
  Uni->Response = (VOID *)DS1_UnitResponse;
  Uni->Close = (VOID *)DS1_UnitClose;
  /*Uni->FileName = FileName;*/
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreateScene' function */

/* END OF 'U_SCENE.C' FILE */
