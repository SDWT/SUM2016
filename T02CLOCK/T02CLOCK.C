/* FILENAME: T02CLOCK.C
 * PROGRAMMER: DS1
 * DATE: 02.06.2016
 * PURPOSE: Clock
 */
#include <math.h>
#include <string.h>
#include <windows.h>

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
  CHAR Str[50], StrBuf[50], StrDays[7][50] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
  static INT w = 1600, h = 800, r = 15;
  static DOUBLE len, mn = 0, mx = 0, x = 0, y = 0;
  static BOOL IsEyes = 1;
  static BITMAP Bm;
  static HBITMAP hBm, hBmLogo;
  static HDC hMemDC, hMemDCLogo;
  SYSTEMTIME ST;
 
  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hBmLogo = LoadImage(NULL, "C.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hMemDCLogo = CreateCompatibleDC(hDC);
    SelectObject(hMemDCLogo, hBmLogo);
    GetObject(hBmLogo, sizeof(Bm), &Bm);;
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_COMMAND:
    IsEyes = !IsEyes;
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
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    DeleteObject(hBm);
    DeleteObject(hMemDC);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  case WM_TIMER:
    /*Drawing*/
    /*
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    Rectangle(hMemDC, 0, 0, w, h);
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(255, 255, 255));
    */
    StretchBlt(hMemDC, 0, 0, w, h, hMemDCLogo, 0, 0,  Bm.bmWidth, Bm.bmHeight, SRCCOPY);
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
    LineTo(hMemDC, (INT)(w / 2 + w / 3 * sin(6.0 * (ST.wSecond * 1000 + ST.wMilliseconds) / 1000 * DS1_PI / 180)), 
             (INT)(h / 2 - h / 3 * cos(6.0 * (ST.wSecond * 1000 + ST.wMilliseconds) / 1000 * DS1_PI / 180)));
    
    SelectObject(hMemDC, hOldPen);
    DeleteObject(hPen);

    SetBkMode(hMemDC, TRANSPARENT);
    StrBuf[0] = 'T';
    StrBuf[1] = 0;
    /* Copy day name  */
    strcpy(StrBuf, StrDays[(ST.wDayOfWeek - 1) % 7]);
    strcat(StrBuf, " "); 
    /* Copy date */
    Str[1] = '0' + ST.wDay % 10;
    Str[0] = '0' + (ST.wDay / 10) % 10;
    Str[2] = '.';
    Str[4] = '0' + ST.wMonth % 10;
    Str[3] = '0' + (ST.wMonth / 10) % 10;
    Str[5] = '.';
    Str[9] = '0' + ST.wYear % 10;
    Str[8] = '0' + (ST.wYear / 10) % 10;
    Str[7] = '0' + (ST.wYear / 100) % 10;
    Str[6] = '0' + (ST.wYear / 1000) % 10;
    Str[10] = ' ';
    Str[11] = 0;
    strcat(StrBuf, Str); 
    /* Copy time */
    Str[1] = '0' + ST.wHour % 10;
    Str[0] = '0' + (ST.wHour / 10) % 10;
    Str[2] = ':';
    Str[4] = '0' + ST.wMinute % 10;
    Str[3] = '0' + (ST.wMinute / 10) % 10;
    Str[5] = '.';
    Str[7] = '0' + ST.wSecond % 10;
    Str[6] = '0' + (ST.wSecond / 10) % 10;
    Str[8] = 0;
    strcat(StrBuf, Str); 
    /* Write date and time on display */
    TextOut(hMemDC, 2, h - h / 30, StrBuf, strlen(StrBuf));

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWinFunc' function */

/* END OF 'T02CLOCK.C' FILE */