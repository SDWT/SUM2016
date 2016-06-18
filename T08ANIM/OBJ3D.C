/* FILENAME: OBJ3D.C
 * PROGRAMMER: DS1
 * DATE: 18.06.2016
 * PURPOSE: Object functions
 */

#include "anim.h"

/* Object create function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjCreate( ds1OBJ *Obj )
{
  memset(Obj, 0, sizeof(ds1OBJ));
  Obj->M = MatrixIdentity();
} /* End of 'DS1_RndObjCreate' function */

/* Object draw function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjDraw( ds1OBJ *Obj )
{
  INT i;
  MATR MSave;

  MSave = DS1_RndMatrWorld;
  DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, Obj->M);
  for (i = 0; i < Obj->NumOfPrims; i++)
    DS1_RndPrimDraw(&Obj->Prims[i]);
  DS1_RndMatrWorld = MSave;
} /* End of 'DS1_RndObjDraw' function */

/* Object free function.
 * ARGUMENTS:
 *   - object structure pointer:
 *       ds1OBJ *Obj;
 * RETURNS: None.
 */
VOID DS1_RndObjFree( ds1OBJ *Obj )
{
  INT i;

  for (i = 0; i < Obj->NumOfPrims; i++)
    DS1_RndPrimFree(&Obj->Prims[i]);
  free(Obj->Prims);
  memset(Obj, 0, sizeof(ds1OBJ));
} /* End of 'DS1_RndObjFree' function */

/* END OF 'OBJ3D.C' FILE */
