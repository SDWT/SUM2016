/* FILENAME: CUBE.C
 * PROGRAMMER: DS1
 * DATE: 14.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <string.h>

#include "anim.h"

typedef struct
{
  ds1UNIT;
  ds1PRIM Pr;
} ds1UNIT_CUBE;

/* Unit cube initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_CUBE *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_CUBE *Uni, ds1ANIM *Ani )
{
  DS1_RndPrimLoad(&Uni->Pr, "modela\\cow.g3d");

} /* End of 'DS1_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT_CUBE *Uni, ds1ANIM *Ani )
{
  DS1_RndPrimFree(&Uni->Pr);
} /* End of 'DS1_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_CUBE *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT_CUBE *Uni, ds1ANIM *Ani )
{
  /*DS1_RndMatrWorld = MatrixScale(1, 1, 1);/*MatrixRotate(Ani->Time, 0, 1, 0);,);*/
  DS1_RndPrimDraw(&Uni->Pr);
} /* End of 'DS1_UnitRender' function */

/* Unit cube creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateCube( VOID )
{
  ds1UNIT_CUBE *Uni;

  if ((Uni = (ds1UNIT_CUBE *)DS1_AnimUnitCreate(sizeof(ds1UNIT_CUBE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)DS1_UnitInit;
  Uni->Render = (VOID *)DS1_UnitRender;
  Uni->Close = (VOID *)DS1_UnitClose;
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreateCube' function */


/* END OF 'CUBE.C' FILE */
