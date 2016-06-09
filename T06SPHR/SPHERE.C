/* FILENAME: SPHERE.C
 * PROGRAMMER: DS1
 * DATE: 07.06.2016
 * PURPOSE: Sphere drawing function
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sphere.h"
#include "vec.h"

#define DS1_PI 3.14159265358979323846
#define M 30
#define N (M / 2)

VEC Sphere[N][M];

/***
 * Sphere handle functions
 ***/

/* Image representation type */
typedef struct
{
  HBITMAP hBmGlobe;
  DWORD *Bits;
  INT W, H;
} IMG;

IMG Globe;

/* Sphere draw function 
 * ARGUMENTS:
 *  -  Handle DC:
 *       HDC hDC;
 *  -  X center coordinate:
 *       INT Xc;
 *  -  Y center coordinate:
 *       INT Yc;
 *  -  Radius of Sphere:
 *       INT R;
 * RETURNS:
 * None.
 */
VOID SphereDrawEllipse( HDC hDC, INT Xc, INT Yc, INT R )
{
  INT i, j;


  for (i = 0; i < N; i++)
  {
    DBL theta = DS1_PI * i / (N - 1);
    for (j = 0; j < M; j++)
    {
      DBL x, y, z, r = R / 50, phi = 2 * DS1_PI * j / (M - 1);

      x = R * sin(theta) * cos(phi);
      z = R * sin(theta) * sin(phi);
      y = R * cos(theta);

      Ellipse(hDC, (INT)(x + Xc - r), (INT)(y + Yc - r), 
                (INT)(x + Xc + r), (INT)(y + Yc + r));
    }
  }
}/* End of 'SphereDrawEllipse' function */

/* Sphere draw function 
 * ARGUMENTS:
 *  -  Handle DC:
 *       HDC hDC;
 *  -  X center coordinate:
 *       INT Xc;
 *  -  Y center coordinate:
 *       INT Yc;
 *  -  Radius of Sphere:
 *       INT R;
 * RETURNS:
 * None.
 */
VOID SphereDrawLines( HDC hDC, INT Xc, INT Yc, INT R )
{
  INT i, j;
  DBL delta = DS1_PI / 6, phase, r = 10;
  HPEN hPen;
  SYSTEMTIME ST;

  GetLocalTime(&ST);

  hPen = SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(0, 155, 0));
  phase = ST.wMilliseconds / 200;

  for (i = 0; i < N; i++)
  {
    DBL theta = DS1_PI * i / (N - 1);
    MoveToEx(hDC, (INT)(Xc + R * sin(theta) * cos(phase)), (INT)(Yc + R * cos(theta)), NULL);

    for (j = 0; j < M; j++)
    {
      DBL x, y, z, r = R / 10, phi = 2 * DS1_PI * j / (M - 1) + phase;

      x = R * sin(theta) * cos(phi);
      z = R * sin(theta) * sin(phi);
      y = R * cos(theta);
      LineTo(hDC, (INT)(x + Xc), (INT)(y + Yc));
    }
  }
  for (j = 0; j < M; j++)
  {
    DBL x, y, z, r = R / 10, phi = 2 * DS1_PI * j / (M - 1) + phase;
    MoveToEx(hDC, (INT)(Xc + R * sin(0) * cos(phi)), (INT)(Yc + R * cos(0)), NULL);
    for (i = 0; i < N; i++)
    {
      DBL theta = DS1_PI * i / (N - 1);

      x = R * sin(theta) * cos(phi);
      z = R * sin(theta) * sin(phi);
      y = R * cos(theta);
      LineTo(hDC, (INT)(x + Xc), (INT)(y + Yc));
    }
  }
  SelectObject(hDC, hPen);
}/* End of 'SphereDrawLines' function */

/* Sphere draw function 
 * ARGUMENTS:
 *  -  Handle DC:
 *       HDC hDC;
 *  -  X center coordinate:
 *       INT Xc;
 *  -  Y center coordinate:
 *       INT Yc;
 *  -  Radius of Sphere:
 *       INT R;
 * RETURNS:
 * None.
 */
