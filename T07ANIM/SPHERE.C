/* FILENAME: SPHERE.C
 * PROGRAMMER: DS1
 * DATE: 07.06.2016
 * PURPOSE: Sphere drawing function
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "anim.h"

#define M 200
#define N (M / 2)

VEC Sphere[N][M];

/***
 * Sphere handle functions
 ***/

/* Image representation type */
typedef struct
{
  ds1UNIT;
  HBITMAP hBmGlobe;
  DWORD *Bits;
  INT W, H, X, Y, R;
} ds1UNIT_GLOBE;

ds1UNIT_GLOBE Globe;
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
static VOID SphereDrawEllipse( HDC hDC, INT Xc, INT Yc, INT R )
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
static VOID SphereDrawLines( HDC hDC, INT Xc, INT Yc, INT R )
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
static VOID SphereDrawPolygon( HDC hDC, INT Xc, INT Yc, INT R )
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

/* Draw quadrilateral function.
 * ARGUMENTS:
 *   - drawing device context:
 *       HDC hDC;
 *   - corner points:
 *       POINT P0, P1, P2, P3;
 *   - color:
 *       DWORD Color;
 * RETURNS: None.
 */
static VOID DrawQuad( HDC hDC, POINT P0, POINT P1, POINT P2, POINT P3 )
{
  INT s =
    (P0.x - P1.x) * (P0.y + P1.y) +
    (P1.x - P2.x) * (P1.y + P2.y) +
    (P2.x - P3.x) * (P2.y + P3.y) +
    (P3.x - P0.x) * (P3.y + P0.y);

  if (s > 0)
  {
    POINT pts[4];
    
    pts[0] = P0;
    pts[1] = P1;
    pts[2] = P2;
    pts[3] = P3;

    Polygon(hDC, pts, 4);
  }
} /* End of 'DrawQuad' function */

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

/* Vector normalization function.
 * ARGUMENTS:
 *   - vector to be normalize:
 *       VEC V;
 * RETURNS:
 *   (VEC) normalized vector value.
 */
static VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len != 1 && len != 0)
    len = sqrt(len), V.X /= len, V.Y /= len, V.Z /= len;
  return V;
} /* End of 'VecNormalize' function */

/* Rotate vector function.
 * ARGUMENTS:
 *   - vector to be rotated:
 *       VEC P;
 *   - vector rotated around:
 *       VEC A;
 *   - rotation angle in degree:
 *       DBL Angle;
 * RETURNS:
 *   (VEC) rotated vector value.
 */
static VEC Rotate( VEC P, VEC A, DBL Angle )
{
  DBL si, co;

  A = VecNormalize(A);

  Angle *= DS1_PI / 180;
  si = sin(Angle);
  co = cos(Angle);

  return VecSet(P.X * (co + A.X * A.X * (1 - co)) +
                P.Y * (A.Y * A.X * (1 - co) + A.Z * si) +
                P.Z * (A.Z * A.X * (1 - co) - A.Y * si),
                P.X * (A.X * A.Y * (1 - co) - A.Z * si) +
                P.Y * (co + A.Y * A.Y * (1 - co)) + 
                P.Z * (A.Z * A.Y * (1 - co) + A.X * si),
                P.X * (A.X * A.Z * (1 - co) + A.Y * si) +
                P.Y * (A.Y * A.Z * (1 - co) - A.X * si) + 
                P.Z * (co + A.Z * A.Z * (1 - co)));
} /* End of 'Rotate' function */

/* Sphere draw function 
 * ARGUMENTS:
 *  -  Handle DC:
 *       HDC hDC;
 *  -  X center coordinate:
 *       INT Xc;
 *  -  Y center coordinate:
 *       INT Yc;
 * RETURNS:
 * None.
 */
