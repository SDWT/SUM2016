/* FILENAME: ANIM.C
 * PROGRAMMER: DS1
 * DATE: 10.06.2016
 * PURPOSE: Animation system
 */

#include <stdio.h>

#include "anim.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm")

#define DS1_GET_JOYSTICK_AXIS(A) \
  (2.0 * (ji.dw##A##pos - jc.w##A##min) / (jc.w##A##max - jc.w##A##min - 1) - 1)

/* Timer local data */
static UINT64
  DS1_StartTime,    /* Start program time */
  DS1_OldTime,      /* Time from program start to previous frame */
  DS1_OldTimeFPS,   /* Old time FPS measurement */
  DS1_PauseTime,    /* Time during pause period */
  DS1_TimePerSec,   /* Timer resolution */
  DS1_FrameCounter; /* Frames counter */

/* Global mouse wheel delta value */
INT DS1_MouseWheel = 0;

/* Global system info on display */
BOOL DS1_IsSysInfo = 0, DS1_IsKeyInfo = 0;

/* Global animation context */
ds1ANIM DS1_Anim;

static VOID DS1_ControlModule( VOID )
{
  /*CHAR StrBuf[200];*/
  FLT x = 0, y = 0, z = 0;
  static FLT jx = 0, jy = 0, jz = 0;
  static VEC tr = {0, 0, 3};
  /*
  if (DS1_IsSysInfo)
  {
    SetBkMode(DS1_Anim.hDC, TRANSPARENT);
    TextOut(DS1_Anim.hDC, 0, 0, StrBuf, sprintf(StrBuf, "Input info: "
      "Mx: %6d; Mdx: %6d; My: %6d; Mdy: %6d; Mz: %6d; Mdz: %6d; "
      "Jx: %5.3lf; Jy: %5.3lf; Jz: %5.3lf; Jr: %5.3lf; JPov: %2d.", 
      DS1_Anim.Mx, DS1_Anim.Mdx, DS1_Anim.My, DS1_Anim.Mdy, DS1_Anim.Mz, DS1_Anim.Mdz,
      DS1_Anim.JX, DS1_Anim.JY, DS1_Anim.JZ, DS1_Anim.JR, DS1_Anim.JPov));
    SetBkMode(DS1_Anim.hDC, OPAQUE);
  }
  if (DS1_IsKeyInfo)
  {
    INT j;
    SetBkMode(DS1_Anim.hDC, TRANSPARENT);
    for (j = 0; j < 256; j++)
    {
      sprintf(StrBuf, "KeyNum: %d - %d;", j, DS1_Anim.Keys[j]);
      TextOut(DS1_Anim.hDC, 120 * (j / 20), 100 + (j * 10 + 10) % 200, StrBuf, strlen(StrBuf));
    }
    SetBkMode(DS1_Anim.hDC, OPAQUE);
  }
  */
  if (DS1_Anim.Keys[VK_MENU] && DS1_Anim.KeysClick[VK_RETURN])
    DS1_FlipFullScreen();
  if (DS1_Anim.KeysClick[VK_ESCAPE])
    PostMessage(DS1_Anim.hWnd, WM_CLOSE, 0, 0);
  if (DS1_Anim.KeysClick[VK_F2])
    DS1_IsSysInfo = !DS1_IsSysInfo;
  if (DS1_Anim.KeysClick[VK_F3])
    DS1_IsKeyInfo = !DS1_IsKeyInfo;
  if (DS1_Anim.KeysClick['p'])
    DS1_Anim.IsPause = !DS1_Anim.IsPause;


  if (DS1_Anim.JPov == 1 || DS1_Anim.JPov == 2 || DS1_Anim.JPov == 8)
    z = -1;
  if (DS1_Anim.JPov == 3 || DS1_Anim.JPov == 2 || DS1_Anim.JPov == 4)
    x = 1;
  if (DS1_Anim.JPov == 4 || DS1_Anim.JPov == 5 || DS1_Anim.JPov == 6)
    z = 1;
  if (DS1_Anim.JPov == 7 || DS1_Anim.JPov == 8 || DS1_Anim.JPov == 6)  
    x = -1;
  tr = VecAddVec(tr, VecSet(x, y, z));
  jx = DS1_Anim.JX;
  jy = DS1_Anim.JY;
  /*MatrixTranslate(DS1_Anim.JX, DS1_Anim.JY, DS1_Anim.JZ);*/
  DS1_RndMatrView = MatrView(tr, VecSet(0, 0, 0), VecSet(0, 1, 0));
  /*DS1_RndMatrWorld = MatrMulMatr(DS1_RndMatrWorld, MatrMulMatr(, MatrixRotateX(jy)));*/
  

} /* End of 'DS1_ControlModule' function */


/* Animation system initialization function.
 * ARGUMENTS:
 *   - window:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID DS1_AnimInit( HWND hWnd )
{
  LARGE_INTEGER t;
  HDC hDC;

  memset(&DS1_Anim, 0, sizeof(ds1ANIM));
  DS1_Anim.hWnd = hWnd;
  hDC = GetDC(hWnd);
  DS1_Anim.hDC = CreateCompatibleDC(hDC);

  ReleaseDC(hWnd, hDC);
  DS1_Anim.NumOfUnits = 0;

  /* Timer initialization */
  QueryPerformanceFrequency(&t);
  DS1_TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  DS1_StartTime = DS1_OldTime = DS1_OldTimeFPS = t.QuadPart;
  DS1_PauseTime = 0;

  DS1_RndMatrWorld = MatrixIdentity();
  DS1_RndMatrProj = MatrFrustum(-1, 1, -1, 1, 1, 100);
  DS1_RndMatrView = MatrView(VecSet(0, 0, 3), VecSet(0, 0, 0), VecSet(0, 1, 0));
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

  DS1_RndSetProj();
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
  LARGE_INTEGER t;
  HPEN hPen;
  HBRUSH hBr;
  POINT pt;
  /*** Obtain input system state ***/

  /*** Handle timer ***/
  DS1_FrameCounter++;
  QueryPerformanceCounter(&t);
  /* Global time */
  DS1_Anim.GlobalTime = (DBL)(t.QuadPart - DS1_StartTime) / DS1_TimePerSec;
  DS1_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - DS1_OldTime) / DS1_TimePerSec;
  /* Time with pause */
  if (DS1_Anim.IsPause)
  {
    DS1_Anim.DeltaTime = 0;
    DS1_PauseTime += t.QuadPart - DS1_OldTime;
  }
  else
  {
    DS1_Anim.Time = (DBL)(t.QuadPart - DS1_StartTime - DS1_PauseTime) / DS1_TimePerSec;
    DS1_Anim.DeltaTime = DS1_Anim.GlobalDeltaTime;
  }
  /* FPS */
  if (t.QuadPart - DS1_OldTimeFPS > DS1_TimePerSec)
  {
    CHAR str[100];

    DS1_Anim.FPS = DS1_FrameCounter * DS1_TimePerSec / (DBL)(t.QuadPart - DS1_OldTimeFPS);
    DS1_OldTimeFPS = t.QuadPart;
    DS1_FrameCounter = 0;
    sprintf(str, "FPS: %.5f", DS1_Anim.FPS);
    SetWindowText(DS1_Anim.hWnd, str);
  }
  DS1_OldTime = t.QuadPart;

  /* Mouse */
  GetCursorPos(&pt);
  ScreenToClient(DS1_Anim.hWnd, &pt);
  DS1_Anim.Mdx = pt.x - DS1_Anim.Mx;
  DS1_Anim.Mdy = pt.y - DS1_Anim.My;
  DS1_Anim.Mx = pt.x;
  DS1_Anim.My = pt.y;
  DS1_Anim.Mdz = DS1_MouseWheel;
  DS1_Anim.Mz += DS1_MouseWheel;
  DS1_MouseWheel = 0;

  /* Keyboard */
  GetKeyboardState(DS1_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    DS1_Anim.Keys[i] >>= 7;
    if (!DS1_Anim.KeysOld[i] && DS1_Anim.Keys[i])
      DS1_Anim.KeysClick[i] = TRUE;
    else
      DS1_Anim.KeysClick[i] = FALSE;
  }
  memcpy(DS1_Anim.KeysOld, DS1_Anim.Keys, 256);

  /* Joystick */
  if (joyGetNumDevs() > 0)
  {
    JOYCAPS jc;

    /* Get joystick info */
    if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(JOYCAPS))== JOYERR_NOERROR)
    {
      JOYINFOEX ji;
      ji.dwSize = sizeof(JOYINFOEX);
      ji.dwFlags = JOY_RETURNALL;
      if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      {
        /* Buttons */
        for (i = 0; i < 32; i++)
          DS1_Anim.JBut[i] = (ji.dwButtons >> i) & 1;
        /* Axes */
        DS1_Anim.JX = (2.0 * (ji.dwXpos - jc.wXmin) / (jc.wXmax - jc.wXmin - 1) - 1);
        DS1_Anim.JX = DS1_GET_JOYSTICK_AXIS(X);
        DS1_Anim.JY = DS1_GET_JOYSTICK_AXIS(Y);
        DS1_Anim.JZ = DS1_GET_JOYSTICK_AXIS(Z);
        DS1_Anim.JR = DS1_GET_JOYSTICK_AXIS(R);
        /* Point of view */
        DS1_Anim.JPov = ji.dwPOV == 0xFFFF ? 0 : ji.dwPOV / 4500 + 1;
      }
    }
  }
  
  DS1_ControlModule();

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

/* Set/reset full screen mode function */
VOID DS1_FlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (IsFullScreen)
  {
    /* restore window size */
    SetWindowPos(DS1_Anim.hWnd, HWND_TOP,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Set full screen size to window */
    HMONITOR hmon;
    MONITORINFOEX moninfo;
    RECT rc;

    /* Store window old size */
    GetWindowRect(DS1_Anim.hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(DS1_Anim.hWnd, MONITOR_DEFAULTTONEAREST);

    /* Obtain monitor info */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* Set window new size */
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(DS1_Anim.hWnd, GWL_STYLE), FALSE);

    SetWindowPos(DS1_Anim.hWnd, HWND_TOPMOST,
      rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
} /* End of 'FlipFullScreen' function */


/* END OF 'ANIM.C' FILE */
