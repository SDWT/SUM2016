/* FILENAME: T03POLE.C
 * PROGRAMMER: DS1
 * DATE: 03.06.2016
 * PURPOSE: Magnetic pole to cursor
 */
#include <math.h>
#include <windows.h>

/* My window class */
#define MY_WND_CLASS "My Window Class"

/* Forward reference */
LRESULT CALLBACK MyWinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
VOID Arrow( HWND hWnd, HDC hDC, INT X, INT Y, INT H1, INT H2, INT W, COLORREF ColorN, COLORREF ColorS );

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
  static INT n = 2, fl = 1;
  HDC hDC;
  PAINTSTRUCT ps;
  static INT w = 1600, h = 800, r = 15;
  static DOUBLE len, mn = 0, mx = 0, x = 0, y = 0;
  static BOOL IsEyes = 1;
  static BITMAP Bm;
  static HBITMAP hBm, hBmAND, hBmXOR;
  static HDC hMemDC, hMemDCAND, hMemDCXOR;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    
    hBmAND = LoadImage(NULL, "SDAND.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hMemDCAND = CreateCompatibleDC(hDC);
    SelectObject(hMemDCAND, hBmAND);
    GetObject(hBmAND, sizeof(Bm), &Bm);;

    hBmXOR = LoadImage(NULL, "SDXOR.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hMemDCXOR = CreateCompatibleDC(hDC);
    SelectObject(hMemDCXOR, hBmXOR);
    

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
  case WM_KEYDOWN:
    n += fl;
    if (n >= 10)
      fl = -1;
    if (n <= 1)
      fl = 1;
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

    for (i = -n; i <= n; i++)
      for (j = -n; j <= n; j++)
        Arrow(hWnd, hMemDC, w / 2 + w / 2 / (n + 1) * i, h / 2 + h / 2 / (n + 1) * j, 160 / n, 80 / n, 100 / n, RGB(0, 0, 255), RGB(255, 0, 0));
    /* Logo */
    BitBlt(hMemDC, -70, -90, Bm.bmWidth, Bm.bmHeight, hMemDCAND, 0, 0, SRCAND);
    BitBlt(hMemDC, -70, -90, Bm.bmWidth, Bm.bmHeight, hMemDCXOR, 0, 0, SRCINVERT);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
}/* End of 'MyWinFunc' function */

/* Callback my class function 
 *  -  Handle window:
 *       HWND hWnd;
 *  -  Handle d c:
 *       HDC hDC;
 *  -  X center arrow:
 *       INT X;
 *  -  Y center arrow:
 *       INT Y;
 *  -  North height:
 *        INT H1;
 *  -  South height:
 *        INT H2;
 *  -  Width arrow:
 *        INT W;
 *  -  North Color RGB(r, g, b):
 *       COLORREF ColorN;
 *  -  South Color RGB(r, g, b):
 *       COLORREF ColorS;
 */
VOID Arrow( HWND hWnd, HDC hDC, INT X, INT Y, INT H1, INT H2, INT W, COLORREF ColorN, COLORREF ColorS )
{
  DOUBLE rM, r = H1, xM, yM, iX, iY;
  POINT pN[3], pS[3], pO[4], pt;
  HPEN hPen;
  HBRUSH hBrush;


  GetCursorPos(&pt);
  ScreenToClient(hWnd, &pt);

  xM = pt.x - X, yM = pt.y - Y;
  rM = sqrt(xM * xM + yM * yM);
  xM /= rM; /*sin(a)*/
  yM /= -rM; /*cos(a)*/

  iX = 0 * yM - (0 + H2) * xM;
  iY = 0 * xM + (0 + H2) * yM;
  pO[0].x = pS[0].x = (INT)(iX + X);
  pO[0].y = pS[0].y = (INT)(iY + Y);

  iX = 0 * yM - (0 - H1) * xM;
  iY = 0 * xM + (0 - H1) * yM;
  pO[2].x = pN[0].x = (INT)(iX + X);
  pO[2].y = pN[0].y = (INT)(iY + Y);

  iX = (0 - W) * yM - 0 * xM;
  iY = (0 - W) * xM + 0 * yM;
  pO[1].x = pS[1].x = pN[1].x = (INT)(iX + X);
  pO[1].y = pS[1].y = pN[1].y = (INT)(iY + Y);

  iX = (0 + W) * yM - 0 * xM;
  iY = (0 + W) * xM + 0 * yM;
  pO[2].x = pS[2].x = pN[2].x = (INT)(iX + X);
  pO[2].y = pS[2].y = pN[2].y = (INT)(iY + Y);


  hPen = SelectObject(hDC, GetStockObject(DC_PEN));
  hBrush = SelectObject(hDC, GetStockObject(DC_BRUSH));

  SetDCPenColor(hDC, ColorN);
  SetDCBrushColor(hDC, ColorN);
  Polygon(hDC, pN, 3);

  SetDCPenColor(hDC, ColorS);
  SetDCBrushColor(hDC, ColorS);
  Polygon(hDC, pS, 3);
  
  SelectObject(hDC, GetStockObject(DC_PEN));
  SelectObject(hDC, GetStockObject(NULL_BRUSH));
  SetDCPenColor(hDC, RGB(0, 0, 0));
  Polygon(hDC, pO, 3);
  
  SelectObject(hDC, hPen);
  SelectObject(hDC, hBrush);


}/* End of 'Arrow' function */


/* END OF 'T01EYES.C' FILE */