static VOID SphereDraw( ds1ANIM *Ani, INT xc, INT yc, INT R1 )
{
  DOUBLE phi, theta, phaze = Ani->Time;
  INT i, j, r1 = R1;
  INT img_x, img_y;
  static VEC V[N][M];
  static POINT Ps[N][M], p0, p1, p2, p3;
  SYSTEMTIME Time;
  COLORREF c;
  BYTE r,g,b;
  HDC hDC = Ani->hDC;
  

  GetLocalTime(&Time);
  for (i = 0; i < N; i++)
  {
    theta = i * DS1_PI / (N - 1);
    for (j = 0; j < M; j++)
    { 

      phi = j * 2.0 * DS1_PI / (M - 1) + phaze;
      V[i][j].X = r1 * sin(theta) * cos(phi);
      V[i][j].Y = r1 * sin(theta) * sin(phi);
      V[i][j].Z = r1 * cos(theta);
      V[i][j] = Rotate(V[i][j], VecSet(1, 1, 1), 30);
      Ps[i][j].x = xc + (INT)V[i][j].X;
      Ps[i][j].y = yc + (INT)V[i][j].Z;
      //SetPixelV(hDC, V[i][j].X + xc, V[i][j].Z + yc, RGB(b, g, r));
    }
  }

  for (j = 0; j < M - 1; j++)
  { 
    for (i = 0; i < N - 1; i++)
    { 
      img_x = j * (Globe.W - 1) / (M - 1);
      img_y = i * (Globe.H - 1) / (N - 1);
      c = Globe.Bits[img_x + img_y * Globe.W]; /* GetPixel(Globe.hDC, img_x, img_y); */
      r = GetRValue(c);
      g = GetGValue(c);
      b = GetBValue(c);
      c = RGB(b, g, r);
      p0 = Ps[i][j];
      p1 = Ps[i][j + 1];
      p2 = Ps[i + 1][j + 1];
      p3 = Ps[i + 1][j];
      SelectObject(hDC, GetStockObject(DC_PEN));
      SelectObject(hDC, GetStockObject(DC_BRUSH));
      SetDCPenColor(hDC, c);
      SetDCBrushColor(hDC, c);
      DrawQuad(hDC, p0, p1, p2, p3);
    }
  } 
  /*for (i = 0; i < N; i++)
  { 
    MoveToEx(hDC, xc + V[i][0].X, yc - V[i][0].Z, NULL);
    for (j = 1; j < M; j++)
    {       
      LineTo(hDC, xc + V[i][j].X, yc - V[i][j].Z);
    }
  } 
  for (j = 0; j < M; j++)
  { 
    MoveToEx(hDC, xc + V[0][j].X, yc - V[0][j].Z, NULL);
    for (i = 1; i < N; i++)
    {       
      LineTo(hDC, xc + V[i][j].X, yc - V[i][j].Z);
    }
  }*/
}

/* Unit ball initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       vg4UNIT_BALL *Uni;
 *   - animation context:
 *       vg4ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitInit( ds1UNIT_GLOBE *Uni, ds1ANIM *Ani )
{
} /* End of 'VG4_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitClose( ds1UNIT_GLOBE *Uni, ds1ANIM *Ani )
{
  free(Globe.Bits);
} /* End of 'DS1_UnitClose' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       ds1UNIT_BALL *Uni;
 *   - animation context:
 *       ds1ANIM *Ani;
 * RETURNS: None.
 */
static VOID DS1_UnitRender( ds1UNIT_GLOBE *Uni, ds1ANIM *Ani )
{
  SphereDraw(Ani, Uni->X, Ani->H / 2, Uni->R); 
  /*SphereDrawLines(Ani->hDC, Ani->W / 2, Ani->H / 2, 100);*/
} /* End of 'DS1_UnitRender' function */

/* Unit ball creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (ds1UNIT *) pointer to created unit.
 */
ds1UNIT * DS1_UnitCreateGlobe( INT X, INT Y, INT R )
{
  ds1UNIT_GLOBE *Uni;

  if ((Uni = (ds1UNIT_GLOBE *)DS1_AnimUnitCreate(sizeof(ds1UNIT_GLOBE))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)DS1_UnitInit;
  Uni->Render = (VOID *)DS1_UnitRender;
  Uni->X = X;
  Uni->Y = Y;
  Uni->R = R;
  return (ds1UNIT *)Uni;
} /* End of 'DS1_UnitCreateBall' function */


/* END OF 'SPHERE.C' FILE */
