/* FILENAME: ANIM.C
 * PROGRAMMER: DS1
 * DATE: 10.06.2016
 * PURPOSE: Unit base
 */

#include "anim.h"

/* default animation object function */

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT *Uni, ds1ANIM *Ani )
{
} /* End of 'DS1_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT *Uni, ds1ANIM *Ani )
{
} /* End of 'DS1_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitResponse( ds1UNIT *Uni, ds1ANIM *Ani )
{
} /* End of 'DS1_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT *Uni, ds1ANIM *Ani )
{
} /* End of 'DS1_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_AnimUnitCreate( INT Size )
{
  ds1UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(ds1UNIT) ||
      (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);
  /* Setup unit methods */
  Uni->Init = DS1_UnitInit;
  Uni->Close = DS1_UnitClose;
  Uni->Response = DS1_UnitResponse;
  Uni->Render = DS1_UnitRender;
  return Uni;
} /* End of 'DS1_AnimUnitCreate' function */

/* END OF 'ANIM.C' FILE */
