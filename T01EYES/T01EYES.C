/* FILENAME: T01EYES.C
 * PROGRAMMER: DS1
 * DATE: 01.06.2016
 * PURPOSE: WinAPI windowed application sample
 */
#include <math.h>
#include <windows.h>

/* My window class */
#define MY_WND_CLASS "My Window Class"

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
  CreateWindow("Button",
    "Eyes",
    WS_CHILDWINDOW | WS_VISIBLE,
    20, 20,
    50, 20,
    hWnd, NULL, hInstance, NULL);

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
 *  -  Handle d c:
 *       HDC hDC;
 *  -  X center coordinate:
 *       INT Xc;
 *  -  Y center coordinate:
 *       INT Yc;
 *  -  Radius of eye:
 *       INT R;
 *  -  Radius of pupil:
 *       INT R1;
 */
VOID Eyes( HWND hWnd, HDC hDC, INT Xc, INT Yc, INT R, INT R1 )
{
  int x, y, x1, y1;
  double len;
  POINT pt;
  
  /* Drawing eye */
  SetDCBrushColor(hDC, RGB(255, 255, 255));
  Ellipse(hDC, Xc - R, Yc + R, Xc + R, Yc - R);
  
  /* Coordinate pupil */
  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);
  x = pt.x - Xc;
  y = pt.y - Yc;
  len = sqrt(x * x + y * y);
  x1 = x, y1 = y;
  if (len > R - R1)
    x1 = (INT)((R - R1) * x / len);
  if (len > R - R1)
    y1 = (INT)((R - R1) * y / len);
  /* Drawing pupil */
  SetDCBrushColor(hDC, RGB(0, 0, 0));
  Ellipse(hDC, x1 + Xc - R1, y1 + Yc + R1, x1 + Xc + R1, y1 + Yc - R1);
    
}/* End of 'Eyes' function */



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
  INT i, j;
  HDC hDC;
  PAINTSTRUCT ps;
  POINT pt;
  static INT w = 1600, h = 800, r = 15;
  static DOUBLE len, mn = 0, mx = 0, x = 0, y = 0;
  static BOOL IsEyes = 1;
  static BITMAP Bm;
  static HBITMAP hBm, hBmLogo;
  static HDC hMemDC, hMemDCLogo;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    hBmLogo = LoadImage(NULL, "C.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hMemDCLogo = CreateCompatibleDC(hDC);
    hBmLogo = CreateCompatibleBitmap(hDC, w, h);
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
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    Rectangle(hMemDC, 0, 0, w, h);
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(255, 255, 255));
    /* Drawing 2 eyes */
    Ellipse(hMemDC, 0, 0, w / 2, h);
    Ellipse(hMemDC, w / 2, 0, w, h);

    GetCursorPos(&pt);
    ScreenToClient(hWnd, &pt);
    SelectObject(hMemDC, GetStockObject(DC_PEN));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCPenColor(hMemDC, RGB(0, 0, 0));
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));
    /* Black eyes part */
    /* Coordinate pupil left */
    x = pt.x - w / 4;
    y = pt.y - h / 2;
    x /= (w / 4 - r);
    y /= (h / 2 - r);
    len = sqrt(x * x + y * y);
    if (len > 1)
      x = (x / len), y = (y / len);
    x *= (w / 4 - r);
    y *= (h / 2 - r);
    /* Drawing pupil left */
    Ellipse(hMemDC, (INT)x + (w / 4 - r), (INT)y + (h / 2 - r), (INT)x + (w / 4 + r), (INT)y + (h / 2 + r));
    /* Coordinate pupil right*/
    x = pt.x - 3 * w / 4;
    y = pt.y - h / 2;
    x /= (w / 4 - r);
    y /= (h / 2 - r);
    len = sqrt(x * x + y * y);
    if (len > 1)
      x = (x / len), y = (y / len);
    x *= (w / 4 - r);
    y *= (h / 2 - r);
    /* Drawing pupil right */
    Ellipse(hMemDC, (INT)x + (3 * w / 4 - r), (INT)y + (h / 2 - r), (INT)x + (3 * w / 4 + r), (INT)y + (h / 2 + r));
    /**/
    if (IsEyes)
      for (i = -2; i <= 2; i++)
        for (j = -2; j <= 2; j++)
          Eyes(hWnd, hMemDC, w / 2 + i * w / 6, h / 2 + j * h / 6, 40, 10);
    
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWinFunc' function */

/* END OF 'T01EYES.C' FILE */