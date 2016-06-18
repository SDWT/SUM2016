/* FILENAME: U_MODEL.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <string.h>

#include "anim.h"

typedef struct
{
  ds1UNIT;
  CHAR *FileName;
  VEC Pos;
  ds1OBJ Obj;
} ds1UNIT_MODEL;

/* Unit model initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_MODEL *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_MODEL *Uni, ds1ANIM *Ani )
{
  ds1GRID G;
  Uni->Pos = VecSet(10 * Rnd1(), 10 * Rnd1(), 10 * Rnd1());
  /*DS1_RndObjLoad(&Uni->Obj, Uni->FileName);*/
  DS1_GridCreatePlane(&G, 5, 10, VecSet(1, 1, 0), VecSet(0, 1, 1));/**/
  DS1_GridCreateObj(&G, &Uni->Obj, -1);
  DS1_GridFree(&G);
} /* End of 'DS1_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT_MODEL *Uni, ds1ANIM *Ani )
{
  DS1_RndObjFree(&Uni->Obj);
} /* End of 'DS1_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_MODEL *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT_MODEL *Uni, ds1ANIM *Ani )
{
  DS1_RndMatrWorld = MatrMulMatr(MatrixScale(0.01, 0.01, 0.01), MatrRotateX(-90));
  /*MatrMulMatr(MatrixScale(0.01, 0.01, 0.01), MatrixTranslate(Uni->Pos.X, Uni->Pos.Y, Uni->Pos.Z));*/
  DS1_RndObjDraw(&Uni->Obj);
} /* End of 'DS1_UnitRender' function */

/* Unit model creation function.
 * ARGUMENTS: 
 *   - Model file:
 *     CHAR *FileName;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateModel( CHAR *FileName )
{
  ds1UNIT_MODEL *Uni;

  if ((Uni = (ds1UNIT_MODEL *)DS1_AnimUnitCreate(sizeof(ds1UNIT_MODEL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)DS1_UnitInit;
  Uni->Render = (VOID *)DS1_UnitRender;
  Uni->Close = (VOID *)DS1_UnitClose;
  Uni->FileName = FileName;
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreateModel' function */


/* END OF 'U_MODEL.C' FILE */
