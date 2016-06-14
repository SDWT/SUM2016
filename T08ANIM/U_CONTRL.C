/* FILENAME: SPRITE.C
 * PROGRAMMER: DS1
 * DATE: 14.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <string.h>

#include "anim.h"

typedef struct
{
  ds1UNIT;
  INT X, Y;
  CHAR FileAND[100], FileXOR[100];
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

} /* End of 'DS1_UnitInit' function */

static VOID DS1_UnitResponse( ds1UNIT_CONTROL *Uni, ds1ANIM *Ani )
{
  /*CHAR StrBuf[200];*/
  FLT x = 0, y = 0, z = 0;
  static FLT jx = 0, jy = 0, jz = 0;
  static VEC tr = {0, 0, 3};
  /*
  if (DS1_IsSysInfo)
  {
    SetBkMode(Ani->hDC, TRANSPARENT);
    TextOut(Ani->hDC, 0, 0, StrBuf, sprintf(StrBuf, "Input info: "
      "Mx: %6d; Mdx: %6d; My: %6d; Mdy: %6d; Mz: %6d; Mdz: %6d; "
      "Jx: %5.3lf; Jy: %5.3lf; Jz: %5.3lf; Jr: %5.3lf; JPov: %2d.", 
      Ani->Mx, Ani->Mdx, Ani->My, Ani->Mdy, Ani->Mz, Ani->Mdz,
      Ani->JX, Ani->JY, Ani->JZ, Ani->JR, Ani->JPov));
    SetBkMode(Ani->hDC, OPAQUE);
  }
  if (DS1_IsKeyInfo)
  {
    INT j;
    SetBkMode(Ani->hDC, TRANSPARENT);
    for (j = 0; j < 256; j++)
    {
      sprintf(StrBuf, "KeyNum: %d - %d;", j, Ani->Keys[j]);
      TextOut(Ani->hDC, 120 * (j / 20), 100 + (j * 10 + 10) % 200, StrBuf, strlen(StrBuf));
    }
    SetBkMode(Ani->hDC, OPAQUE);
  }
  */
  if (Ani->Keys[VK_MENU] && Ani->KeysClick[VK_RETURN])
    DS1_FlipFullScreen();
  if (Ani->KeysClick[VK_ESCAPE])
    PostMessage(Ani->hWnd, WM_CLOSE, 0, 0);
  if (Ani->KeysClick[VK_F2])
    DS1_IsSysInfo = !DS1_IsSysInfo;
  if (Ani->KeysClick[VK_F3])
    DS1_IsKeyInfo = !DS1_IsKeyInfo;
  if (Ani->KeysClick['p'])
    Ani->IsPause = !Ani->IsPause;


  if (Ani->JPov == 1 || Ani->JPov == 2 || Ani->JPov == 8)
    z = -1;
  if (Ani->JPov == 3 || Ani->JPov == 2 || Ani->JPov == 4)
    x = 1;
  if (Ani->JPov == 4 || Ani->JPov == 5 || Ani->JPov == 6)
    z = 1;
  if (Ani->JPov == 7 || Ani->JPov == 8 || Ani->JPov == 6)  
    x = -1;
  tr = VecAddVec(tr, VecSet(x, y, z));
  jx = Ani->JX;
  jy = Ani->JY;
  /*MatrixTranslate(Ani->JX, Ani->JY, Ani->JZ);*/
  DS1_RndMatrView = MatrView(tr, VecSet(0, 0, 0), VecSet(0, 1, 0));
  /*DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, MatrMulMatr(, MatrixRotateX(jy)));*/
  

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
  static INT X = 0, Y = 0;

  X += 3 * (INT)Ani->JZ;
  Y += 3 * (INT)Ani->JR;
  if (Ani->KeysClick['0'])
    Y = X = 0;

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
  Uni->Response = (VOID *)DS1_UnitResponse;
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreateControl' function */


/* END OF 'SPRITE.C' FILE */