VOID SphereDrawPolygon( HDC hDC, INT Xc, INT Yc, INT R )
{
  INT i, j;
  DBL delta;
  HPEN hPen;
  SYSTEMTIME ST;

  GetLocalTime(&ST);

  hPen = SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(0, 155, 0));
  delta = ST.wMilliseconds / 70;

  for (i = 0; i < N; i++)
  {
    DBL theta = DS1_PI * i / N;

    for (j = 0; j < M; j++)
    {
      DBL r = R / 10, phi = 2 * DS1_PI * j / M + delta;

      Sphere[i][j].X = R * sin(theta) * cos(phi);
      Sphere[i][j].Y = R * sin(theta) * sin(phi);
      Sphere[i][j].Z = R * cos(theta);
    }
  }
  SelectObject(hDC, hPen);
}/* End of 'SphereDrawPolygon' function */

/*
  Check matrix and vector functions
  M = MatrixIdentity();
  C = VecSet(1, 0.5, 2);
  A = VecSet(1, 0, 0);
  B = VecSet(0, 1, 0);
  C = VecAddVec(A, B);
  C = VecDivNum(C, 2);
  C = VecCrossVec(A, B);
  res = VecDotVec(A, A);
  res = VecLen(A);
  res = VecLen2(A);
  C = VecMullNum(C, 2);
  C = VecNeg(C);
  C = VecNorlize(C);
  C = VecSubVec(C, C);
  M = MatrixTranslate(2, 2, 2);
  C = VecTransform(A, M);
  res = MatrDeterm(M);
  M = MatrInverse(M);
  M = MatrixRotateX(90);
  M = MatrixRotateY(90);
  M = MatrixRotateZ(90);
  M = MatrixRotate(90, 0, 1, 0);
  M = MatrixScale(2, 2, 2);
  M = MatrMullMatr(M, MatrixIdentity());
  C = PointTransform(C, MatrixIdentity());
  C = NormalTransform(C, MatrixIdentity());
  */

/* Load sphere texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID LoadSphere( VOID )
{
  HDC hDC = GetDC(NULL), hMemDC, hMemDC1;
  HBITMAP hBm;
  BITMAP bm;
  BITMAPINFOHEADER bmih;

  /* Load image from file */
  hMemDC = CreateCompatibleDC(hDC);
  hBm = LoadImage(NULL, "GLOBE.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  GetObject(hBm, sizeof(bm), &bm);
  Globe.W = bm.bmWidth;
  Globe.H = bm.bmHeight;
  SelectObject(hMemDC, hBm);

  /* Fill DIB info */
  memset(&bmih, 0, sizeof(bmih));
  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biBitCount = 32;                   /* BGRx - DWORD */
  bmih.biPlanes = 1;                      /* always */
  bmih.biCompression = BI_RGB;            /* 0 - no compression */
  bmih.biWidth = bm.bmWidth;              /* width */
  bmih.biHeight = -bm.bmHeight;           /* height + first coded row is 0 */
  bmih.biSizeImage = bm.bmWidth * bm.bmHeight * 4;  /* image size in bytes */

  Globe.hBmGlobe = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS,
                 (VOID **)&Globe.Bits, NULL, 0);
  hMemDC1 = CreateCompatibleDC(hDC);
  SelectObject(hMemDC1, Globe.hBmGlobe);

  BitBlt(hMemDC1, 0, 0, Globe.W, Globe.H, hMemDC, 0, 0, SRCCOPY);

  DeleteDC(hMemDC);
  DeleteDC(hMemDC1);
  DeleteObject(hBm);

  ReleaseDC(NULL, hDC);
} /* End of 'LoadSphere' function */

/*
. . .
      INT img_x, img_y;
      COLORREF c;

. . .
      img_x = j * (Globe.W - 1) / (M - 1);
      img_y = i * (Globe.H - 1) / (N - 1);
      c = Globe.Bits[img_x + img_y * Globe.W]; /* GetPixel(Globe.hDC, img_x, img_y); */
/*
      SetPixelV(hDC, x, y, c);
*/

/* END OF 'SPHERE.C' FILE */
