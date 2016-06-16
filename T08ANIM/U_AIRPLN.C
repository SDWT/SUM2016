/* FILENAME: U_AIRPLN.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Airplane unit drawing module
 */

#include <string.h>

#include "u_scene.h"
#include "anim.h"

/* Unit plane initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_PLANE *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_PLANE *Uni, ds1ANIM *Ani )
{
  Uni->Plane.Pos = VecSet(10 * Rnd1(), 10 * Rnd1(), 10 * Rnd1());
  DS1_RndObjLoad(&Uni->Plane.Obj, Uni->Plane.FileName);
  DS1_Scale = 0.01;
} /* End of 'DS1_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT_PLANE *Uni, ds1ANIM *Ani )
{
  DS1_RndObjFree(&Uni->Plane.Obj);
} /* End of 'DS1_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_PLANE *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT_PLANE *Uni, ds1ANIM *Ani )
{
  DS1_RndMatrWorld = MatrMulMatr(MatrMulMatr(DS1_RndMatrWorld, MatrixScale(DS1_Scale, DS1_Scale, DS1_Scale)), MatrRotateX(-90));
  /*DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, MatrixTranslate(Uni->Plane.Pos.X, Uni->Plane.Pos.Y, Uni->Plane.Pos.Z));*/
  /*MatrMulMatr(MatrixScale(0.01, 0.01, 0.01), MatrixTranslate(Uni->Pos.X, Uni->Pos.Y, Uni->Pos.Z));*/
  DS1_RndObjDraw(&Uni->Plane.Obj);
} /* End of 'DS1_UnitRender' function */

/* Unit plane creation function.
 * ARGUMENTS: 
 *   - Plane file:
 *     CHAR *FileName;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreatePlane( CHAR *FileName )
{
  ds1UNIT_PLANE *Uni;

  if ((Uni = (ds1UNIT_PLANE *)DS1_AnimUnitCreate(sizeof(ds1UNIT_PLANE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)DS1_UnitInit;
  Uni->Render = (VOID *)DS1_UnitRender;
  Uni->Close = (VOID *)DS1_UnitClose;
  Uni->Plane.FileName = FileName;
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreatePlane' function */


/* END OF 'U_AIRPLN.C' FILE */
