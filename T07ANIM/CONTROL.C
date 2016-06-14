/* FILENAME: SPRITE.C
 * PROGRAMMER: DS1
 * DATE: 07.06.2016
 * PURPOSE: Sprite unit drawing module
 */

#include <string.h>

#include "anim.h"

typedef struct
{
  ds1UNIT;
  BITMAP Bm;
  HBITMAP hBmAND, hBmXOR;
  HDC hDCAND, hDCXOR;
  INT X, Y;
  CHAR FileAND[100], FileXOR[100];
} ds1UNIT_SPRITE;

/* Unit ball initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_BALL *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_SPRITE *Uni, ds1ANIM *Ani )
{
  
  Uni->hBmAND = LoadImage(NULL, Uni->FileAND, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  Uni->hDCAND = CreateCompatibleDC(Ani->hDC);
  SelectObject(Uni->hDCAND, Uni->hBmAND);
  GetObject(Uni->hBmAND, sizeof(Uni->Bm), &Uni->Bm);;

  Uni->hBmXOR = LoadImage(NULL, Uni->FileXOR, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  Uni->hDCXOR = CreateCompatibleDC(Ani->hDC);
  SelectObject(Uni->hDCXOR, Uni->hBmXOR);

} /* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT_SPRITE *Uni, ds1ANIM *Ani )
{
  DeleteObject(Uni->hBmAND);
  DeleteObject(Uni->hDCAND);
  DeleteObject(Uni->hBmXOR);
  DeleteObject(Uni->hDCXOR);
} /* End of 'DS1_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_BALL *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT_SPRITE *Uni, ds1ANIM *Ani )
{
  static INT X = 0, Y = 0;

  X += 3 * (INT)Ani->JZ;
  Y += 3 * (INT)Ani->JR;
  if (Ani->KeysClick['0'])
    Y = X = 0;
  BitBlt(Ani->hDC, Uni->X + X, Uni->Y + Y, Uni->Bm.bmWidth, Uni->Bm.bmHeight, Uni->hDCAND, 0, 0, SRCAND);
  BitBlt(Ani->hDC, Uni->X + X, Uni->Y + Y, Uni->Bm.bmWidth, Uni->Bm.bmHeight, Uni->hDCXOR, 0, 0, SRCINVERT);
} /* End of 'DS1_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateSprite( INT X, INT Y, CHAR *FileAnd, CHAR *FileXor )
{
  ds1UNIT_SPRITE *Uni;

  if ((Uni = (ds1UNIT_SPRITE *)DS1_AnimUnitCreate(sizeof(ds1UNIT_SPRITE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)DS1_UnitInit;
  Uni->Render = (VOID *)DS1_UnitRender;
  Uni->Close = (VOID *)DS1_UnitClose;
  Uni->X = X;
  Uni->Y = Y;
  strcpy(Uni->FileAND, FileAnd);
  strcpy(Uni->FileXOR, FileXor);
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreateBall' function */


/* END OF 'SPRITE.C' FILE */
