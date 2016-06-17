/* FILENAME: U_PORT.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <string.h>

#include "u_scene.h"
#include "anim.h"

/* Unit port initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_PORT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_PORT *Uni, ds1ANIM *Ani )
{
  Uni->Port.Pos = VecSet(10 * Rnd1(), 10 * Rnd1(), 10 * Rnd1());
  DS1_RndObjLoad(&Uni->Port.Obj, Uni->Port.FileNameObj);
  DS1_RndObjLoad(&Uni->Port.RWI, Uni->Port.FileNameRWI);
  DS1_RndObjLoad(&Uni->Port.RWT, Uni->Port.FileNameRWT);
  DS1_RndObjLoad(&Uni->Port.RWO, Uni->Port.FileNameRWO);
  DS1_Scale = 0.5;
} /* End of 'DS1_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT_PORT *Uni, ds1ANIM *Ani )
{
  DS1_RndObjFree(&Uni->Port.Obj);
  DS1_RndObjFree(&Uni->Port.RWI);
  DS1_RndObjFree(&Uni->Port.RWT);
  DS1_RndObjFree(&Uni->Port.RWO);
} /* End of 'DS1_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_PORT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT_PORT *Uni, ds1ANIM *Ani )
{
  FLT ScaleA = 1, Sd = 100, ScaleB = 4;
  DS1_RndMatrWorld = MatrixScale(DS1_Scale, DS1_Scale, DS1_Scale);
  /*MatrMulMatr(MatrixScale(0.01, 0.01, 0.01), MatrixTranslate(Uni->Pos.X, Uni->Pos.Y, Uni->Pos.Z));*/
  DS1_RndObjDraw(&Uni->Port.Obj);

  DS1_RndMatrWorld = MatrixScale(ScaleA * ScaleB, 1, ScaleA);
  DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, MatrixTranslate(Sd * ScaleA * (ScaleB - 0.5), 0, -Sd *(ScaleA +  ScaleA)));
  DS1_RndObjDraw(&Uni->Port.RWI);

  DS1_RndMatrWorld = MatrixScale(ScaleA / 2, 0, ScaleA);/*MatrixTranslate(-Sd * ScaleA * 1.5, 0, -Sd * ScaleA);*/
  DS1_RndObjDraw(&Uni->Port.RWI);

  DS1_RndMatrWorld = MatrixScale(ScaleA * ScaleB, 1, ScaleA);
  DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, MatrixTranslate(Sd * ScaleA * (ScaleB - 0.5), 0, Sd *(ScaleA +  ScaleA)));
  DS1_RndObjDraw(&Uni->Port.RWI);
  /*
  DS1_RndMatrWorld = MatrixScale(ScaleA * 5, ScaleA, ScaleA);
  DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, MatrixTranslate(-Sd * ScaleA * 1.5, 0, -Sd * ScaleA));
  DS1_RndObjDraw(&Uni->Port.RWI);
  */
  /*
  DS1_RndMatrWorld = MatrixScale(ScaleA, ScaleA, ScaleA * 2);
  DS1_RndObjDraw(&Uni->Port.RWT);

  DS1_RndMatrWorld = MatrixScale(ScaleA * 5, ScaleA, ScaleA);
  DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, MatrixTranslate(-Sd * ScaleA * 1.25, 0, Sd * ScaleA));
  DS1_RndObjDraw(&Uni->Port.RWO);
  */
} /* End of 'DS1_UnitRender' function */

/* Unit port creation function.
 * ARGUMENTS: 
 *   - Port file:
 *     CHAR *FileNameObj; 
 *   - Runway landing file:
 *     CHAR *FileNameRWI;
 *   - Runway taxi file:
 *     CHAR *FileNameRWT;
 *   - Runway takeoff file:
 *     CHAR *FileNameRWO;
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreatePort( CHAR *FileNameObj, CHAR *FileNameRWI, CHAR *FileNameRWT, CHAR *FileNameRWO )
{
  ds1UNIT_PORT *Uni;

  if ((Uni = (ds1UNIT_PORT *)DS1_AnimUnitCreate(sizeof(ds1UNIT_PORT))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)DS1_UnitInit;
  Uni->Close = (VOID *)DS1_UnitClose;
  Uni->Render = (VOID *)DS1_UnitRender;
  Uni->Port.FileNameObj = FileNameObj;
  Uni->Port.FileNameRWI = FileNameRWI;
  Uni->Port.FileNameRWT = FileNameRWT;
  Uni->Port.FileNameRWO = FileNameRWO;
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreatePort' function */


/* END OF 'U_PORT.C' FILE */
