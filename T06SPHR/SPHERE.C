/* FILENAME: SPHERE.C
 * PROGRAMMER: DS1
 * DATE: 07.06.2016
 * PURPOSE: Sphere drawing function
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "resource.h"
#include "sphere.h"

#define DS1_PI 3.14159265358979323846
#define M 30
#define N (M / 2)

VEC Sphere[N][M];

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
      if (j == 0)
        MoveToEx(hDC, (INT)(x + Xc), (INT)(y + Yc), NULL);
      else
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
      if (i == 0)
        MoveToEx(hDC, (INT)(x + Xc), (INT)(y + Yc), NULL);
      else
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

/* END OF 'SPHERE.C' FILE */
