/* FILENAME: CUBE.C
 * PROGRAMMER: DS1
 * DATE: 07.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <string.h>

#include "anim.h"

typedef struct
{
  ds1UNIT;
} ds1UNIT_CUBE;

VEC CubeP[] =
{
  {-1, -1,  1},
  { 1, -1,  1},
  { 1, -1, -1},
  {-1, -1, -1},
  {-1,  1,  1},
  { 1,  1,  1},
  { 1,  1, -1},
  {-1,  1, -1}
};

INT CubeE[][2] =
{
  {0, 1}, {1, 2}, {2, 3}, {3, 0},
  {4, 5}, {5, 6}, {6, 7}, {7, 4},
  {0, 4}, {1, 5}, {2, 6}, {3, 7}

  /*{0, 2}, {2, 3}, {3, 1}, {1, 0},
  {4, 6}, {6, 7}, {7, 5}, {5, 4},
  {0, 4}, {1, 5}, {2, 6}, {3, 7}*/

  /*{0, 1}, {2, 3}, {1, 7}, {3, 0},
  {4, 5}, {6, 7}, {5, 6}, {7, 4},
  {0, 4}, {1, 5}, {2, 6}, {3, 7}*/
};
ds1PRIM Cube =
{
  CubeP, sizeof(CubeP) / sizeof(CubeP[0]),
  CubeE, sizeof(CubeE) / sizeof(CubeE[0])
};

/* Unit cube initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_CUBE *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_CUBE *Uni, ds1ANIM *Ani )
{



} /* End of 'VG4_UnitInit' function */

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
  DS1_RndPrimDraw(&Cube);
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
