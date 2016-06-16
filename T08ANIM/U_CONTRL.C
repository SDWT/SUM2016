/* FILENAME: SPRITE.C
 * PROGRAMMER: DS1
 * DATE: 15.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <string.h>

#include "anim.h"

typedef struct
{
  ds1UNIT;
  VEC Pos;
} ds1UNIT_CONTROL;

/* Global system info on display */
BOOL DS1_IsSysInfo = 0, DS1_IsKeyInfo = 0;

/* Unit ball initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_BALL *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_CONTROL *Uni, ds1ANIM *Ani )
{
  Uni->Pos = VecSet(0, 0, -40);

} /* End of 'DS1_UnitInit' function */

static VOID DS1_UnitResponse( ds1UNIT_CONTROL *Uni, ds1ANIM *Ani )
{
  /*CHAR StrBuf[200];*/
  FLT x = 0, y = 0, z = 0;
  DBL r;
  static FLT jx = 0, jy = 0, jz = 0;
  static VEC tr = {0, 0, 3}, at = {0, 0, 0}, up1 = {0, 1, 0}, Zero = {0, 0, 0};

  if (Ani->Keys[VK_MENU] && Ani->KeysClick[VK_RETURN])
    DS1_FlipFullScreen();
  if (Ani->KeysClick[VK_ESCAPE])
    PostMessage(Ani->hWnd, WM_CLOSE, 0, 0);
  if (Ani->KeysClick[VK_F2])
    DS1_IsSysInfo = !DS1_IsSysInfo;
  if (Ani->KeysClick[VK_F3])
    DS1_IsKeyInfo = !DS1_IsKeyInfo;
  if (Ani->KeysClick['P'])
    Ani->IsPause = !Ani->IsPause;
  if (Ani->KeysClick[VK_F7])
    DS1_IsNor = !DS1_IsNor;
  if (Ani->KeysClick[VK_F8])
    DS1_IsPart = !DS1_IsPart;

  if (Ani->KeysClick['A'])
    Zero.X += 10000 * DS1_Scale;
  if (Ani->KeysClick['D'] && Zero.X > 0)
    Zero.X -= 10000 * DS1_Scale;
  if (Ani->KeysClick[VK_F5])
    DS1_Scale /= 10;
  if (Ani->KeysClick[VK_F6])
    DS1_Scale *= 10;

  if (Ani->KeysClick['R'])
  {
    DS1_RndShaderFree(DS1_RndPrg);
    DS1_RndPrg = DS1_RndShaderLoad("a");
  }
  if (Ani->JPov == 1 || Ani->JPov == 2 || Ani->JPov == 8)
    z = -1;
  else if (Ani->JPov == 4 || Ani->JPov == 5 || Ani->JPov == 6)
    z = 1;
  if (Ani->JPov == 3 || Ani->JPov == 2 || Ani->JPov == 4)
    x = 1;
  else if (Ani->JPov == 7 || Ani->JPov == 8 || Ani->JPov == 6)
    x = -1;
  jx = Ani->JX;
  jy = Ani->JY;
  /*MatrixTranslate(Ani->JX, Ani->JY, Ani->JZ);*/
  /*DS1_RndMatrView = MatrView(tr, VecSet(0, 0, 0), VecSet(0, 1, 0));*/
  /*DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, MatrMulMatr(, MatrixRotateX(jy)));*/
  

  Uni->Pos = VecAddVec(Uni->Pos, VecSet(x, y, z));
  /* Uni->Pos.Y += Ani->JY * Ani->GlobalDeltaTime; */
  Uni->Pos = VecTransform43(Uni->Pos, MatrRotateX(59 * Ani->JY * Ani->GlobalDeltaTime));
  Uni->Pos = VecTransform43(Uni->Pos, MatrRotate(59 * Ani->JX * Ani->GlobalDeltaTime,
                 VecNormalize(VecCrossVec(VecNormalize(VecSubVec(Zero, Uni->Pos)), up1))));

  if (Ani->Keys[VK_LBUTTON])
  {
    Uni->Pos = VecTransform43(Uni->Pos, MatrRotateY(59 * Ani->Mdx * Ani->GlobalDeltaTime));
    Uni->Pos = VecTransform43(Uni->Pos, MatrRotate(59 * Ani->Mdy * Ani->GlobalDeltaTime,
                 VecNormalize(VecCrossVec(VecNormalize(VecSubVec(Zero, Uni->Pos)), up1))));
  }

  Uni->Pos = VecTransform43(Uni->Pos, MatrRotateY(59 * Ani->Keys[VK_RIGHT] * Ani->GlobalDeltaTime));
  Uni->Pos = VecTransform43(Uni->Pos, MatrRotateY(-59 * Ani->Keys[VK_LEFT] * Ani->GlobalDeltaTime));

  r = VecLen(Uni->Pos);
  Uni->Pos = VecMullNum(Uni->Pos, (r + -Ani->Mdz * Ani->GlobalDeltaTime) / r);

  DS1_RndMatrView = MatrView(VecAddVec(Uni->Pos, Zero), Zero, up1);

} /* End of 'DS1_ControlModule' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT_CONTROL *Uni, ds1ANIM *Ani )
{
} /* End of 'DS1_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_BALL *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT_CONTROL *Uni, ds1ANIM *Ani )
{

} /* End of 'DS1_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateControl( VOID )
{
  ds1UNIT_CONTROL *Uni;

  if ((Uni = (ds1UNIT_CONTROL *)DS1_AnimUnitCreate(sizeof(ds1UNIT_CONTROL))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)DS1_UnitInit;
  Uni->Response = (VOID *)DS1_UnitResponse;
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreateControl' function */


/* END OF 'SPRITE.C' FILE */
