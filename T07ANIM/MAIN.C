/* FILENAME: T07ANIM.C
 * PROGRAMMER: DS1
 * DATE: 08.06.2016
 * PURPOSE: Animation sample
 *          Main module
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>

#include "anim.h"
#include "units.h"

/* My window class */
#define DS1_MY_WND_CLASS "My Window Class"

/* Forward reference */
LRESULT CALLBACK MyWinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* Main program function
 * ARGUMENTS:
 *  -  Handle inctance(sample) application:
 *       HINSTANCE hInctance;
 *  -  Handle previous inctance(sample) application:
 *       HINSTANCE hPrevInctance;
 *  -  Command string:
 *       LPSTR lpCmdLine;
 *  -  :
 *       INT nShowCmd;
 * RETURNS:
 *  - (INT) Code of ending program.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    LPSTR lpCmdLine, INT nShowCmd )
{
  WNDCLASS wc;
  MSG msg;
  HWND hWnd;

  /* Memmory left checking */
  SetDbgMemHooks();

  /* Create window class */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hInstance = hInstance;
  wc.lpszClassName = DS1_MY_WND_CLASS;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = MyWinFunc;
  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error registor window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  } 

  /* Create window */
  hWnd = CreateWindow(DS1_MY_WND_CLASS,
                      "30!",
                      WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT,
                      1600, 800,
                      NULL, NULL, hInstance, NULL);
  if (hWnd == NULL)
  {
    MessageBox(NULL, "Create window error", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  }
  /* Show window */
  ShowWindow(hWnd, SW_SHOWNORMAL);
  /* Update window */
  UpdateWindow(hWnd);

  /*** Add unit samples ***/
  LoadSphere();
  DS1_AnimAddUnit(DS1_UnitCreateGlobe(1600 / 4, 800 / 2, (2400) / 10));
  DS1_AnimAddUnit(DS1_UnitCreateGlobe(3 * 1600 / 4, 800 / 2, (2400) / 10));

  /* Run message loop */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);
  return 0;
}/* End of 'WinMain' function */

/* Callback my class function 
 *  -  Handle window:
 *       HWND hWnd;
 *  -  Incoming message:
 *       UINT Msg;
 *  -  Word parametr:
 *       WPARAM wParam;
 *  -  Long parametr:
 *       LPARAM lParam;
 */
LRESULT CALLBACK MyWinFunc( HWND hWnd, UINT Msg,
                            WPARAM wParam, LPARAM lParam )
{

  /*
  INT i, j;
  CHAR StrBuf[30];
  */
  HDC hDC;
  PAINTSTRUCT ps;
  MINMAXINFO *MinMax;
  static INT w = 800, h = 400;
  static BITMAP Bm;
  static HBITMAP hBm;
  static HDC hMemDC;
  
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    MinMax = (MINMAXINFO *)lParam;
    MinMax->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    /* Animation initialization */
    DS1_AnimInit(hWnd);
    SendMessage(hWnd, WM_SIZE, 0, 0);
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    /* Animation resize */
    DS1_AnimResize(w, h);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    break;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    /* Animation copy frame */
    DS1_AnimCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    /* Animation close */
    DS1_AnimClose();
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;

  case WM_TIMER:
    /* Animation render */
    DS1_AnimRender();

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_MOUSEWHEEL:
    DS1_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  case WM_ERASEBKGND:
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'MyWinFunc' function */

/* END OF 'T07ANIM.C' FILE */
