/* FILENAME: ANIM.C
 * PROGRAMMER: DS1
 * DATE: 14.06.2016
 * PURPOSE: Animation system
 */

#include <stdio.h>

#include "anim.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")


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
  INT i;
  PIXELFORMATDESCRIPTOR pfd = {0};
  LARGE_INTEGER t;

  memset(&DS1_Anim, 0, sizeof(ds1ANIM));
  /* Store window and create memory device context */
  DS1_Anim.hWnd = hWnd;
  DS1_Anim.hDC = GetDC(hWnd);
  DS1_Anim.NumOfUnits = 0;

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(DS1_Anim.hDC, &pfd);
  DescribePixelFormat(DS1_Anim.hDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(DS1_Anim.hDC, i, &pfd);

  /* OpenGL init: setup rendering context */
  DS1_Anim.hGLRC = wglCreateContext(DS1_Anim.hDC);
  wglMakeCurrent(DS1_Anim.hDC, DS1_Anim.hGLRC);

  /* OpenGL init: setup extensions: GLEW library */
  if (glewInit() != GLEW_OK ||
      !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader))
  {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(DS1_Anim.hGLRC);
    ReleaseDC(DS1_Anim.hWnd, DS1_Anim.hDC);
    exit(0);
  }

  /* Timer initialization */
  QueryPerformanceFrequency(&t);
  DS1_TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  DS1_StartTime = DS1_OldTime = DS1_OldTimeFPS = t.QuadPart;
  DS1_PauseTime = 0;

  DS1_RndMatrWorld = MatrixIdentity();
  DS1_RndMatrProj = MatrFrustum(-1, 1, -1, 1, 1, 100);
  DS1_RndMatrView = MatrView(VecSet(0, 0, 3), VecSet(0, 0, 0), VecSet(0, 1, 0));

  /* OpenGL specific initialization */
  glClearColor((FLT)100 / 255, (FLT)200 / 255, (FLT)150 / 255, 1);
  /*
  RGB(100, 200, 150)
  glClearColor(0.3, 0.5, 0.7, 1);
  */
  glEnable(GL_DEPTH_TEST);
  /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
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

  /* Delete rendering context */
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(DS1_Anim.hGLRC);
  ReleaseDC(DS1_Anim.hWnd, DS1_Anim.hDC);
} /* End of 'DS1_ANIMClose' function */

/* Animation system resize function.
 * ARGUMENTS:
 *   - width, height window size:
 *       INT W, H;
 * RETURNS: None.
 */
VOID DS1_AnimResize( INT W, INT H )
{
  DS1_Anim.W = W;
  DS1_Anim.H = H;

  glViewport(0, 0, W, H);
  DS1_RndSetProj();
} /* End of 'DS1_AnimResize' function */

/* Double buffer frame copy function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID DS1_AnimCopyFrame( VOID )
{
  SwapBuffers(DS1_Anim.hDC);
} /* End of 'DS1_AnimCopyFrame' function */

/* Animation system render function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
VOID DS1_AnimRender( VOID )
{
  int i;
  LARGE_INTEGER t;
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

  /*** Send response to all units ***/
  for (i = 0; i < DS1_Anim.NumOfUnits; i++)
    DS1_Anim.Units[i]->Response(DS1_Anim.Units[i], &DS1_Anim);

  /*** Clear frame ***/
  /* Clear background */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*** Render all units ***/
  for (i = 0; i < DS1_Anim.NumOfUnits; i++)
  {
    DS1_RndMatrWorld = MatrixIdentity();
    DS1_Anim.Units[i]->Render(DS1_Anim.Units[i], &DS1_Anim);
  }

  glLoadMatrixf(DS1_RndMatrView.A[0]);
  /* Finalize OpenGL drawing */
  glFinish();

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
