/* FILENAME: ANIM.C
 * PROGRAMMER: DS1
 * DATE: 10.06.2016
 * PURPOSE: Animation system
 */

#include "anim.h"

/* Global animation context */
ds1ANIM DS1_Anim;

/* Animation system initialization function.
 * ARGUMENTS:
 *   - window:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID DS1_AnimInit( HWND hWnd )
{
  HDC hDC;

  memset(&DS1_Anim, 0, sizeof(ds1ANIM));
  DS1_Anim.hWnd = hWnd;
  hDC = GetDC(hWnd);
  DS1_Anim.hDC = CreateCompatibleDC(hDC);

  ReleaseDC(hWnd, hDC);
  DS1_Anim.NumOfUnits = 0;

} /* End of 'DS1_ANIMInit' function */

/* Animation system deinitialization function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID DS1_AnimClose( VOID )
{
  int i;

  for (i = 0; i < DS1_Anim.NumOfUnits; i++)
  {
    DS1_Anim.Units[i]->Close(DS1_Anim.Units[i], &DS1_Anim);
    free(DS1_Anim.Units[i]);
  }
  DS1_Anim.NumOfUnits = 0;

  DeleteObject(DS1_Anim.hFrame);
  DeleteDC(DS1_Anim.hDC);

} /* End of 'DS1_ANIMClose' function */

/* Animation system resize function.
 * ARGUMENTS:
 *   - width, height window size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID DS1_AnimResize( INT W, INT H )
{
  HDC hDC;

  DS1_Anim.W = W;
  DS1_Anim.H = H;

  if (DS1_Anim.hFrame != NULL)
    DeleteObject(DS1_Anim.hFrame);

  hDC = GetDC(DS1_Anim.hWnd);
  DS1_Anim.hFrame = CreateCompatibleBitmap(hDC, DS1_Anim.W, DS1_Anim.H);
  ReleaseDC(DS1_Anim.hWnd, hDC);
  SelectObject(DS1_Anim.hDC, DS1_Anim.hFrame);


} /* End of 'DS1_AnimResize' function */

/* Double buffer frame copy function.
 * ARGUMENTS:
 *   - window:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID DS1_AnimCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, DS1_Anim.W, DS1_Anim.H, DS1_Anim.hDC, 0, 0, SRCCOPY);
} /* End of 'DS1_AnimCopyFrame' function */

/* Animation system render function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID DS1_AnimRender( VOID )
{
  int i;
  HPEN hPen;
  HBRUSH hBr;

  /*** Obtain input system state ***/

  /* Keyboard */

  /* Mouse */

  /* Joystick */

  /*** Send response to all units ***/
  for (i = 0; i < DS1_Anim.NumOfUnits; i++)
    DS1_Anim.Units[i]->Response(DS1_Anim.Units[i], &DS1_Anim);

  /*** Clear frame ***/
  hPen = SelectObject(DS1_Anim.hDC, GetStockObject(DC_PEN));
  hBr = SelectObject(DS1_Anim.hDC, GetStockObject(DC_BRUSH));
  SetDCPenColor(DS1_Anim.hDC, RGB(0, 155, 0));
  SetDCBrushColor(DS1_Anim.hDC, RGB(100, 200, 150));
  Rectangle(DS1_Anim.hDC, 0, 0, DS1_Anim.W, DS1_Anim.H);
  SetDCPenColor(DS1_Anim.hDC, RGB(0, 0, 0));
  SetDCBrushColor(DS1_Anim.hDC, RGB(255, 255, 255));
  SelectObject(DS1_Anim.hDC, hPen);
  SelectObject(DS1_Anim.hDC, hBr);
  /*** Render all unit ***/
  for (i = 0; i < DS1_Anim.NumOfUnits; i++)
  {
    SelectObject(DS1_Anim.hDC, GetStockObject(DC_PEN));
    SelectObject(DS1_Anim.hDC, GetStockObject(DC_BRUSH));
    SetDCPenColor(DS1_Anim.hDC, RGB(0, 0, 0));
    SetDCBrushColor(DS1_Anim.hDC, RGB(255, 255, 255));
    DS1_Anim.Units[i]->Render(DS1_Anim.Units[i], &DS1_Anim);
  }
  /*. . .*/
} /* End of 'DS1_ANIMRender' function */

/* Animation system exit function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID DS1_AnimDoExit( VOID )
{
  DestroyWindow(DS1_Anim.hWnd);
} /* End of 'DS1_ANIMClose' function */

/* Animation system initialization function.
 * ARGUMENTS:
 *   - Animation parameters:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
VOID DS1_AnimAddUnit( ds1UNIT *Uni )
{
  if (DS1_Anim.NumOfUnits >= DS1_MAX_UNITS)
    return;
  DS1_Anim.Units[DS1_Anim.NumOfUnits++] = Uni;
  Uni->Init(Uni, &DS1_Anim);
} /* End of 'DS1_AnimAddUnit' function */

/* END OF 'ANIM.C' FILE */
