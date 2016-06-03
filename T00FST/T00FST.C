/* FILENAME: T00FST.C
 * PROGRAMMER: DS1
 * DATE: 01.06.2016
 * PURPOSE: WinAPI windowed application sample
 */
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
  static INT w = 1600, h = 800, r = 15;
  static DOUBLE len, mn = 0, mx = 0, x = 0, y = 0;
  static BOOL IsEyes = 1;
  static HBITMAP hBm;
  static HDC hMemDC;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 10, NULL);
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_COMMAND:
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
    SetDCPenColor(hMemDC, RGB(255, 255, 255));
    SetDCBrushColor(hMemDC, RGB(255, 255, 255));
    Rectangle(hMemDC, 0, 0, w, h);
    SetDCPenColor(hMemDC, RGB(0, 0, 0));

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWinFunc' function */

/* END OF 'T00FST.C' FILE */