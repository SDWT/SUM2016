/* FILENAME: T02CLOCK.C
 * PROGRAMMER: DS1
 * DATE: 02.06.2016
 * PURPOSE: Clock
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#include "resource.h"

/* My window class */
#define MY_WND_CLASS "My Window Class"
#define DS1_PI 3.14159265358979323846

/* Forward reference */
LRESULT CALLBACK MyWinFunc( HWND hWnd, UINT Msg,
                            WPARAM wParam, LPARAM lParam );

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
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
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
                      500, 500,
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
  HDC hDC;
  PAINTSTRUCT ps;
  HPEN hPen, hOldPen;
  SYSTEMTIME ST;
  CREATESTRUCT *cs;
  MINMAXINFO *MinMax;
  static CHAR Str[50], StrBuf[50], StrDays[][50] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  static INT w = 1600, h = 800, r = 15;
  static DOUBLE len, mn = 0, mx = 0, x = 0, y = 0;
  static BITMAP Bm, bmS;
  static HBITMAP hBm, hBmAND, hBmXOR, hBmLogo;
  static HDC hMemDC, hMemDCAND, hMemDCXOR, hMemDCLogo;
  /*static LOGFONT font;*/
 
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

    /*hBmLogo = LoadImage(NULL, "C.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);*/
    hBmLogo = LoadImage(cs->hInstance, (CHAR *)IDB_CLOCKFACE, IMAGE_BITMAP, 0, 0, 0);
    hMemDCLogo = CreateCompatibleDC(hDC);
    SelectObject(hMemDCLogo, hBmLogo);
    GetObject(hBmLogo, sizeof(bmS), &bmS);;

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
    /* Fullscreen on */
    FlipFullScreen(hWnd);
    return 0;
  case WM_COMMAND:
    /*InvalidateRect(hWnd, NULL, FALSE);*/
    return 0;
  case WM_ERASEBKGND:
    /*InvalidateRect(hWnd, NULL, FALSE);*/
    return 0;
  case WM_KEYDOWN:
    if (LOWORD(wParam) == 'F')
      FlipFullScreen(hWnd);
    else if (LOWORD(wParam) == VK_ESCAPE)
      DestroyWindow(hWnd);
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
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    DeleteObject(hBm);
    DeleteObject(hMemDC);
    DeleteObject(hBmLogo);
    DeleteObject(hMemDCLogo);
    DeleteObject(hBmAND);
    DeleteObject(hMemDCAND);
    DeleteObject(hBmXOR);
    DeleteObject(hMemDCXOR);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  case WM_TIMER:
    /*Drawing*/
    StretchBlt(hMemDC, 0, 0, w, h, hMemDCLogo, 0, 0,  bmS.bmWidth, bmS.bmHeight, SRCCOPY);
    /*BitBlt(hMemDC, 0, 0, Bm.bmWidth, Bm.bmHeight, hMemDCLogo, 0, 0, SRCCOPY);*/
    
    GetLocalTime(&ST);
    /* Hour hand */
    hPen = CreatePen(PS_SOLID, 6, RGB(255, 0, 0));
    hOldPen = SelectObject(hMemDC, hPen);

    MoveToEx(hMemDC, w / 2, h / 2, NULL);
    LineTo(hMemDC, (INT)(w / 2 + w / 8 * sin(30.0 * ((ST.wHour % 12) * 60 + ST.wMinute) / 60 * DS1_PI / 180)), 
             (INT)(h / 2 - h / 8 * cos(30.0 * ((ST.wHour % 12) * 60 + ST.wMinute) / 60 * DS1_PI / 180)));
    
    SelectObject(hMemDC, hOldPen);
    DeleteObject(hPen);
    /* Minute hand */
    hPen = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
    hOldPen = SelectObject(hMemDC, hPen);

    MoveToEx(hMemDC, w / 2, h / 2, NULL);
    LineTo(hMemDC, (INT)(w / 2 + w / 4 * sin(6.0 * (ST.wMinute * 60 + ST.wSecond) / 60 * DS1_PI / 180)), 
             (INT)(h / 2 - h / 4 * cos(6.0 * (ST.wMinute * 60 + ST.wSecond) / 60 * DS1_PI / 180)));
    
    SelectObject(hMemDC, hOldPen);
    DeleteObject(hPen);
    /* Second hand */
    hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    hOldPen = SelectObject(hMemDC, hPen);

    MoveToEx(hMemDC, w / 2, h / 2, NULL);
    LineTo(hMemDC, (INT)(w / 2 + w / 3 * sin(6.0 * (ST.wSecond + ST.wMilliseconds / 1000.0) * DS1_PI / 180)), 
             (INT)(h / 2 - h / 3 * cos(6.0 * (ST.wSecond + ST.wMilliseconds / 1000.0) * DS1_PI / 180)));
    
    SelectObject(hMemDC, hOldPen);
    DeleteObject(hPen);

    SetBkMode(hMemDC, TRANSPARENT);
    /* Write date and time on display */
    TextOut(hMemDC, 2, h - h / 30, StrBuf, sprintf(StrBuf, "%s, %02d.%02d.%04d %02d:%02d.%02d", StrDays[ST.wDayOfWeek % 7], 
                                                  ST.wDay, ST.wMonth, ST.wYear, ST.wHour, ST.wMinute, ST.wSecond));
    /* Logo */
    BitBlt(hMemDC, -70, -90, Bm.bmWidth, Bm.bmHeight, hMemDCAND, 0, 0, SRCAND);
    BitBlt(hMemDC, -70, -90, Bm.bmWidth, Bm.bmHeight, hMemDCXOR, 0, 0, SRCINVERT);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWinFunc' function */

/* END OF 'T02CLOCK.C' FILE */