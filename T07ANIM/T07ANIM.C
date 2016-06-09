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

#include "resource.h"
#include "vec.h"

/* My window class */
#define MY_WND_CLASS "My Window Class"

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


  /* Create window class */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hInstance = hInstance;
  wc.lpszClassName = MY_WND_CLASS;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = MyWinFunc;
  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error registor window class", "ERROR", MB_OK | MB_ICONERROR);
    return 0;
  } 

  /* Create window */
  hWnd = CreateWindow(MY_WND_CLASS,
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



  /* Run message loop */
  while (GetMessage(&msg, NULL, 0, 0))
  { 
    /**/
    /*TranslateMessage(&msg);*/
    /* Dispatch message */
    DispatchMessage(&msg);
  }
  return 0;
}/* End of 'WinMain' function */

/* Set/reset full screen mode function */
VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (IsFullScreen)
  {
    /* restore window size */
    SetWindowPos(hWnd, HWND_TOP,
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
    GetWindowRect(hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Obtain monitor info */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* Set window new size */
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOPMOST,
      rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
} /* End of 'FlipFullScreen' function */


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
  SYSTEMTIME ST;
  CREATESTRUCT *cs;
  MINMAXINFO *MinMax;
  static INT w = 800, h = 400;
  static BITMAP Bm;
  static HBITMAP hBm, hBmAND, hBmXOR;
  static HDC hMemDC, hMemDCAND, hMemDCXOR;
  
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
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);

    cs = (CREATESTRUCT *)lParam;
    /*hBmAND = LoadImage(NULL, "SDAND.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);*/
    hBmAND = LoadImage(cs->hInstance, (CHAR *)IDB_AND, IMAGE_BITMAP, 0, 0, 0);
    hMemDCAND = CreateCompatibleDC(hDC);
    SelectObject(hMemDCAND, hBmAND);
    GetObject(hBmAND, sizeof(Bm), &Bm);;

    /*hBmXOR = LoadImage(NULL, "SDXOR.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);*/
    hBmXOR = LoadImage(cs->hInstance, (CHAR *)IDB_XOR, IMAGE_BITMAP, 0, 0, 0);
    hMemDCXOR = CreateCompatibleDC(hDC);
    SelectObject(hMemDCXOR, hBmXOR);

    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_COMMAND:
    /*InvalidateRect(hWnd, NULL, FALSE);*/
    return 0;
  case WM_ERASEBKGND:
    /*InvalidateRect(hWnd, NULL, FALSE);*/
    return 0;
  case WM_SIZE:
    w = LOWORD(lParam);
    h = HIWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, w, h);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 0, 0);
    break;
  case WM_MOUSEMOVE:
    /*InvalidateRect(hWnd, NULL, TRUE);*/
    return 0;
  case WM_KEYDOWN:
    if (LOWORD(wParam) == 'F')
      FlipFullScreen(hWnd);
    else if (LOWORD(wParam) == VK_ESCAPE)
      DestroyWindow(hWnd);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    DeleteObject(hBm);
    DeleteObject(hMemDC);
    DeleteObject(hBmAND);
    DeleteObject(hMemDCAND);
    DeleteObject(hBmXOR);
    DeleteObject(hMemDCXOR);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  case WM_TIMER:
    /*Drawing*/
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    Rectangle(hMemDC, 0, 0, w, h);
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(255, 255, 255));

    GetLocalTime(&ST);

    /* Logo */
    BitBlt(hMemDC, -70, -90, Bm.bmWidth, Bm.bmHeight, hMemDCAND, 0, 0, SRCAND);
    BitBlt(hMemDC, -70, -90, Bm.bmWidth, Bm.bmHeight, hMemDCXOR, 0, 0, SRCINVERT);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'MyWinFunc' function */

/* END OF 'T07ANIM.C' FILE */
